#include <stdint.h>
namespace dovzhyna {
	enum InsAttrib{
		A_NONE,
		A_PREFIX,
		A_MULTIBYTE,
		A_GRP, // special group handling required
		A_UD, // undefined instruction.
		// NOTE: No, UD2 is not an undefined instruction, it is defined to be an undefined instruction.
	};

	enum ImmType {
		M_NONE,
		M_BYTE, // 1 byte
		M_WORD, // 2 bytes
		M_THREE, // 3 bytes, used by ENTER instruction

		M_VORD, // word or dword [or qword] depending on operand size
		M_ZORD = M_VORD, // word or dword depending on operand size (for now equal to VORD)

		M_MEMORY, // address size
		M_FAR, // far address (M_WORD + M_MEMORY)
	};

	struct OpBasicInfo {
		InsAttrib attrib;
		bool modrm;
		ImmType immed;
	};

	struct OpState {
		int state;

		uint8_t data[15];
		int index;

		bool bits32;

		OpBasicInfo basic;
		int grp1, grp2, grp3, grp4;
		int opcode, modrm, imm;
		// imm is offset to immediate data
		
	};

	enum {
		S_INIT, // prefixes and initial op
		S_CONT, // continuation 0F xx
		S_CONT2, // continuation 0F 38/3A xx
		S_MODRM,
		S_GRPFIXUP,
		S_IMMED,
		S_DONE = -2 ,
		S_ERROR = -1
	};

	int decode(OpState&op, uint8_t* data, bool bits32);
}