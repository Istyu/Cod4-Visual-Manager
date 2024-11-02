#include "stdafx.hpp"

namespace Manager
{
	//float r_filmTweakDarkTint1, r_filmTweakDarkTint2, r_filmTweakDarkTint3, r_filmtweakLighttint1, r_filmtweakLighttint2, r_filmtweakLighttint3, r_filmTweakBrightness;
	static bool filmtweak = false;
	static int fovscale = 0;
	static int fps = 0;
	static bool drawFps = false;
	static bool fullbright = false;

	DWORD WINAPI Init( LPVOID param )
	{
		// Read values from .ini
        //CIniReader iniReader("VisualSettings.ini");

        //r_filmTweakDarkTint1 = iniReader.ReadFloat("Filmtweak", "r_filmTweakDarkTint1", 1.8f);
        //r_filmTweakDarkTint2 = iniReader.ReadFloat("Filmtweak", "r_filmTweakDarkTint2", 1.8f);
        //r_filmTweakDarkTint3 = iniReader.ReadFloat("Filmtweak", "r_filmTweakDarkTint3", 2.0f);
        //r_filmtweakLighttint1 = iniReader.ReadFloat("Filmtweak", "r_filmtweakLighttint1", 0.8f);
        //r_filmtweakLighttint2 = iniReader.ReadFloat("Filmtweak", "r_filmtweakLighttint2", 0.8f);
        //r_filmtweakLighttint3 = iniReader.ReadFloat("Filmtweak", "r_filmtweakLighttint3", 1.0f);
        //r_filmTweakBrightness = iniReader.ReadFloat("Filmtweak", "r_filmTweakBrightness", 0.1f);

		// Fullbright 2
    	//DWORD D0x00633278 = 0x00633278; 
        //_asm call D0x00633278;

        //Sleep(1000);

		while( true )
		{
			if( GetAsyncKeyState(VK_NUMPAD0) )
			{
				if( fovscale == 1 )
				{
					injector::WriteMemory<float>(0x0CBACE58, 1.45f, true);
					Game::iPrintLnBold("Field of View Scale: 1.45");
					fovscale = 0;
				}
				else if( fovscale == 2 )
				{
					injector::WriteMemory<float>(0x0CBACE58, 1.35f, true);
					Game::iPrintLnBold("Field of View Scale: 1.35");
					fovscale = 1;
				}
				else if( fovscale == 3 )
				{
					injector::WriteMemory<float>(0x0CBACE58, 1.135f, true);
					Game::iPrintLnBold("Field of View Scale: 1.135");
					fovscale = 2;
				}
				else if( fovscale == 0 )
				{
					injector::WriteMemory<float>(0x0CBACE58, 1.0f, true); // FOVscale
					Game::iPrintLnBold("Field of View Scale: 1.0");
					fovscale = 3;
				}
			}
	
			if( GetAsyncKeyState(VK_NUMPAD1) )
			{
				if( !filmtweak )
				{
					injector::WriteMemory<int>(0x0CBC0020, 1, true); // r_filmusetweaks
					injector::WriteMemory<int>(0x0CBC006C, 1, true); // r_filmTweakenable
					injector::WriteMemory<float>(0x0CBC02CC, 1.8f, true); // r_filmTweakDarkTint first value
					injector::WriteMemory<float>(0x0CBC02D0, 1.8f, true); // r_filmTweakDarkTint second value
					injector::WriteMemory<float>(0x0CBC02D4, 2.0f, true); // r_filmTweakDarkTint third value
					injector::WriteMemory<float>(0x0CBC0318, 0.8f, true); // r_filmtweakLighttint first value
					injector::WriteMemory<float>(0x0CBC031C, 0.8f, true); // r_filmtweakLighttint second value
					injector::WriteMemory<float>(0x0CBC0320, 1.0f, true); // r_filmtweakLighttint third value
					injector::WriteMemory<float>(0x0CBC01E8, 0.1f, true); // r_filmTweakBrightness
					Game::iPrintLnBold("Promod vision ON");
					filmtweak = true;
				}
				else if( filmtweak )
				{
					injector::WriteMemory<int>(0x0CBC0020, 0, true); // r_filmusetweaks
					injector::WriteMemory<int>(0x0CBC006C, 0, true); // r_filmTweakenable
					Game::iPrintLnBold("Promod vision OFF");
					filmtweak = false;
				}
			}

			if( GetAsyncKeyState(VK_NUMPAD2) )
			{
				if( !fullbright )
				{
					DWORD D0x0063325B = 0x0063325B;
        			_asm call D0x0063325B;
        			Game::iPrintLnBold("Fullbright ON");
        			fullbright = true;
        		}
        		else if( fullbright )
        		{
        			DWORD D0x0063326C = 0x0063326C;
            		_asm call D0x0063326C;
            		Game::iPrintLnBold("Fullbright OFF");
            		fullbright = false;
        		}
			}
	
			if( GetAsyncKeyState(VK_NUMPAD3) )
			{
				if( fps == 0 )
				{
					injector::WriteMemory<int>(0x0CBAB8AC, 125, true); // com_maxfps
					Game::iPrintLnBold("Frame/second: 125");
					fps = 1;
				}
				else if( fps == 1 )
				{
					injector::WriteMemory<int>(0x0CBAB8AC, 250, true);
					Game::iPrintLnBold("Frame/second: 250");
					fps = 2;
				}
				else if( fps == 2 )
				{
					injector::WriteMemory<int>(0x0CBAB8AC, 333, true);
					Game::iPrintLnBold("Frame/second: 333");
					fps = 0;
				}
			}
	
			if( GetAsyncKeyState(VK_NUMPAD4) )
			{
				if( !drawFps )
				{
					injector::WriteMemory<int>(0x0CBAEFE4, 0, true); // cg_drawFPS
					drawFps = true;
				}
				else if( drawFps )
				{
					injector::WriteMemory<int>(0x0CBAEFE4, 1, true);
					drawFps = false;
				}
			}

			Sleep(100);
		}

		FreeLibraryAndExitThread( (HMODULE)param, 0 );

		return 0;
	}
}

/*
	0x4605E0
	0x470060
	0x472790
	0x4FF1C0
	0x52A4D0
	0x543410
	0x5472B0
	0x6CF580 a17
	0x6CF584 aCod4Mp

	0x6CF5E4 aSS_3 '%s %s',0
	0x6CF58C aSS_5 '%s: %s> ',0

	iw3mp.exe+110F86C
	iw3mp.exe+1111424

	iw3mp.exe+1111394 01511394 cod4x.ovh

	cod4x_021.dll+43EC968
	cod4x_021.dll+4480E20 14B70E20

	008F1BA0 console text

	Console color
	0CBB15E7
	0CBB15EB
	0CBB15EF

	Color of the console input hint box
	0CBB1633
	0CBB1637
	0CBB163B

	:0062A0B7                 mov     eax, offset aRFullbright ; "r_fullbright"
	.rdata:007048A8 aRFullbright    db 'r_fullbright',0     ; DATA XREF: sub_629D70+347↑o
*/