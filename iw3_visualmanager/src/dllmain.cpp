// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.hpp"

namespace Main
{
    void initialize( HMODULE hModule )
    {
        if( !hModule )
        {
            MessageBox(NULL, (LPCWSTR)L"Cod4 initialize failed.", (LPCWSTR)L"Visual Manager", MB_ICONERROR);
            return;
        }

        Components::Loader::Initialize( hModule );
        //Patch::patch();

        //if( cod4x_entry )
        //    MessageBox(NULL, (LPCWSTR)L"Cod4x.", (LPCWSTR)L"Visual Manager", MB_OK); // DEV
    }
}

void CreateConsole()
{
    // Allocate a console for this app
    AllocConsole();

    // Redirect stdout to the console
    FILE* stream;
    stream = freopen("CONOUT$", "w", stdout);

    // Optionally redirect stdin and stderr as well
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);

    // You can use std::cout as well
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID /*lpReserved*/ )
{
    if( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        #if DEV
            CreateConsole();
        #endif
        Main::initialize( hModule );

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

