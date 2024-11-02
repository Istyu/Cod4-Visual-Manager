#pragma once

namespace Components
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		//virtual void preDestroy() {}
	};

	class Loader
	{
	public:
		static HANDLE mainThread;
		static void Initialize( HMODULE hModule );
	};
}

//#include "Modules/.hpp"