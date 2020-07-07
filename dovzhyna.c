#include <assert.h>
#include <string.h>
#include "dovzhyna.h"

#include "x86optab.h"

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

#define CHECK_INDEX(x,y) if(x > 15-y) return S_ERROR
int dovzhyna_decode(struct OpState *op, uint8_t* data, int bits32)
{
	memcpy(op->data, data, 15);
	op->index = 0;
	op->pfx_rep = op->pfx_seg = op->pfx_opsize = op->pfx_memsize = -1;
	op->bits32 = bits32;
	
	uint8_t code = 0;
sproc_init:
	CHECK_INDEX(op->index, 1);
	code = op->data[op->index++];
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
		case 0x0F: // 2-byte opcode prefix
			goto sproc_cont;
		}
		
		goto sproc_init;
	}
	
	// not a prefix
	goto sproc_modrm;
	
sproc_cont:
	CHECK_INDEX(op->index, 1);
	code = op->data[op->index++];
	op->opcode = (op->opcode << 8) | code;
	op->basic = op_basic_info_0f(code);

	if (op->basic.attrib == A_PREFIX) {
		CHECK_INDEX(op->index, 1);
		code = op->data[op->index++];
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
		return S_ERROR;
	}
	
sproc_modrm:
	if (op->basic.modrm) {
		CHECK_INDEX(op->index, 1);
		uint8_t modrm = op->data[op->index++];
		op->modrm = modrm;

		if (op->bits32 != (op->pfx_memsize != -1)) { // 32-bit addressing
			if (modrm < 0xC0 && (modrm & 7) == 4) {
				CHECK_INDEX(op->index, 1);
				uint8_t sib = op->data[op->index++];
				if (modrm < 0x40 && (sib & 7) == 5) {
					CHECK_INDEX(op->index, 4);
					op->index += 4;
				}
			}
			if (modrm >= 0x80 && modrm < 0xC0) {
				CHECK_INDEX(op->index, 4);
				op->index += 4;
			}
			else if ((modrm & 0xC7) == 5) {
				CHECK_INDEX(op->index, 4);
				op->index += 4;
			}
		}
		else {
			if (modrm >= 0x80 && modrm < 0xC0) {
				CHECK_INDEX(op->index, 2);
				op->index += 2;
			}
			else if ((modrm & 0xC7) == 6) {
				CHECK_INDEX(op->index, 2);
				op->index += 2;
			}
		}

		if (modrm >= 0x40 && modrm < 0x80) {
			CHECK_INDEX(op->index, 1);
			op->index += 1;
		}
		
		goto sproc_grpfixup;
	}
	
	goto sproc_immed;
	
sproc_grpfixup:
	if (op->basic.attrib == A_GRP) {
		// fixup for some of the Grp's
		switch (op->opcode) {
		case 0xF6:
		case 0xF7:
			if (op->modrm & 0x38) {
				op->basic.immed = M_NONE;
			}
			break;
		}
	}

sproc_immed:
	if (op->basic.immed) {
		op->imm = op->index;
		op->index += get_imm_size(op->basic.immed, op->bits32 != (op->pfx_opsize != -1), op->bits32 != (op->pfx_memsize != -1));
		CHECK_INDEX(op->index, 0);
	}
	
	return S_SUCCESS;
}
