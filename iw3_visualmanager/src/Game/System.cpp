#include "stdafx.hpp"

namespace Game
{
	int	sys_timeBase;
	int Sys_MilliSeconds()
	{
		int	sys_curtime;
		static bool	initialized = false;

		if (!initialized) {
			sys_timeBase = timeGetTime();
			initialized = true;
		}
		sys_curtime = timeGetTime() - sys_timeBase;

		return sys_curtime;
	}
}