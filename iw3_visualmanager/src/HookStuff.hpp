#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
//#include "..\includes\IniReader.h"

//int input1Hook;

typedef void(*Com_PrintMessage_t)(int, const char*, char);
		extern Com_PrintMessage_t Com_PrintMessage;

Com_PrintMessage_t			Com_PrintMessage = Com_PrintMessage_t(0x4FCA50);


typedef void(*Cmd_ExecuteSingleCommand_t)(int controller, int a2, const char* cmd);
		extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

Cmd_ExecuteSingleCommand_t	Cmd_ExecuteSingleCommand = Cmd_ExecuteSingleCommand_t(0x4F9AB0);


void iPrintLnBold(const char* text);

void iPrintLnBold(const char* text)
{
    __asm
    {
        push text
        push 0
        mov esi, 0x43de00
        call esi
        add esp, 0x8
    }
}
/*
template <typename T>
static void set(void* place, T value)
{
	DWORD old_protect;
	VirtualProtect(place, sizeof(T), PAGE_EXECUTE_READWRITE, &old_protect);

	*static_cast<T*>(place) = value;

	VirtualProtect(place, sizeof(T), old_protect, &old_protect);
	FlushInstructionCache(GetCurrentProcess(), place, sizeof(T));
}

template <typename T>
static void set(const DWORD place, T value)
{
	return set<T>(reinterpret_cast<void*>(place), value);
}*/
union DvarLimits
	{
		struct
		{
			int stringCount;
			const char **strings;
		} enumeration;

		struct
		{
			int min;
			int max;
		} integer;

		struct
		{
			float min;
			float max;
		} value;

		struct
		{
			float min;
			float max;
		} vector;
	};
union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char *string;
		char color[4];
	};
enum class dvar_type : std::int8_t
	{
		boolean = 0,
		value = 1,
		vec2 = 2,
		vec3 = 3,
		vec4 = 4,
		integer = 5,
		enumeration = 6,
		string = 7,
		color = 8,
		rgb = 9 // Color without alpha
	};
enum dvar_flags : std::uint16_t
	{
		none				= 0x0,
		saved				= 0x1,
		user_info			= 0x2, // sent to server on connect or change
		server_info			= 0x4, // sent in response to front end requests
		replicated			= 0x8,
		write_protected		= 0x10,
		latched				= 0x20,
		read_only			= 0x40,
		cheat_protected		= 0x80,
		temp				= 0x100,
		no_restart			= 0x400, // do not clear when a cvar_restart is issued
		user_created		= 0x4000, // created by a set command
	};
struct dvar_s
	{
		const char *name;
		const char *description;
		//unsigned __int16 flags;
		dvar_flags flags;
		//char type;
		dvar_type type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		bool(__cdecl *domainFunc)(dvar_s *, DvarValue);
		dvar_s *hashNext;
	};
extern dvar_s* r_aspectRatio_custom;
dvar_s* r_aspectRatio_custom = nullptr;

extern dvar_s* ui_ultrawide;
dvar_s* ui_ultrawide = nullptr;
void dvar_set_value_dirty(dvar_s* dvar, bool value);
void dvar_set_value_dirty(dvar_s* dvar, bool value)
	{
		if (!dvar)
		{
			return;
		}

		dvar->current.enabled = value;
		dvar->latched.enabled = value;
		//_dvar->modified = false;
	}

void set_ultrawide_dvar(bool state)
	{
		if (ui_ultrawide)
		{
			dvar_set_value_dirty(ui_ultrawide, true);
		}
	}

	void set_custom_aspect_ratio()
	{
		if (r_aspectRatio_custom)
		{
			*(float*)(0xCC9D0F8) = r_aspectRatio_custom->current.value;
		}
	}

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

static bool filmtweak = false;
static int fovscale = 0;
static int fps = 0;
static bool drawFps = false;

//static const auto cg_fov_limit = 120.0f;

DWORD WINAPI Init(LPVOID)
{
	//char szSection[] = "Misc";
	//char szKey[] = "input1Value";
	//CIniReader iniReader("HookSettings.ini");

	//input1Hook = iniReader.ReadInteger(szSection, szKey, 0);

	//injector::WriteMemory<float>(0x438F7E, &cg_fov_limit, true);
	//set(0x438F7E, &cg_fov_limit);

	//injector::WriteMemory<float>(0x43ad8d, &cg_fov_limit, true);
	//set(0x43ad8d, &cg_fov_limit);
	//WriteSymbol(0x43ad8d, &cg_fov_limit);

	Com_PrintMessage(0, "^2Test print:\n", 0);
	Cmd_ExecuteSingleCommand(0, 0, "say \"Export Done!\"\n");
	Cmd_ExecuteSingleCommand(0, 0, "r_fullbright 1\n");

//	injector::MakeNOP(0x5F352E, 6, true);
//	injector::MakeJMP(0x5F352E, aspect_ratio_custom_reset_stub, true);
	Utils::Hook::Nop(0x5F352E, 6);
	Utils::Hook(0x5F352E, aspect_ratio_custom_reset_stub, HOOK_JUMP).install()->quick();

	//hook(0x5F35FA, aspect_ratio_custom_stub, HOOK_JUMP).install()->quick();
//	injector::MakeNOP(0x5F35FA, 6, true);
//	injector::MakeJMP(0x5F35FA, aspect_ratio_custom_stub, true);
	Utils::Hook::Nop(0x5F35FA, 6);
	Utils::Hook(0x5F35FA, aspect_ratio_custom_stub, HOOK_JUMP).install()->quick();

	for( ;;Sleep(500) )
	{
		if( GetAsyncKeyState(VK_NUMPAD0) )
		{
			if( fovscale == 1 )
			{
			//	injector::WriteMemory<float>(0x0CBACE58, 1.45f, true);
				Utils::Hook(0x0CBACE58, 1.45f, HOOK_JUMP).install()->quick();
				iPrintLnBold("Field of View Scale: 1.45");
				fovscale = 0;
			}
			else if( fovscale == 2 )
			{
			//	injector::WriteMemory<float>(0x0CBACE58, 1.35f, true);
				Utils::Hook(0x0CBACE58, 1.35f, HOOK_JUMP).install()->quick();
				iPrintLnBold("Field of View Scale: 1.35");
				fovscale = 1;
			}
			else if( fovscale == 3 )
			{
			//	injector::WriteMemory<float>(0x0CBACE58, 1.135f, true);
				Utils::Hook(0x0CBACE58, 1.135f, HOOK_JUMP).install()->quick();
				iPrintLnBold("Field of View Scale: 1.135");
				fovscale = 2;
			}
			else if( fovscale == 0 )
			{
			//	injector::WriteMemory<float>(0x0CBACE58, 1.0f, true); // FOVscale
				Utils::Hook(0x0CBACE58, 1.0f, HOOK_JUMP).install()->quick();
				iPrintLnBold("Field of View Scale: 1.0");
				fovscale = 3;
			}
		}

		if( GetAsyncKeyState(VK_NUMPAD1) )
		{
			if( !filmtweak )
			{
			//	injector::WriteMemory<int>(0x0CBC0020, 1, true); // r_filmusetweaks
			//	injector::WriteMemory<int>(0x0CBC006C, 1, true); // r_filmTweakenable
			//	injector::WriteMemory<float>(0x0CBC02CC, 1.8f, true); // r_filmTweakDarkTint first value
			//	injector::WriteMemory<float>(0x0CBC02D0, 1.8f, true); // r_filmTweakDarkTint second value
			//	injector::WriteMemory<float>(0x0CBC02D4, 2.0f, true); // r_filmTweakDarkTint third value
			//	injector::WriteMemory<float>(0x0CBC0318, 0.8f, true); // r_filmtweakLighttint first value
			//	injector::WriteMemory<float>(0x0CBC031C, 0.8f, true); // r_filmtweakLighttint second value
			//	injector::WriteMemory<float>(0x0CBC0320, 1.0f, true); // r_filmtweakLighttint third value
			//	injector::WriteMemory<float>(0x0CBC01E8, 0.1f, true); // r_filmTweakBrightness
				Utils::Hook(0x0CBC0020, 1, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC006C, 1, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC02CC, 1.8f, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC02D0, 1.8f, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC02D4, 2.0f, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC0318, 0.8f, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC031C, 0.8f, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC0320, 1.0f, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC01E8, 0.1f, HOOK_JUMP).install()->quick();
				iPrintLnBold("Promod vision ON");
				filmtweak = true;
			}
			else if( filmtweak )
			{
			//	injector::WriteMemory<int>(0x0CBC0020, 0, true); // r_filmusetweaks
			//	injector::WriteMemory<int>(0x0CBC006C, 0, true); // r_filmTweakenable
				Utils::Hook(0x0CBC0020, 0, HOOK_JUMP).install()->quick();
				Utils::Hook(0x0CBC006C, 0, HOOK_JUMP).install()->quick();
				iPrintLnBold("Promod vision OFF");
				filmtweak = false;
			}
		}

		if( GetAsyncKeyState(VK_NUMPAD2) )
		{
			if( fps == 0 )
			{
			//	injector::WriteMemory<int>(0x0CBAB8AC, 125, true); // com_maxfps
				Utils::Hook(0x0CBAB8AC, 125, HOOK_JUMP).install()->quick();
				iPrintLnBold("Frame/second: 125");
				fps = 1;
			}
			else if( fps == 1 )
			{
			//	injector::WriteMemory<int>(0x0CBAB8AC, 250, true);
				Utils::Hook(0x0CBAB8AC, 250, HOOK_JUMP).install()->quick();
				iPrintLnBold("Frame/second: 250");
				fps = 2;
			}
			else if( fps == 2 )
			{
			//	injector::WriteMemory<int>(0x0CBAB8AC, 333, true);
				Utils::Hook(0x0CBAB8AC, 333, HOOK_JUMP).install()->quick();
				iPrintLnBold("Frame/second: 333");
				fps = 0;
			}
		}

		if( GetAsyncKeyState(VK_NUMPAD3) )
		{
			if( !drawFps )
			{
			//	injector::WriteMemory<int>(0x0CBAEFE4, 0, true); // cg_drawFPS
				Utils::Hook(0x0CBAEFE4, 0, HOOK_JUMP).install()->quick();
				drawFps = true;
			}
			else if( drawFps )
			{
			//	injector::WriteMemory<int>(0x0CBAEFE4, 1, true);
				Utils::Hook(0x0CBAEFE4, 1, HOOK_JUMP).install()->quick();
				drawFps = false;
			}
		}
	}

	//injector::WriteMemory<int>(0x0CBBDFC4, 1, true); // fullbright
	//injector::WriteMemory<int>(0x0CBBDFD4, 1, true); // fullbright
}