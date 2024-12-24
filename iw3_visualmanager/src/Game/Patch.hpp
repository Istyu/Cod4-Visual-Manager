#pragma once

namespace Patch
{
	void cvar_cheats();
	void WriteStringToMemory(DWORD address, const char* str);
	void WriteStringToMemory2(DWORD address, const char* str);
	void patch();
}