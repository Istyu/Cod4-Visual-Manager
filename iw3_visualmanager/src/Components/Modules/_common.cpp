#include "stdafx.hpp"

namespace Components
{
	// disable cheat / write check
	__declspec(naked) void disable_dvar_cheats_stub()
	{
		const static uint32_t retn_addr = 0x56B3A1;
		__asm
		{
			movzx   eax, word ptr [edi + 8];	// overwritten op
			jmp		retn_addr;
		}
	}
}