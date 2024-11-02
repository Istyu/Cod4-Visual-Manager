#include "stdafx.hpp"
#include "ManagerStuff.hpp"

namespace Components
{
	HANDLE Components::Loader::mainThread = nullptr;
	void Loader::Initialize( HMODULE hModule )
	{
		mainThread = CreateThread(NULL, NULL, Manager::Init, hModule, NULL, NULL);
	}
}