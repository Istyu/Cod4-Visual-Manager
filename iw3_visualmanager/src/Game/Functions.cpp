#include "stdafx.hpp"

namespace Game
{
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

	// dvars 

	void dvar_set_value_dirty(dvar_s* dvar, int value)
	{
		if (!dvar)
		{
			return;
		}

		dvar->current.integer = value;
		dvar->latched.integer = value;
		//_dvar->modified = false;
	}

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

	void dvar_set_value_dirty(dvar_s* dvar, const float dvar_value)
	{
		if (!dvar)
		{
			return;
		}

		dvar->current.value = dvar_value;
		dvar->latched.value = dvar_value;
		//_dvar->modified = false;
	}

	void dvar_set_value_dirty(dvar_s* dvar, const char *dvar_value)
	{
		if (!dvar)
		{
			return;
		}

		dvar->current.string = dvar_value;
		dvar->latched.string = dvar_value;
		dvar->modified = false;
	}

	void dvar_set_value_dirty(dvar_s* dvar, const float* dvar_value, int size)
	{
		if (!dvar)
		{
			return;
		}

		for (auto i = 0; i < size && i < 4; i++)
		{
			dvar->current.vector[i] = dvar_value[i];
			dvar->latched.vector[i] = dvar_value[i];
		}
	}

	Cmd_ExecuteSingleCommand_t	Cmd_ExecuteSingleCommand = Cmd_ExecuteSingleCommand_t(0x4F9AB0);
	Com_PrintMessage_t			Com_PrintMessage = Com_PrintMessage_t(0x4FCA50);
	Com_Printf_t Com_Printf = Com_Printf_t(0x4FCBC0);
	Com_Error_t Com_Error = Com_Error_t(0x4FD330);
}