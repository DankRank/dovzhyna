#include <cassert>
#include <cstring>
#include "dovzhyna.hh"

#define _DOVZHYNA_CC_INCLUDE
#include "op_basic_info.hh"
#include "op_basic_info_0f.hh"

namespace dovzhyna {
	static inline int get_prefix_grp(uint8_t c) {
		switch (c) {
		case 0xF0:
		case 0xF2:
		case 0xF3:
			return 0;
		case 0x26:
		case 0x2E:
		case 0x36:
		case 0x3E:
		case 0x64:
		case 0x65:
			return 1;
		case 0x66:
			return 2;
		case 0x67:
			return 3;
		}
		assert(!"not a prefix");
		return -1;
	}
	static inline int get_imm_size(ImmType imm, bool opsize, bool memsize) {
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
	int sproc_init(OpState&op) {
		uint8_t code = op.data[op.index];
		if (op_basic_info[code].attrib == A_PREFIX) {
			switch (get_prefix_grp(code)) {
			case 0: op.grp1 = code; break;
			case 1: op.grp2 = code; break;
			case 2: op.grp3 = code; break;
			case 3: op.grp4 = code; break;
			}
			++op.index;
			return S_INIT;
		}
		// not a prefix
		op.opcode = code;
		op.basic = op_basic_info[code];
		op.index++;

		if (op.basic.attrib == A_MULTIBYTE) {	
			return S_CONT;
		}

		return S_MODRM;
	}
	int sproc_cont(OpState&op) {
		uint8_t code = op.data[op.index];
		op.opcode = (op.opcode << 8) | code;
		op.basic = op_basic_info_0f[code];
		op.index++;

		if (op.basic.attrib == A_MULTIBYTE) {
			return S_CONT2;
		}

		if (op.basic.attrib == A_UD) {
			return S_ERROR;
		}

		return S_MODRM;
	}
	int sproc_cont2(OpState&op) {
		assert(!"NYI");
		return S_ERROR;
	}
	int sproc_modrm(OpState&op) {
		if (op.basic.modrm) {
			uint8_t modrm = op.data[op.index];
			op.modrm = modrm;
			op.index++;

			if (op.bits32 != (op.grp4 != -1)) { // 32-bit addressing
				if (modrm < 0xC0 && (modrm & 7) == 4) {
					op.index++; // skip sib
				}
				if (modrm >= 0x80 && modrm < 0xC0) {
					op.index += 4;
				}
				else if ((modrm & 0xC7) == 5) {
					op.index += 4;
				}
			}
			else {
				if (modrm >= 0x80 && modrm < 0xC0) {
					op.index += 2;
				}
				else if ((modrm & 0xC7) == 6) {
					op.index += 2;
				}
			}

			if (modrm >= 0x40 && modrm < 0x80) {
				op.index += 1;
			}
			return S_GRPFIXUP;
		}
		return S_IMMED;
	}
	int sproc_grpfixup(OpState&op) {
		if (op.basic.attrib == A_GRP) {
			// fixup for some of the Grp's
			switch (op.opcode) {
			case 0xF6:
			case 0xF7:
				if (op.modrm & 0x38) {
					op.basic.immed = M_NONE;
				}
				break;
			}
		}
		return S_IMMED;
	}
	int sproc_immed(OpState&op) {
		if (op.basic.immed) {
			op.imm = op.index;
			op.index += get_imm_size(op.basic.immed, op.bits32 != (op.grp3 != -1), op.bits32 != (op.grp4 != -1));
		}
		return S_DONE;
	}
	int(*sprocs[])(OpState&op) = {
		sproc_init,
		sproc_cont,
		sproc_cont2,
		sproc_modrm,
		sproc_grpfixup,
		sproc_immed,
	};
	int decode(OpState&op, uint8_t* data, bool bits32) {
		op.state = S_INIT;
		memcpy(op.data, data, 15);
		op.index = 0;
		op.grp1 = op.grp2 = op.grp3 = op.grp4 = -1;
		op.bits32 = bits32;
		while (op.state != S_DONE && op.state != S_ERROR) {
			op.state = sprocs[op.state](op);
		}
		return op.state;
	}
	
}