#include "stdafx.hpp"
//#include "ManagerStuff.hpp"
namespace Patch
{
	void cvar_cheats()
	{
		// Turn off cheat protection
		if( cod4x_entry )
			*(int *)0xCBA7404 |= 4;
		else if(!strcmp((char*)0x6E0568, "568"))
			*(int *)0xCBA7404 |= 1;
	}

	void WriteStringToMemory(DWORD address, const char* str)
	{
		// Iterate over each character in the string
		for (size_t i = 0; i < strlen(str); ++i)
		{
		    // Write a byte to the given address
		    //injector::WriteMemory<BYTE>(address + i, str[i], true);
		    injector::WriteMemory<BYTE>(*(DWORD*)address + i, (DWORD)(str[i]), true);
		}
	}
	void WriteStringToMemory2(DWORD address, const char* str)
	{
	    for (size_t i = 0; i < strlen(str); ++i)
	    {
	        // If the character is '>', replace it with, for example, ':'
	        BYTE characterToWrite = (str[i] == '>') ? ':' : str[i];
	        
	        // Write the selected character to memory
	        injector::WriteMemory<BYTE>(*(DWORD*)address + i, (DWORD)(characterToWrite), true);
	    }
	}

	void borderLess()
	{
		bool done  =  false;
        while (!done)
        {
            HWND hGameWindow = FindWindow( NULL, TEXT("Call of Duty 4") );
            if( hGameWindow != NULL )
            { 
                //MessageBox(NULL, "The Call of Duty 4 must be run!", "COD4!", MB_OK);
                LONG styles = GetWindowLong(hGameWindow,  GWL_STYLE);
                if (0 != styles)
                {
                    styles ^= WS_CAPTION;
                    LONG result = SetWindowLong(hGameWindow, GWL_STYLE, styles);
                }
            }
            //char c;
            //scanf("%c", &c);
            //if ('q' == c)
                done = true;
        }
	}

	void patch()
	{
		cvar_cheats();

		if(!strcmp((char*)0x6E0568, "568"))
		{
			// build tag in UI code
			const char* myString = "1.7.568 \n Visual manager";
    		DWORD buildVer = 0x5434BC;
    		WriteStringToMemory(buildVer, myString);

    		// console '%s: %s> ' string
			myString = "%s- VM %s: ";
    		DWORD aSS_5 = 0x46060F;
    		WriteStringToMemory(aSS_5, myString);

    		myString = "COD4 MP";
    		DWORD aCod4Mp = 0x46060A;
    		WriteStringToMemory2(aCod4Mp, myString);

    		myString = "1.7";
    		DWORD a17 = 0x460605;
    		WriteStringToMemory2(a17, myString);

    		// version string
    		myString = "1.7";
    		DWORD ver = 0x461B84;
    		WriteStringToMemory(ver, myString);

    		//if( Manager::borderless == 1 )
    			borderLess();
    	}
    	if( cod4x_entry )
    	{
    		// Console color
    		injector::WriteMemory<BYTE>(0x0CBB15E7, 60, true); // red
    		injector::WriteMemory<BYTE>(0x0CBB15EB, 60, true); // green
    		injector::WriteMemory<BYTE>(0x0CBB15EF, 60, true); // blue

    		// Color of the console input hint box
    		injector::WriteMemory<BYTE>(0x0CBB1633, 60, true); // red
    		injector::WriteMemory<BYTE>(0x0CBB1637, 60, true); // green
    		injector::WriteMemory<BYTE>(0x0CBB163B, 60, true); // blue
    	}
	}
}