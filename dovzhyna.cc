#include <cassert>
#include <cstring>
#include "dovzhyna.hh"

#define _DOVZHYNA_CC_INCLUDE
#include "op_basic_info.hh"
#include "op_basic_info_0f.hh"

namespace dovzhyna {
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
	
	int decode(OpState&op, uint8_t* data, bool bits32) {
		memcpy(op.data, data, 15);
		op.index = 0;
		op.grp1 = op.grp2 = op.grp3 = op.grp4 = -1;
		op.bits32 = bits32;
		
		uint8_t code = 0;
	sproc_init:
		code = op.data[op.index++];
		op.opcode = code;

		if (op_basic_info[code].attrib == A_PREFIX) {
			switch (code) {
			case 0xF0:
			case 0xF2:
			case 0xF3:
				op.grp1 = code; break;
			case 0x26:
			case 0x2E:
			case 0x36:
			case 0x3E:
			case 0x64:
			case 0x65:
				op.grp2 = code; break;
			case 0x66:
				op.grp3 = code; break;
			case 0x67:
				op.grp4 = code; break;
			case 0x0F:
				goto sproc_cont;
			}
			
			goto sproc_init;
		}
		
		// not a prefix
		op.basic = op_basic_info[code];

		goto sproc_modrm;
		
	sproc_cont:
		code = op.data[op.index++];
		op.opcode = (op.opcode << 8) | code;
		op.basic = op_basic_info_0f[code];

		if (op.basic.attrib == A_PREFIX) {
			code = op.data[op.index++];
			if (op.opcode == 0x0F38) {
				op.basic = { A_NONE, true, M_NONE };
			}
			else if (op.opcode == 0x0F3A) {
				op.basic = { A_NONE, true, M_BYTE };
				// 66 0f 3a 4a/4b/4c - don't have immed, but only available
				// using (E)VEX form
			}
			op.opcode = (op.opcode << 8) | code;
		}

		if (op.basic.attrib == A_UD) {
			return S_ERROR;
		}
		
		goto sproc_modrm;
	
	sproc_modrm:
		if (op.basic.modrm) {
			uint8_t modrm = op.data[op.index++];
			op.modrm = modrm;

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
			
			goto sproc_grpfixup;
		}
		
		goto sproc_immed;
		
	sproc_grpfixup:
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
		
		goto sproc_immed;
	
	sproc_immed:
		if (op.basic.immed) {
			op.imm = op.index;
			op.index += get_imm_size(op.basic.immed, op.bits32 != (op.grp3 != -1), op.bits32 != (op.grp4 != -1));
		}
		
		return S_SUCCESS;
	}
}
