#ifndef DOVZHYNA_C_INCLUDE_
#error "do not include this file"
#endif
// NOTE: Originally this table was supposed to only cover unprefixed 2-byte
// instructions, but then I realized that there are no instructions which 
// have different immed encoding when different prefix is used.
// Counterexample: F3 0F B8 (POPCNT) vs 0F B8 (JMPE)
// However, I don't care about 0F B8, because that's IA-64.
// The downside to this approach is that many UD instructions are marked
// as valid. This is not a big deal, if Intel introduces new instructions
// they will probably be (E)VEXed, or follow the aforementioned pattern.
static struct OpBasicInfo op_basic_info_0f[] = {
	{ A_NONE, true, M_NONE }, // 00 Grp6 
	{ A_NONE, true, M_NONE }, // 01 Grp7
	{ A_NONE, true, M_NONE }, // 02 LAR
	{ A_NONE, true, M_NONE }, // 03 LSL
	{ A_UD }, // 04
	{ A_NONE, false, M_NONE }, // 05 SYSCALL
	{ A_NONE, false, M_NONE }, // 06 CLTS
	{ A_NONE, false, M_NONE }, // 07 SYSRET
	{ A_NONE, false, M_NONE }, // 08 INVD
	{ A_NONE, false, M_NONE }, // 09 WBINVD
	{ A_UD }, // 0A
	{ A_NONE, false, M_NONE }, // 0B UD2
	{ A_UD }, // 0C
	{ A_NONE, true, M_NONE }, // 0D PREFETCHW
	{ A_UD }, // 0E
	{ A_UD }, // 0F
	{ A_NONE, true, M_NONE }, // 10 MOVUPS r, rm
	{ A_NONE, true, M_NONE }, // 11 MOVUPS rm, r
	{ A_NONE, true, M_NONE }, // 12 MOVLPS r, m
	{ A_NONE, true, M_NONE }, // 13 MOVLPS m, r
	{ A_NONE, true, M_NONE }, // 14 UNPCKLPS r, rm
	{ A_NONE, true, M_NONE }, // 15 UNPCKHPS r, rm
	{ A_NONE, true, M_NONE }, // 16 MOVHPS r, m
	{ A_NONE, true, M_NONE }, // 17 MOVHPS m, r
	{ A_NONE, true, M_NONE }, // 18 Prefetch Grp16
	{ A_UD }, // 19 Reserved-NOP
	{ A_NONE, true, M_NONE }, // 1A BNDLDX
	{ A_NONE, true, M_NONE }, // 1B BNDSTX
	{ A_UD }, // 1C Reserved-NOP
	{ A_UD }, // 1D Reserved-NOP
	{ A_UD }, // 1E Reserved-NOP
	{ A_NONE, true, M_NONE }, // 1F NOP r/m32
	{ A_NONE, true, M_NONE }, // 20 MOV r, cr
	{ A_NONE, true, M_NONE }, // 21 MOV r, dr
	{ A_NONE, true, M_NONE }, // 22 MOV cr, r
	{ A_NONE, true, M_NONE }, // 23 MOV dr, r
	{ A_UD },{ A_UD },{ A_UD },{ A_UD }, // 24 25 26 27
	{ A_NONE, true, M_NONE }, // 28 MOVAPS r, rm
	{ A_NONE, true, M_NONE }, // 29 MOVAPS rm, r
	{ A_NONE, true, M_NONE }, // 2A CTPI2PS r, rm
	{ A_NONE, true, M_NONE }, // 2B MOVNTPS m, r
	{ A_NONE, true, M_NONE }, // 2C CVTTPS2PI rm, r
	{ A_NONE, true, M_NONE }, // 2D CVTPS2PI rm, r
	{ A_NONE, true, M_NONE }, // 2E UCOMISS r, rm
	{ A_NONE, true, M_NONE }, // 2F COMISS r, rm

	{ A_NONE, false, M_NONE }, // 30 WRMSR
	{ A_NONE, false, M_NONE }, // 31 RDTSC
	{ A_NONE, false, M_NONE }, // 32 RDMSR
	{ A_NONE, false, M_NONE }, // 33 RDPMC
	{ A_NONE, false, M_NONE }, // 34 SYSENTER
	{ A_NONE, false, M_NONE }, // 35 SYSEXIT
	{ A_UD }, // 36
	{ A_NONE, false, M_NONE }, // 37 GETSEC
	{ A_PREFIX }, // 38 3-byte
	{ A_UD }, // 39
	{ A_PREFIX }, // 3A 3-byte
	{ A_UD },{ A_UD },{ A_UD },{ A_UD },{ A_UD }, // 3B 3C 3D 3E 3F
	// 40-4F CMOVEcc r32, rm32
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE }, // 50 MOVMSKPS r32, r
	{ A_NONE, true, M_NONE }, // 51 SQRTPS r, rm
	{ A_NONE, true, M_NONE }, // 52 RSQRTPS r, rm
	{ A_NONE, true, M_NONE }, // 53 RCPPS r, rm
	{ A_NONE, true, M_NONE }, // 54 ANDPS r, rm
	{ A_NONE, true, M_NONE }, // 55 ANDNPS r, rm
	{ A_NONE, true, M_NONE }, // 56 ORPS r, rm
	{ A_NONE, true, M_NONE }, // 57 XORPS r, rm
	{ A_NONE, true, M_NONE }, // 58 ADDPS, rm
	{ A_NONE, true, M_NONE }, // 59 MULPS r, rm
	{ A_NONE, true, M_NONE }, // 5A CVTPS2PD r, rm
	{ A_NONE, true, M_NONE }, // 5B CVTDQ2PS r, rm
	{ A_NONE, true, M_NONE }, // 5C SUBPS r, rm
	{ A_NONE, true, M_NONE }, // 5D MINPS r, rm
	{ A_NONE, true, M_NONE }, // 5E DIVPS r, rm
	{ A_NONE, true, M_NONE }, // 5F MAXPS r, rm

	{ A_NONE, true, M_NONE }, // 60 PUNPCKLBW r, rm
	{ A_NONE, true, M_NONE }, // 61 PUNPCKLWD r, rm
	{ A_NONE, true, M_NONE }, // 62 PUNPCKLDQ r, rm
	{ A_NONE, true, M_NONE }, // 63 PACKSSWB r, rm
	{ A_NONE, true, M_NONE }, // 64 PCMPGTB r, rm
	{ A_NONE, true, M_NONE }, // 65 PCMPGTW r, rm
	{ A_NONE, true, M_NONE }, // 66 PCMPGTD r, rm
	{ A_NONE, true, M_NONE }, // 67 PACKUSWB r, rm
	{ A_NONE, true, M_NONE }, // 68 PUNPCKHBW r, rm
	{ A_NONE, true, M_NONE }, // 69 PUNPCKHWD r, rm
	{ A_NONE, true, M_NONE }, // 6A PUNPCKHDQ r, rm
	{ A_NONE, true, M_NONE }, // 6B PACKSSDW r, rm
	{ A_NONE, true, M_NONE }, // 6C PUNPCKLQDQ r, rm (prefix 66)
	{ A_NONE, true, M_NONE }, // 6D PUNPCKHQDQ r, rm (prefix 66)
	{ A_NONE, true, M_NONE }, // 6E MOVD r, rm
	{ A_NONE, true, M_NONE }, // 6F MOVQ r, rm

	{ A_NONE, true, M_NONE }, // 70 PSHUFW r, rm
	{ A_NONE, true, M_BYTE }, // 71 Grp12
	{ A_NONE, true, M_BYTE }, // 72 Grp13
	{ A_NONE, true, M_BYTE }, // 73 Grp14
	{ A_NONE, true, M_NONE }, // 74 PCMPEQB r, rm
	{ A_NONE, true, M_NONE }, // 75 PCMPEQW r, rm
	{ A_NONE, true, M_NONE }, // 76 PCMPEQD r, rm
	{ A_NONE, false, M_NONE }, // 77 EMMS
	{ A_NONE, true, M_NONE }, // 78 VM_READ
	{ A_NONE, true, M_NONE }, // 79 VM_WRITE
	{ A_UD }, // 7A
	{ A_UD }, // 7B
	{ A_NONE, true, M_NONE }, // 7C HADDPD r, rm (prefix 66)
	{ A_NONE, true, M_NONE }, // 7D HSUBPD r, rm (prefix 66)
	{ A_NONE, true, M_NONE }, // 7E MOVD rm, r
	{ A_NONE, true, M_NONE }, // 7F MOVQ rm, r
	// 80-8F Jcc NEAR
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	{ A_NONE, false, M_VORD },
	// 90-9F SETcc rm8
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },
	{ A_NONE, true, M_NONE },

	{ A_NONE, false, M_NONE }, // A0 PUSH FS
	{ A_NONE, false, M_NONE }, // A1 POP FS
	{ A_NONE, false, M_NONE }, // A2 CPUID
	{ A_NONE, true, M_NONE }, // A3 BT rm32, r32
	{ A_NONE, true, M_BYTE }, // A4 SHLD rm32, r32, imm8
	{ A_NONE, true, M_NONE }, // A5 SHLD rm32, r32, cl
	{ A_UD }, // A6
	{ A_UD }, // A7
	{ A_NONE, false, M_NONE }, // A8 PUSH GS
	{ A_NONE, false, M_NONE }, // A9 POP GS
	{ A_NONE, false, M_NONE }, // AA RSM
	{ A_NONE, true, M_NONE }, // AB BTS rm32, r32
	{ A_NONE, true, M_BYTE }, // AC SHRD rm32, r32, imm8
	{ A_NONE, true, M_NONE }, // AD SHRD rm32, r32, cl
	{ A_NONE, true, M_NONE }, // AE Grp15
	{ A_NONE, true, M_NONE }, // AF IMUL r32, rm32

	{ A_NONE, true, M_NONE }, // B0 CMPXCHG rm8, r8
	{ A_NONE, true, M_NONE }, // B1 CMPXCHG rm32, r32
	{ A_NONE, true, M_NONE }, // B2 LSS
	{ A_NONE, true, M_NONE }, // B3 BTS rm32, r32
	{ A_NONE, true, M_NONE }, // B4 LFS
	{ A_NONE, true, M_NONE }, // B5 LGS
	{ A_NONE, true, M_NONE }, // B6 MOVZX r8, rm8
	{ A_NONE, true, M_NONE }, // B7 MOVZX r32, rm16
	{ A_NONE, true, M_NONE }, // B8 POPCNT r32, rm32 (prefix F3. unprefixed is related to IA-64)
	{ A_NONE, true, M_NONE }, // B9 UD1 (Grp10)
	{ A_NONE, true, M_BYTE }, // BA Grp8 rm32, imm8
	{ A_NONE, true, M_NONE }, // BB BTC rm32, r32
	{ A_NONE, true, M_NONE }, // BC BSF r32, rm32
	{ A_NONE, true, M_NONE }, // BD BSR r32, rm32
	{ A_NONE, true, M_NONE }, // BE MOVSX r8, rm8
	{ A_NONE, true, M_NONE }, // BF MOVSX r32, rm16

	{ A_NONE, true, M_NONE }, // C0 XADD rm8, r8
	{ A_NONE, true, M_NONE }, // C1 XADD rm32, r32
	{ A_NONE, true, M_BYTE }, // C2 CMPPS r, rm, imm8
	{ A_NONE, true, M_NONE }, // C3 MOVNTI m32, r32
	{ A_NONE, true, M_BYTE}, // C4 PINSRW r, r32/m16, imm8
	{ A_NONE, true, M_BYTE }, // C5 PEXTRW r32, r(m), imm8
	{ A_NONE, true, M_BYTE }, // C6 SHUFPS r, rm, imm8
	{ A_NONE, true, M_NONE }, // C7 Grp9
	{ A_NONE, false, M_NONE }, // C8 BSWAP eax
	{ A_NONE, false, M_NONE }, // C9 BSWAP ecx
	{ A_NONE, false, M_NONE }, // CA BSWAP edx
	{ A_NONE, false, M_NONE }, // CB BSWAP ebx
	{ A_NONE, false, M_NONE }, // CC BSWAP esp
	{ A_NONE, false, M_NONE }, // CD BSWAP ebp
	{ A_NONE, false, M_NONE }, // CE BSWAP esi
	{ A_NONE, false, M_NONE }, // CF BSWAP edi

	{ A_NONE, true, M_NONE }, // D0 ADDSUBPD r, rm (prefixed 66)
	{ A_NONE, true, M_NONE }, // D1 PSRLW r, rm
	{ A_NONE, true, M_NONE }, // D2 PSRLD r, rm
	{ A_NONE, true, M_NONE }, // D3 PSRLQ r, rm
	{ A_NONE, true, M_NONE }, // D4 PADDQ r, rm
	{ A_NONE, true, M_NONE }, // D5 PMULLW r, rm
	{ A_NONE, true, M_NONE }, // D6 MOVQ rm, r (prefixed 66)
	{ A_NONE, true, M_NONE }, // D7 PMOVMSKB r32, r(m)
	{ A_NONE, true, M_NONE }, // D8 PSUBUSB r, rm
	{ A_NONE, true, M_NONE }, // D9 PSUBUSW r, rm
	{ A_NONE, true, M_NONE }, // DA PMINUB r, rm
	{ A_NONE, true, M_NONE }, // DB PAND r, rm
	{ A_NONE, true, M_NONE }, // DC PADDUSB r, rm
	{ A_NONE, true, M_NONE }, // DD PADDUSW r, rm
	{ A_NONE, true, M_NONE }, // DE PMAXUB r, rm
	{ A_NONE, true, M_NONE }, // DF PADDN r, rm

	{ A_NONE, true, M_NONE }, // E0 PAVGB r, rm
	{ A_NONE, true, M_NONE }, // E1 PSRAW r, rm
	{ A_NONE, true, M_NONE }, // E2 PSRAD r, rm
	{ A_NONE, true, M_NONE }, // E3 PAVGW r, rm
	{ A_NONE, true, M_NONE }, // E4 PMULHUW r, rm
	{ A_NONE, true, M_NONE }, // E5 PMULHW r, rm
	{ A_NONE, true, M_NONE }, // E6 CVTTPD2DQ r, rm (prefixed 66)
	{ A_NONE, true, M_NONE }, // E7 MOVNTQ m, r
	{ A_NONE, true, M_NONE }, // E8 PSUBSB r, rm
	{ A_NONE, true, M_NONE }, // E9 PSUBSW r, rm
	{ A_NONE, true, M_NONE }, // EA PMINSW r, rm
	{ A_NONE, true, M_NONE }, // EB POR r, rm
	{ A_NONE, true, M_NONE }, // EC PADDSB r, rm
	{ A_NONE, true, M_NONE }, // ED PADDSW r, rm
	{ A_NONE, true, M_NONE }, // EE PMAXSW r, rm
	{ A_NONE, true, M_NONE }, // EF PXOR r, rm

	{ A_NONE, true, M_NONE }, // F0 LDDQU r, m (prefix F2)
	{ A_NONE, true, M_NONE }, // F1 PSLLW r, rm
	{ A_NONE, true, M_NONE }, // F2 PSLLD r, rm
	{ A_NONE, true, M_NONE }, // F3 PSLLQ r, rm
	{ A_NONE, true, M_NONE }, // F4 PMULUDQ r, rm
	{ A_NONE, true, M_NONE }, // F5 PMADDWD r, rm
	{ A_NONE, true, M_NONE }, // F6 PSADBW r, rm
	{ A_NONE, true, M_NONE }, // F7 MASKMOVQ r, r(m)
	{ A_NONE, true, M_NONE }, // F8 PSUBB r, rm
	{ A_NONE, true, M_NONE }, // F9 PSUBW r, rm
	{ A_NONE, true, M_NONE }, // FA PSUBD r, rm
	{ A_NONE, true, M_NONE }, // FB PSUBQ r, rm
	{ A_NONE, true, M_NONE }, // FC PADDB r, rm
	{ A_NONE, true, M_NONE }, // FD PADDW r, rm
	{ A_NONE, true, M_NONE }, // FE PADDD r, rm
	{ A_NONE, false, M_NONE }, // FF UD0
};
_Static_assert(256 == sizeof(op_basic_info_0f) / sizeof(struct OpBasicInfo), "op_basic_info_0f size error");
