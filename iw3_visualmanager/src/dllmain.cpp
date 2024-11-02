// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.hpp"
//#include "HookStuff.h"

namespace Main
{
    void initialize( HMODULE hModule )
    {
        Components::Loader::Initialize( hModule );
    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID /*lpReserved*/ )
{
    if( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        //DWORD oldProtect;
        //VirtualProtect(GetModuleHandle(nullptr), 0xD536000, PAGE_EXECUTE_READWRITE, &oldProtect);

        //injector::MakeJMP(0x67493C, StartEntryPoint, true);

        Main::initialize( hModule );

        //CreateThread(NULL, NULL, Init, NULL, NULL, NULL);
        #if DEV
            MessageBox(NULL, (LPCWSTR)L"Dll attached", (LPCWSTR)L"INJ!", MB_OK);
        #endif
    }
    else if( ul_reason_for_call == DLL_PROCESS_DETACH )
    {
        WaitForSingleObject(Components::Loader::mainThread, INFINITE);
        CloseHandle(Components::Loader::mainThread);

        #if DEV
            MessageBox(NULL, (LPCWSTR)L"Uninjecting", (LPCWSTR)L"Bye!", MB_OK);
        #endif
    }

    return TRUE;
}

