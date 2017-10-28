#ifndef _DOVZHYNA_CC_INCLUDE
#error don't include this file
#endif
namespace dovzhyna {
	static OpBasicInfo op_basic_info[] = {
		{ A_NONE, true, M_NONE }, // 00 ADD rm8, r8
		{ A_NONE, true, M_NONE }, // 01 ADD rm32, r32
		{ A_NONE, true, M_NONE }, // 02 ADD r8, rm8
		{ A_NONE, true, M_NONE }, // 03 ADD r32, rm32
		{ A_NONE, false, M_BYTE }, // 04 ADD al, imm8
		{ A_NONE, false, M_ZORD }, // 05 ADD eax, imm32
		{ A_NONE, false, M_NONE }, // 06 PUSH ES
		{ A_NONE, false, M_NONE }, // 07 POP ES
		{ A_NONE, true, M_NONE }, // 08 OR rm8, r8
		{ A_NONE, true, M_NONE }, // 09 OR rm32, r32
		{ A_NONE, true, M_NONE }, // 0A OR r8, rm8
		{ A_NONE, true, M_NONE }, // 0B OR r32, rm32
		{ A_NONE, false, M_BYTE }, // 0C OR al, imm8
		{ A_NONE, false, M_ZORD }, // 0D OR eax, imm32
		{ A_NONE, false, M_NONE }, // 0E PUSH CS
		{ A_PREFIX }, // 0F 2-byte escape
		{ A_NONE, true, M_NONE }, // 10 ADC rm8, r8
		{ A_NONE, true, M_NONE }, // 11 ADC rm32, r32
		{ A_NONE, true, M_NONE }, // 12 ADC r8, rm8
		{ A_NONE, true, M_NONE }, // 13 ADC r32, rm32
		{ A_NONE, false, M_BYTE }, // 14 ADC al, imm8
		{ A_NONE, false, M_ZORD }, // 15 ADC eax, imm32
		{ A_NONE, false, M_NONE }, // 16 PUSH SS
		{ A_NONE, false, M_NONE }, // 17 POP SS
		{ A_NONE, true, M_NONE }, // 18 SBB rm8, r8
		{ A_NONE, true, M_NONE }, // 19 SBB rm32, r32
		{ A_NONE, true, M_NONE }, // 1A SBB r8, rm8
		{ A_NONE, true, M_NONE }, // 1B SBB r32, rm32
		{ A_NONE, false, M_BYTE }, // 1C SBB al, imm8
		{ A_NONE, false, M_ZORD }, // 1D SBB eax, imm32
		{ A_NONE, false, M_NONE }, // 1E PUSH DS
		{ A_NONE, false, M_NONE }, // 1F POP DS
		{ A_NONE, true, M_NONE }, // 20 AND rm8, r8
		{ A_NONE, true, M_NONE }, // 21 AND rm32, r32
		{ A_NONE, true, M_NONE }, // 22 AND r8, rm8
		{ A_NONE, true, M_NONE }, // 23 AND r32, rm32
		{ A_NONE, false, M_BYTE }, // 24 AND al, imm8
		{ A_NONE, false, M_ZORD }, // 25 AND eax, imm32
		{ A_PREFIX }, // 26 ES prefix
		{ A_NONE, false, M_NONE }, // 27 DAA
		{ A_NONE, true, M_NONE }, // 28 SUB rm8, r8
		{ A_NONE, true, M_NONE }, // 29 SUB rm32, r32
		{ A_NONE, true, M_NONE }, // 2A SUB r8, rm8
		{ A_NONE, true, M_NONE }, // 2B SUB r32, rm32
		{ A_NONE, false, M_BYTE }, // 2C SUB al, imm8
		{ A_NONE, false, M_ZORD }, // 2D SUB eax, imm32
		{ A_PREFIX }, // 2E CS prefix
		{ A_NONE, false, M_NONE }, // 2F DAS
		{ A_NONE, true, M_NONE }, // 30 XOR rm8, r8
		{ A_NONE, true, M_NONE }, // 31 XOR rm32, r32
		{ A_NONE, true, M_NONE }, // 32 XOR r8, rm8
		{ A_NONE, true, M_NONE }, // 33 XOR r32, rm32
		{ A_NONE, false, M_BYTE }, // 34 XOR al, imm8
		{ A_NONE, false, M_ZORD }, // 35 XOR eax, imm32
		{ A_PREFIX }, // 36 SS prefix
		{ A_NONE, false, M_NONE }, // 37 AAA
		{ A_NONE, true, M_NONE }, // 38 CMP rm8, r8
		{ A_NONE, true, M_NONE }, // 39 CMP rm32, r32
		{ A_NONE, true, M_NONE }, // 3A CMP r8, rm8
		{ A_NONE, true, M_NONE }, // 3B CMP r32, rm32
		{ A_NONE, false, M_BYTE }, // 3C CMP al, imm8
		{ A_NONE, false, M_ZORD }, // 3D CMP eax, imm32
		{ A_PREFIX }, // 3E DS prefix
		{ A_NONE, false, M_NONE }, // 3F AAS
		{ A_NONE, false, M_NONE }, // 40 INC eax
		{ A_NONE, false, M_NONE }, // 41 INC ecx
		{ A_NONE, false, M_NONE }, // 42 INC edx
		{ A_NONE, false, M_NONE }, // 43 INC ebx
		{ A_NONE, false, M_NONE }, // 44 INC esp
		{ A_NONE, false, M_NONE }, // 45 INC ebp
		{ A_NONE, false, M_NONE }, // 46 INC esi
		{ A_NONE, false, M_NONE }, // 47 INC edi
		{ A_NONE, false, M_NONE }, // 48 DEC eax
		{ A_NONE, false, M_NONE }, // 49 DEC ecx
		{ A_NONE, false, M_NONE }, // 4A DEC edx
		{ A_NONE, false, M_NONE }, // 4B DEC ebx
		{ A_NONE, false, M_NONE }, // 4C DEC esp
		{ A_NONE, false, M_NONE }, // 4D DEC ebp
		{ A_NONE, false, M_NONE }, // 4E DEC esi
		{ A_NONE, false, M_NONE }, // 4F DEC edi
		{ A_NONE, false, M_NONE }, // 50 PUSH eax
		{ A_NONE, false, M_NONE }, // 51 PUSH ecx
		{ A_NONE, false, M_NONE }, // 52 PUSH edx
		{ A_NONE, false, M_NONE }, // 53 PUSH ebx
		{ A_NONE, false, M_NONE }, // 54 PUSH esp
		{ A_NONE, false, M_NONE }, // 55 PUSH ebp
		{ A_NONE, false, M_NONE }, // 56 PUSH esi
		{ A_NONE, false, M_NONE }, // 57 PUSH edi
		{ A_NONE, false, M_NONE }, // 58 POP eax
		{ A_NONE, false, M_NONE }, // 59 POP ecx
		{ A_NONE, false, M_NONE }, // 5A POP edx
		{ A_NONE, false, M_NONE }, // 5B POP ebx
		{ A_NONE, false, M_NONE }, // 5C POP esp
		{ A_NONE, false, M_NONE }, // 5D POP ebp
		{ A_NONE, false, M_NONE }, // 5E POP esi
		{ A_NONE, false, M_NONE }, // 5F POP edi
		{ A_NONE, false, M_NONE }, // 60 PUSHAD
		{ A_NONE, false, M_NONE }, // 61 POPAD
		{ A_NONE, true, M_NONE }, // 62 BOUND
		{ A_NONE, true, M_NONE }, // 63 ARPL
		{ A_PREFIX }, // 64 FS prefix
		{ A_PREFIX }, // 65 GS prefix
		{ A_PREFIX }, // 66 Operand-size prefix
		{ A_PREFIX }, // 67 Address-size prefix
		{ A_NONE, false, M_ZORD }, // 68 PUSH i32
		{ A_NONE, true, M_ZORD }, // 69 IMUL i32
		{ A_NONE, false, M_BYTE }, // 6A PUSH i8
		{ A_NONE, true, M_BYTE }, // 6B IMUL i8
		{ A_NONE, false, M_NONE }, // 6C INSB
		{ A_NONE, false, M_NONE }, // 6D INSD
		{ A_NONE, false, M_NONE }, // 6E OUTSB
		{ A_NONE, false, M_NONE }, // 6F OUTSD
		{ A_NONE, false, M_BYTE }, // 70 JO
		{ A_NONE, false, M_BYTE }, // 71 JNO
		{ A_NONE, false, M_BYTE }, // 72 JB/JNAE/JC
		{ A_NONE, false, M_BYTE }, // 73 JNB/JAE/JNC
		{ A_NONE, false, M_BYTE }, // 74 JZ/JE
		{ A_NONE, false, M_BYTE }, // 75 JNZ/JNE
		{ A_NONE, false, M_BYTE }, // 76 JBE/JNA
		{ A_NONE, false, M_BYTE }, // 77 JNBE/JA
		{ A_NONE, false, M_BYTE }, // 78 JS
		{ A_NONE, false, M_BYTE }, // 79 JNS
		{ A_NONE, false, M_BYTE }, // 7A JP/JPE
		{ A_NONE, false, M_BYTE }, // 7B JNP/JPO
		{ A_NONE, false, M_BYTE }, // 7C JL/JNGE
		{ A_NONE, false, M_BYTE }, // 7D JNL/JGE
		{ A_NONE, false, M_BYTE }, // 7E JLE/JNG
		{ A_NONE, false, M_BYTE }, // 7F JNLE/JG
		{ A_NONE, true, M_BYTE }, // 80 Grp1 rm8, imm8
		{ A_NONE, true, M_ZORD }, // 81 Grp1 rm32, imm32
		{ A_NONE, true, M_BYTE }, // 82 Grp1 rm8, imm8 (duplicate of 80, #UD in long mode)
		{ A_NONE, true, M_BYTE }, // 83 Grp1 rm32, imm8
		{ A_NONE, true, M_NONE }, // 84 TEST rm8, r8
		{ A_NONE, true, M_NONE }, // 85 TEST rm32, r32
		{ A_NONE, true, M_NONE }, // 86 XCHG rm8, r8
		{ A_NONE, true, M_NONE }, // 87 XCHG rm32, r32
		{ A_NONE, true, M_NONE }, // 88 MOV rm8, r8
		{ A_NONE, true, M_NONE }, // 89 MOV rm32, r32
		{ A_NONE, true, M_NONE }, // 8A MOV r8, rm8
		{ A_NONE, true, M_NONE }, // 8B MOV r32, rm32
		{ A_NONE, true, M_NONE }, // 8C MOV rm32, s16
		{ A_NONE, true, M_NONE }, // 8D LEA r32, mem
		{ A_NONE, true, M_NONE }, // 8E MOV s16, rm16
		{ A_NONE, true, M_NONE }, // 8F Grp1A (r=0 POP, otherwise #UD) rm32
		{ A_NONE, false, M_NONE }, // 90 NOP
		{ A_NONE, false, M_NONE }, // 91 XCHG eax,ecx
		{ A_NONE, false, M_NONE }, // 92 XCHG eax,edx
		{ A_NONE, false, M_NONE }, // 93 XCHG eax,ebx
		{ A_NONE, false, M_NONE }, // 94 XCHG eax,esp
		{ A_NONE, false, M_NONE }, // 95 XCHG eax,ebp
		{ A_NONE, false, M_NONE }, // 96 XCHG eax,esi
		{ A_NONE, false, M_NONE }, // 97 XCHG eax,edi
		{ A_NONE, false, M_NONE }, // 98 CBW
		{ A_NONE, false, M_NONE }, // 99 CWD
		{ A_NONE, false, M_FAR }, // 9A CALL far
		{ A_NONE, false, M_NONE }, // 9B FWAIT
		{ A_NONE, false, M_NONE }, // 9C PUSHFD
		{ A_NONE, false, M_NONE }, // 9D POPFD
		{ A_NONE, false, M_NONE }, // 9E SAHF
		{ A_NONE, false, M_NONE }, // 9F LAHF
		{ A_NONE, false, M_MEMORY }, // A0 MOV al, mem8
		{ A_NONE, false, M_MEMORY }, // A1 MOV eax, mem32
		{ A_NONE, false, M_MEMORY }, // A2 MOV mem8, al
		{ A_NONE, false, M_MEMORY }, // A3 MOV mem32, eax
		{ A_NONE, false, M_NONE }, // A4 MOVSB
		{ A_NONE, false, M_NONE }, // A5 MOVSD
		{ A_NONE, false, M_NONE }, // A6 CMPSB
		{ A_NONE, false, M_NONE }, // A7 CMPSD
		{ A_NONE, false, M_BYTE }, // A8 TEST al, imm8
		{ A_NONE, false, M_ZORD }, // A9 TEST eax, imm32
		{ A_NONE, false, M_NONE }, // AA STOSB
		{ A_NONE, false, M_NONE }, // AB STOSD
		{ A_NONE, false, M_NONE }, // AC LODSB
		{ A_NONE, false, M_NONE }, // AD LODSD
		{ A_NONE, false, M_NONE }, // AE SCASB
		{ A_NONE, false, M_NONE }, // AF SCASD
		{ A_NONE, false, M_BYTE }, // B0 MOV al, imm8
		{ A_NONE, false, M_BYTE }, // B1 MOV cl, imm8
		{ A_NONE, false, M_BYTE }, // B2 MOV dl, imm8
		{ A_NONE, false, M_BYTE }, // B3 MOV bl, imm8
		{ A_NONE, false, M_BYTE }, // B4 MOV ah, imm8
		{ A_NONE, false, M_BYTE }, // B5 MOV ch, imm8
		{ A_NONE, false, M_BYTE }, // B6 MOV dh, imm8
		{ A_NONE, false, M_BYTE }, // B7 MOV bh, imm8
		{ A_NONE, false, M_VORD }, // B8 MOV eax, imm32
		{ A_NONE, false, M_VORD }, // B9 MOV ecx, imm32
		{ A_NONE, false, M_VORD }, // BA MOV edx, imm32
		{ A_NONE, false, M_VORD }, // BB MOV ebx, imm32
		{ A_NONE, false, M_VORD }, // BC MOV esp, imm32
		{ A_NONE, false, M_VORD }, // BD MOV ebp, imm32
		{ A_NONE, false, M_VORD }, // BE MOV esi, imm32
		{ A_NONE, false, M_VORD }, // BF MOV edi, imm32
		{ A_NONE, true, M_BYTE }, // C0 Grp2 rm8, imm8
		{ A_NONE, true, M_BYTE }, // C1 Grp2 rm32, imm8
		{ A_NONE, false, M_WORD }, // C2 RETN imm16
		{ A_NONE, false, M_NONE }, // C3 RETN
		{ A_NONE, true, M_NONE }, // C4 LES r16, mem16+16
		{ A_NONE, true, M_NONE }, // C5 LDS r16, mem16+16
		{ A_NONE, true, M_BYTE }, // C6 MOV rm8, imm8
		{ A_NONE, true, M_ZORD }, // C7 MOV rm32, imm32
		{ A_NONE, false, M_THREE }, // C8 ENTER imm16, imm8
		{ A_NONE, false, M_NONE }, // C9 LEAVE
		{ A_NONE, false, M_WORD }, // CA RETF imm16
		{ A_NONE, false, M_NONE }, // CB RETF
		{ A_NONE, false, M_NONE }, // CC INT 3
		{ A_NONE, false, M_BYTE }, // CD INT imm8
		{ A_NONE, false, M_NONE }, // CE INTO
		{ A_NONE, false, M_NONE }, // CF IRETD
		{ A_NONE, true, M_NONE }, // D0 Grp2 rm8, 1
		{ A_NONE, true, M_NONE }, // D1 Grp2 rm32, 1
		{ A_NONE, true, M_NONE }, // D2 Grp2 rm8, cl
		{ A_NONE, true, M_NONE }, // D3 Grp2 rm32, cl
		{ A_NONE, false, M_BYTE }, // D4 AAM imm8
		{ A_NONE, false, M_BYTE }, // D5 AAD imm8
		{ A_NONE, false, M_NONE }, // D6 SETALC (undocumented)
		{ A_NONE, false, M_NONE }, // D7 XLATB
		{ A_NONE, true, M_NONE }, // D8 ESC
		{ A_NONE, true, M_NONE }, // D9 ESC
		{ A_NONE, true, M_NONE }, // DA ESC
		{ A_NONE, true, M_NONE }, // DB ESC
		{ A_NONE, true, M_NONE }, // DC ESC
		{ A_NONE, true, M_NONE }, // DD ESC
		{ A_NONE, true, M_NONE }, // DE ESC
		{ A_NONE, true, M_NONE }, // DF ESC
		{ A_NONE, false, M_BYTE }, // E0 LOOPNZ
		{ A_NONE, false, M_BYTE }, // E1 LOOPZ
		{ A_NONE, false, M_BYTE }, // E2 LOOP
		{ A_NONE, false, M_BYTE }, // E3 JECXZ
		{ A_NONE, false, M_BYTE }, // E4 IN al, imm8
		{ A_NONE, false, M_BYTE }, // E5 IN eax, imm8
		{ A_NONE, false, M_BYTE }, // E6 OUT imm8, al
		{ A_NONE, false, M_BYTE }, // E7 OUT imm8, eax
		{ A_NONE, false, M_ZORD }, // E8 CALL near
		{ A_NONE, false, M_ZORD }, // E9 JMP near
		{ A_NONE, false, M_FAR }, // EA JMP far
		{ A_NONE, false, M_BYTE }, // EB JMP short
		{ A_NONE, false, M_NONE }, // EC IN al, dx
		{ A_NONE, false, M_NONE }, // ED IN eax, dx
		{ A_NONE, false, M_NONE }, // EE OUT dx, al
		{ A_NONE, false, M_NONE }, // EF OUT dx, eax
		{ A_PREFIX }, // F0 LOCK prefix
		{ A_NONE, false, M_NONE }, // F1 ICEBP (aka INT 1, undocumented)
		{ A_PREFIX }, // F2 REPNE prefix
		{ A_PREFIX }, // F3 REP/REPE prefix
		{ A_NONE, false, M_NONE }, // F4 HLT
		{ A_NONE, false, M_NONE }, // F5 CMC
		{ A_GRP, true, M_BYTE }, // F6 Grp3 rm8 (/0 -> imm8)
		{ A_GRP, true, M_ZORD }, // F7 Grp3 rm32 (/0 -> imm32)
		{ A_NONE, false, M_NONE }, // F8 CLC
		{ A_NONE, false, M_NONE }, // F9 STC
		{ A_NONE, false, M_NONE }, // FA CLI
		{ A_NONE, false, M_NONE }, // FB STI
		{ A_NONE, false, M_NONE }, // FC CLD
		{ A_NONE, false, M_NONE }, // FD STD
		{ A_NONE, true, M_NONE }, // FE Grp4 rm8 (inc/dec)
		{ A_NONE, true, M_NONE }, // FF Grp4 rm32 (inc/dec + indirect call/jmp and imm push)
	};
	static_assert(256 == sizeof(op_basic_info) / sizeof(OpBasicInfo), "op_basic_info size error");
}