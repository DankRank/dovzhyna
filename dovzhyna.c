#include <assert.h>
#include <string.h>
#include "dovzhyna.h"

#include "x86optab.h"

#define lxor(a,b) (!(a) != !(b))
static int get_imm_size(enum ImmType imm, int opsize, int memsize)
{
	switch (imm) {
	case M_NONE:
		return 0;
	case M_BYTE:
		return 1;
	case M_WORD:
		return 2;
	case M_THREE:
		return 3;
	case M_VORD:
		return opsize ? 4 : 2;
	case M_MEMORY:
		return memsize ? 4 : 2;
	case M_FAR:
		return memsize ? 6 : 4;
	default:
		assert(!"Invalid ImmType");
		return -1;
	}
}

static struct OpBasicInfo op_basic_info(int op) {
	struct OpBasicInfo basic;
	char byte = x86optab[op];
	basic.attrib = (byte>>4)&3;
	basic.modrm = !!(byte&8);
	basic.immed = byte&7;
	return basic;
}
#define op_basic_info_0f(op) op_basic_info(256+(op))

/* If sib is out of bounds, you can pass an arbitrary value. */
static int modrm_length(uint8_t modrm, uint8_t sib, int memsize)
{
	int len = 0;

	if (memsize) { /* 32-bit addressing */
		if (modrm < 0xC0 && (modrm & 7) == 4) {
			len += 1; /* sib byte */
			if (modrm < 0x40 && (sib & 7) == 5)
				len += 4;
		}
		if (modrm >= 0x80 && modrm < 0xC0)
			len += 4;
		else if ((modrm & 0xC7) == 5)
			len += 4;
	}
	else {
		if (modrm >= 0x80 && modrm < 0xC0)
			len += 2;
		else if ((modrm & 0xC7) == 6)
			len += 2;
	}

	if (modrm >= 0x40 && modrm < 0x80)
		len += 1;

	return len;
}

#define CHECK_INDEX(x,y) if(x > MAXLEN_X86-y) return 1
int dovzhyna_decode(struct OpState *op, uint8_t* data, int bits32)
{
	op->index = 0;
	op->pfx_rep = op->pfx_seg = op->pfx_opsize = op->pfx_memsize = 0;

	uint8_t code = 0;
sproc_init:
	CHECK_INDEX(op->index, 1);
	code = data[op->index++];
	op->opcode = code;

	op->basic = op_basic_info(code);
	if (op->basic.attrib == A_PREFIX) {
		switch (code) {
		case 0xF0: // LOCK
		case 0xF2: // REPNE
		case 0xF3: // REP
			op->pfx_rep = code; break;
		case 0x26: // ES
		case 0x2E: // CS
		case 0x36: // SS
		case 0x3E: // DS
		case 0x64: // FS
		case 0x65: // GS
			op->pfx_seg = code; break;
		case 0x66: // operand size prefix
			op->pfx_opsize = code; break;
		case 0x67: // address size prefix
			op->pfx_memsize = code; break;
		}

		goto sproc_init;
	}

	if (code == 0x0F) { /* 2-byte opcode prefix */
		CHECK_INDEX(op->index, 1);
		code = data[op->index++];
		op->opcode = (op->opcode << 8) | code;
		op->basic = op_basic_info_0f(code);

		if (op->basic.attrib == A_PREFIX) {
			CHECK_INDEX(op->index, 1);
			code = data[op->index++];
			if (op->opcode == 0x0F38) {
				op->basic = (struct OpBasicInfo){ A_NONE, 1, M_NONE };
			}
			else if (op->opcode == 0x0F3A) {
				op->basic = (struct OpBasicInfo){ A_NONE, 1, M_BYTE };
				// 66 0f 3a 4a/4b/4c - don't have immed, but only available
				// using (E)VEX form
			}
			op->opcode = (op->opcode << 8) | code;
		}

		if (op->basic.attrib == A_UD) {
			return 1;
		}
	}

	if (op->basic.modrm) {
		op->modrm_off = op->index;
		CHECK_INDEX(op->index, 1);
		uint8_t modrm = data[op->index++];
		uint8_t sib = op->index != MAXLEN_X86 ? data[op->index] : 0;

		int len = modrm_length(modrm, sib, lxor(bits32, op->pfx_memsize));
		CHECK_INDEX(op->index, len);
		op->index += len;

		switch (op->opcode) {
		case 0xC5: /* LDS (VEX 2-byte) */
		case 0xC4: /* LES (VEX 3-byte) */
		case 0x62: /* BOUND (EVEX 4-byte) */
			if ((modrm & 0xC0) == 0xC0)
				return 1; /* Unsupported for now */
			break;
		case 0x8F: /* Grp1A (XOP prefix) */
			if ((modrm & 0x38) != 0) /* reg != /0 */
				return 1; /* Unsupported */
			break;
		case 0xF6: /* Grp3 rm8 [imm8] */
		case 0xF7: /* Grp3 rm32 [imm32] */
			/* Unlike the rest of instructions in this group, /0 (TEST)
			 * has an immediate operand. /1 is actually an alias to /0,
			 * but Intel won't tell you this. In the table, these are
			 * encoded according to /0 and /1, so for everything else we
			 * have to set immed to none. */
			if ((modrm & 0x38) > 0x10) /* reg > /1 */
				op->basic.immed = M_NONE;
			break;
		}
	}

	if (op->basic.immed) {
		op->imm_off = op->index;
		op->index += get_imm_size(op->basic.immed, lxor(bits32, op->pfx_opsize), lxor(bits32, op->pfx_memsize));
		CHECK_INDEX(op->index, 0);
	}

	return 0;
}
