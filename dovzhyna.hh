#include <stdint.h>
namespace dovzhyna {
	struct OpBasicInfo {
		int attrib;
		bool modrm; // Here only distinction between M_NONE and others matters
		int immed;
	};

	enum {
		A_NONE,
		A_PREFIX,
		A_MULTIBYTE,
		A_GRP, // special group handling required
		A_UD, // undefined instruction.
		// NOTE: No, UD2 is not an undefined instruction, it is defined to be an undefined instruction.
	};

	enum {
		M_NONE,
		M_BYTE,
		M_WORD,
		M_VORD, // word or dword [or qword] depending on operand size
		M_ZORD = M_VORD, // word or dword depending on operand size (for now equal to VORD)
		M_DWORD,
		M_YORD = M_DWORD, // dword [or qword]
		M_MEMORY, // in modrm field, it means a generic pointer to data of unspecified size
				  // in immed field, it means that immediate value is of address size, and is actually an offset without modrm
		M_DVORD = M_MEMORY, // used only by BOUND instruction - two words/dwords depending on opsize (also, has to be in memory)
		M_MM = M_MEMORY,
		M_XMM = M_MEMORY, // XMM or YMM or ZMM
		M_REG = M_MEMORY, // modrm can only point to register

		M_THREE, // WORD+BYTE, used for enter instruction

		M_FAR, // far address (M_WORD + M_MEMORY)
		M_COPROC, // for fpu instructions
		
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