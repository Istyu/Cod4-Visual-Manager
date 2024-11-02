#include "stdafx.hpp"

namespace Components
{
	void set_ultrawide_dvar(bool state)
	{
		if (Dvars::ui_ultrawide)
		{
			Game::dvar_set_value_dirty(Dvars::ui_ultrawide, state);
		}
	}

	void set_custom_aspect_ratio()
	{
		if (Dvars::r_aspectRatio_custom)
		{
			*(float*)(0xCC9D0F8) = Dvars::r_aspectRatio_custom->current.value;
		}
	}

	// hook R_AspectRatio to initially reset the ultrawide dvar (menu helper)
	__declspec(naked) void aspect_ratio_custom_reset_stub()
	{
		const static uint32_t retn_addr = 0x5F3534;
		__asm
		{
			pushad;
			push	0;
			call	set_ultrawide_dvar;
			add		esp, 4;
			popad;

			mov     eax, [eax + 0xC];	// overwritten op
			cmp     eax, 3;				// overwritten op

			jmp		retn_addr;			// jump back to break op
		}
	}

	// set custom aspect ratio by using the default switchcase in R_AspectRatio
	__declspec(naked) void aspect_ratio_custom_stub()
	{
		const static uint32_t retn_addr = 0x5F35E5;
		__asm
		{
			pushad;
			push	1;
			call	set_ultrawide_dvar;
			add		esp, 4;

			Call	set_custom_aspect_ratio;
			popad;

			mov     ecx, 1;				// widescreen true
			jmp		retn_addr;			// jump back to break op
		}
	}
}