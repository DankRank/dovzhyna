#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
enum InsAttrib{
	A_NONE,
	A_PREFIX,
	A_GRP, // special group handling required
	A_UD, // undefined instruction.
	// NOTE: No, UD2 is not an undefined instruction, it is defined to be an undefined instruction.
};

enum ImmType {
	M_NONE,
	M_BYTE, // 1 byte
	M_WORD, // 2 bytes
	M_THREE, // 3 bytes, used by ENTER instruction

	M_VORD, // word or dword depending on operand size

	M_MEMORY, // address size
	M_FAR, // far address (M_WORD + M_MEMORY)
};

struct OpBasicInfo {
	enum InsAttrib attrib;
	int modrm;
	enum ImmType immed;
};

struct OpState {
	uint8_t data[15];
	int index;

	int bits32;

	struct OpBasicInfo basic;
	int pfx_rep, pfx_seg, pfx_opsize, pfx_memsize;
	int opcode, modrm, imm;
	// imm is offset to immediate data
	
};

enum {
	S_SUCCESS = 0,
	S_ERROR = 1
};

int dovzhyna_decode(struct OpState *op, uint8_t* data, int bits32);

#ifdef __cplusplus
}
#endif
