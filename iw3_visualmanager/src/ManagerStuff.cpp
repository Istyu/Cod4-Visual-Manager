#include "stdafx.hpp"
#include "ManagerStuff.hpp"
#include "..\includes\IniReader.h"

// clientUIActives.state = CA_CHALLENGING		3
// clientUIActives.state = CA_CONNECTING		4, 5
// clientUIActives.state = CA_CONNECTED			6
// clientUIActives.state = CA_ACTIVE			9

namespace Manager
{
	float r_filmTweakDarkTint1, r_filmTweakDarkTint2, r_filmTweakDarkTint3, r_filmtweakLighttint1, r_filmtweakLighttint2, r_filmtweakLighttint3, r_filmTweakBrightness;
	static bool filmtweak = false;
	static int fps = 0;
	static bool specular = false;
	static bool normal = false;
	static bool decals = false;
	static bool drawFps = false;
	static bool fullbright = false;

	#define clientUIActives (*((Game::clientUIActives_t*)(0xc5f8f4)))
	#define MANAGER_WINDOW_TITLE L"IW3 visual manager"
	#define MANAGER_DEFAULT_WIDTH    800
	#define MANAGER_DEFAULT_HEIGHT   600

	void getIni()
	{
		// Read values from .ini
        CIniReader iniReader("VisualSettings.ini");

        r_filmTweakDarkTint1 = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmTweakDarkTint1"), 1.8f);
        r_filmTweakDarkTint2 = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmTweakDarkTint2"), 1.8f);
        r_filmTweakDarkTint3 = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmTweakDarkTint3"), 2.0f);
        r_filmtweakLighttint1 = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmtweakLighttint1"), 0.8f);
        r_filmtweakLighttint2 = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmtweakLighttint2"), 0.8f);
        r_filmtweakLighttint3 = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmtweakLighttint3"), 1.0f);
        r_filmTweakBrightness = iniReader.ReadFloat(const_cast<char*>("Filmtweak"), const_cast<char*>("r_filmTweakBrightness"), 0.1f);
        borderless = iniReader.ReadInteger(const_cast<char*>("Screen"), const_cast<char*>("borderless"), 0);

        #if DEV
        	std::cout << "filmTweak DarkTint1: " << r_filmTweakDarkTint1 << std::endl;
        	std::cout << "filmTweak DarkTint2: " << r_filmTweakDarkTint2 << std::endl;
        	std::cout << "filmTweak DarkTint3: " << r_filmTweakDarkTint3 << std::endl;
        	std::cout << "filmTweak Lighttint1: " << r_filmtweakLighttint1 << std::endl;
        	std::cout << "filmTweak Lighttint2: " << r_filmtweakLighttint2 << std::endl;
        	std::cout << "filmTweak Lighttint3: " << r_filmtweakLighttint3 << std::endl;
        	std::cout << "filmTweak Brightness: " << r_filmTweakBrightness << std::endl;
        	std::cout << "borderless: " << borderless << std::endl;
        #endif

        char tweakPrint[50];
		snprintf(tweakPrint, sizeof(tweakPrint), "filmTweakDarkTint 1: %.1f\n", r_filmTweakDarkTint1);
        Game::Com_Printf(0, tweakPrint, 0);

        snprintf(tweakPrint, sizeof(tweakPrint), "filmTweakDarkTint 2: %.1f\n", r_filmTweakDarkTint2);
        Game::Com_Printf(0, tweakPrint, 0);

        snprintf(tweakPrint, sizeof(tweakPrint), "filmTweakDarkTint 3: %.1f\n", r_filmTweakDarkTint3);
        Game::Com_Printf(0, tweakPrint, 0);

        snprintf(tweakPrint, sizeof(tweakPrint), "filmtweakLighttint 1: %.1f\n", r_filmtweakLighttint1);
        Game::Com_Printf(0, tweakPrint, 0);

        snprintf(tweakPrint, sizeof(tweakPrint), "filmtweakLighttint 2: %.1f\n", r_filmtweakLighttint2);
        Game::Com_Printf(0, tweakPrint, 0);

        snprintf(tweakPrint, sizeof(tweakPrint), "filmtweakLighttint 3: %.1f\n", r_filmtweakLighttint3);
        Game::Com_Printf(0, tweakPrint, 0);

        snprintf(tweakPrint, sizeof(tweakPrint), "filmTweakBrightness: %.1f\n", r_filmTweakBrightness);
        Game::Com_Printf(0, tweakPrint, 0);
	}


	#define FTWEAK_ID 1
	#define FBRIGHT_ID 2
	#define SPECULAR_ID 3
	#define NORMAL_ID 4
	#define DECALS_ID 5
	#define FPSLIMIT_ID 6
	#define FPSMETER_ID 7

	// UI_Init: manager entry point
	void UI_Init( HMODULE hInstance )
	{
		HDC hDC;
	    WNDCLASS wc;
	    RECT rect;
	    LPCWSTR MANAGERCLASS = MANAGER_WINDOW_TITLE L" 2.0";
	    LPCWSTR WINDOWNAME = MANAGER_WINDOW_TITLE L" 2.0";

	    int nHeight;
    	int swidth, sheight;
    	int MANAGERSTYLE = WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX;
	
	    // Window class definition
	    memset(&wc, 0, sizeof(wc));
	//    wc.cbSize        = sizeof(WNDCLASS);
	    wc.style         = 0;
	    wc.lpfnWndProc   = WndProc;
	    wc.cbClsExtra    = 0;
	    wc.cbWndExtra    = 0;
	    wc.hInstance     = (HMODULE)hInstance;
	    wc.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
	    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
	    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	    wc.lpszMenuName  = NULL;
	    wc.lpszClassName = MANAGERCLASS;
	//    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	
		if( !GetClassInfo(hInstance, MANAGERCLASS, &wc) )
		{
	    	if( !RegisterClass(&wc) )
	    	{
	    		#if DEV
	    	    MessageBoxA( 0, "Window registration failed!", "Error!", 0 );
	    	    #endif
	    	    return;
	    	}
	    }

	    rect.left = 0;
    	rect.right = MANAGER_DEFAULT_WIDTH;
    	rect.top = 0;
    	rect.bottom = MANAGER_DEFAULT_HEIGHT;
    	AdjustWindowRect(&rect, MANAGERSTYLE, FALSE);

    	hDC = GetDC(GetDesktopWindow());
    	swidth = GetDeviceCaps(hDC, HORZRES);
    	sheight = GetDeviceCaps(hDC, VERTRES);
    	ReleaseDC(GetDesktopWindow(), hDC);

    	//s_wcd.windowWidth = rect.right - rect.left + 1;
    	//s_wcd.windowHeight = rect.bottom - rect.top + 1;
	
	    // Create window
	    hwnd = CreateWindowEx(
	        0,
	        MANAGERCLASS,
	        WINDOWNAME,
	        MANAGERSTYLE,
	        ( swidth - 600 ) / 2, ( sheight - 450 ) / 2, rect.right - rect.left + 1, rect.bottom - rect.top + 1,
	        NULL, NULL, (HMODULE)hInstance, NULL);
	
	    if( hwnd == NULL )
	    {
	        #if DEV
	        MessageBoxA( 0, "Failed to create window!", "Error!", 0 );
	        #endif
	        return;
	    }
	
	    ShowWindow( hwnd, SW_SHOWDEFAULT );
	    UpdateWindow( hwnd );
	    SetForegroundWindow( hwnd );



	    // Create slider
        hTrackbar = CreateWindowEx(
            0,
            TRACKBAR_CLASS,
            NULL,
            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
            50, 450, 300, 30,  // position and size
            hwnd,
            NULL,
            (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),
            NULL);

        // Slider minimum and maximum value
        SendMessage(hTrackbar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 100)); // Range: 0-100
        SendMessage(hTrackbar, TBM_SETPOS, TRUE, 0); // Set start position to 0
	}

	// Window function
	LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
	    switch( msg )
	    {
	        case WM_CREATE:
	            hButton = CreateWindow(
	                L"BUTTON",  // Button class name
	                L"Filmtweak: OFF",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 50,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) FTWEAK_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            hButton2 = CreateWindow(
	            	L"BUTTON",  // Button class name
	                L"Fullbright: OFF",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 100,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) FBRIGHT_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            hButton3 = CreateWindow(
	            	L"BUTTON",  // Button class name
	                L"Specular maps: OFF",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 150,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) SPECULAR_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            hButton4 = CreateWindow(
	            	L"BUTTON",  // Button class name
	                L"Normal maps: OFF",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 200,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) NORMAL_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            hButton5 = CreateWindow(
	            	L"BUTTON",  // Button class name
	                L"Draw decals: OFF",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 250,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) DECALS_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            hButton6 = CreateWindow(
	            	L"BUTTON",  // Button class name
	                L"FPSlimit: ",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 300,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) FPSLIMIT_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            hButton7 = CreateWindow(
	            	L"BUTTON",  // Button class name
	                L"FPSmeter: OFF",  // Button title
	                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Button styles
	                50, 350,  // Button position
	                140, 30,  // Button size
	                hwnd,  // parent window
	                (HMENU) FPSMETER_ID,  // Button ID
	                (HINSTANCE) GetWindowLongPtr( hwnd, GWLP_HINSTANCE ),  // Window instance
	                NULL);
	            // Create label
            	hLabel = CreateWindow(
                	L"STATIC",               // Label class
                	L"FOV scale. Range: 1.0 - 1.45.\nValue: 0.0",   // Label text
                	WS_VISIBLE | WS_CHILD,   // It is visible and appears as a child window
                	50, 410,                  // X and Y position
                	200, 40,                 // Width and height
                	hwnd,                    // parent window
                	NULL,                    // We do not assign an ID to it because it is static
                	(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                	NULL);
	            break;
	        case WM_HSCROLL: // Event when the slider is moved
            {
            	if( clientUIActives.state != 9 )
				{
					#if DEV
    				std::cout << "CLI state: " << clientUIActives.state << std::endl;
    				#endif
	
    				Sleep(100);
    				SendMessage(hTrackbar, TBM_SETPOS, TRUE, 0);
	
    				break;
				}

                if( (HWND)lParam == hTrackbar )  // Check if the slider has been moved
                {
                    int pos = SendMessage(hTrackbar, TBM_GETPOS, 0, 0); // Slider current position
                    float fovValue = 1.0f + (pos / 100.0f) * 0.45f; // Convert between 1.0 and 1.45
                    if( cod4x_entry )
                    	injector::WriteMemory<float>(0x0CBACE58, fovValue, true); // FOVscale value setting cod4x
                	else if(!strcmp((char*)0x6E0568, "568"))
                    	injector::WriteMemory<float>(0x0CBACDC0, fovValue, true); // FOVscale value setting cod4 1.7
                    // Create a buffer to store the converted value
					char buffer[50]; // The length of the buffer should be sufficient for store the formatted text
					snprintf(buffer, sizeof(buffer), "Field of View Scale: %.2f", fovValue);
					Game::iPrintLnBold(buffer);

					wchar_t labelBuff[100];
					swprintf(labelBuff, sizeof(labelBuff) / sizeof(wchar_t), L"FOV scale. Range: 1.0 - 1.45.\nValue: %.2f", fovValue);
					SetWindowText(hLabel, labelBuff);
                }
                break;
            }
	        case WM_COMMAND:
	        	if( clientUIActives.state != 9 )
				{
					#if DEV
    				std::cout << "CLI state: " << clientUIActives.state << std::endl;
    				#endif
	
    				Sleep(500);
	
    				break;
				}

	            if( LOWORD(wParam) == FTWEAK_ID )
	            {
	                if( !filmtweak )
					{
						Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmusetweaks \"1\"\n");
						Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmTweakenable \"1\"\n");
					//	Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmTweakDarkTint \"1.8\" \"1.8\" \"2.0\"\n");
        				char darkTintCMD[100];
        				sprintf(darkTintCMD, "r_filmTweakDarkTint \"%.1f\" \"%.1f\" \"%.1f\"\n",
        				        r_filmTweakDarkTint1, r_filmTweakDarkTint2, r_filmTweakDarkTint3);
        				Game::Cmd_ExecuteSingleCommand(0, 0, darkTintCMD);

					//	Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmtweakLighttint \"0.8\" \"0.8\" \"1.0\"\n");
						char lightTintCMD[100];
        				sprintf(lightTintCMD, "r_filmtweakLighttint \"%.1f\" \"%.1f\" \"%.1f\"\n",
        				        r_filmtweakLighttint1, r_filmtweakLighttint2, r_filmtweakLighttint3);
        				Game::Cmd_ExecuteSingleCommand(0, 0, lightTintCMD);

					//	Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmTweakBrightness \"0.1\"\n");
						char brightnessCMD[100];
        				sprintf(brightnessCMD, "r_filmTweakBrightness \"%.1f\"\n",
        				        r_filmTweakBrightness);
        				Game::Cmd_ExecuteSingleCommand(0, 0, brightnessCMD);
						Game::iPrintLnBold("Promod vision ON");
						filmtweak = true;
					}
					else if( filmtweak )
					{
						Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmusetweaks \"0\"\n");
						Game::Cmd_ExecuteSingleCommand(0, 0, "r_filmTweakenable \"0\"\n");
						Game::iPrintLnBold("Promod vision OFF");
						filmtweak = false;
					}
	            }
	            else if( LOWORD(wParam) == FBRIGHT_ID )
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
	            else if( LOWORD(wParam) == SPECULAR_ID )
	            {
	            	if( !specular )
	            	{
	            		Game::Cmd_ExecuteSingleCommand(0, 0, "r_specular \"1\"\n");
	            		Game::iPrintLnBold("Specular maps ON");
	            		specular = true;
	            	}
	            	else if( specular )
	            	{
	            		Game::Cmd_ExecuteSingleCommand(0, 0, "r_specular \"0\"\n");
	            		Game::iPrintLnBold("Specular maps OFF");
	            		specular = false;
	            	}
	            }
	            else if( LOWORD(wParam) == NORMAL_ID )
	            {
	            	if( !normal )
	            	{
	            		Game::Cmd_ExecuteSingleCommand(0, 0, "r_normal \"1\"\n");
	            		Game::iPrintLnBold("Normal maps ON");
	            		normal = true;
	            	}
	            	else if( normal )
	            	{
	            		Game::Cmd_ExecuteSingleCommand(0, 0, "r_normal \"0\"\n");
	            		Game::iPrintLnBold("Normal maps OFF");
	            		normal = false;
	            	}
	            }
	            else if( LOWORD(wParam) == DECALS_ID )
	            {
	            	if( !decals )
	            	{
	            		Game::Cmd_ExecuteSingleCommand(0, 0, "r_drawDecals \"1\"\n");
	            		Game::iPrintLnBold("Draw decals ON");
	            		decals = true;
	            	}
	            	else if( decals )
	            	{
	            		Game::Cmd_ExecuteSingleCommand(0, 0, "r_drawDecals \"0\"\n");
	            		Game::iPrintLnBold("Draw decals OFF");
	            		decals = false;
	            	}
	            }
	            else if( LOWORD(wParam) == FPSLIMIT_ID )
	            {
	            	if( fps == 0 )
					{
						//injector::WriteMemory<int>(0x0CBAB8AC, 125, true); // com_maxfps
						Game::iPrintLnBold("Frame/second: 125");
						Game::Cmd_ExecuteSingleCommand(0, 0, "com_maxfps \"125\"\n");
						fps = 1;
					}
					else if( fps == 1 )
					{
						//injector::WriteMemory<int>(0x0CBAB8AC, 250, true);
						Game::Cmd_ExecuteSingleCommand(0, 0, "com_maxfps \"250\"\n");
						Game::iPrintLnBold("Frame/second: 250");
						fps = 2;
					}
					else if( fps == 2 )
					{
						//injector::WriteMemory<int>(0x0CBAB8AC, 333, true);
						Game::Cmd_ExecuteSingleCommand(0, 0, "com_maxfps \"333\"\n");
						Game::iPrintLnBold("Frame/second: 333");
						fps = 0;
					}
	            }
	            else if( LOWORD(wParam) == FPSMETER_ID )
	            {
	            	if( !drawFps )
					{
						//injector::WriteMemory<int>(0x0CBAEFE4, 0, true); // cg_drawFPS
						Game::Cmd_ExecuteSingleCommand(0, 0, "cg_drawFPS \"1\"\n");
						drawFps = true;
					}
					else if( drawFps )
					{
						//injector::WriteMemory<int>(0x0CBAEFE4, 1, true);
						Game::Cmd_ExecuteSingleCommand(0, 0, "cg_drawFPS \"0\"\n");
						drawFps = false;
					}
	            }
	            break;
	        case WM_CLOSE:
	        	Sleep(100);
	            DestroyWindow( hwnd );
	            break;
	        case WM_DESTROY:
	        	Sleep(100);
	            PostQuitMessage(0);
	            break;
	        default:
	            return DefWindowProc( hwnd, msg, wParam, lParam );
	    }
	    return 0;
	}

	void UI_Shutdown(void)
	{
    	if( hwnd )
    	{
    	    ShowWindow( hwnd, SW_HIDE );
    	    CloseWindow( hwnd );
    	    DestroyWindow( hwnd );
    	    hwnd = 0;
    	}
	}

	void changeBtnText()
	{
		if( !filmtweak )
			SetWindowText(hButton, L"Filmtweak: OFF");
		else if( filmtweak )
			SetWindowText(hButton, L"Filmtweak: ON");

		if( !fullbright )
			SetWindowText(hButton2, L"Fullbright: OFF");
		else if( fullbright )
			SetWindowText(hButton2, L"Fullbright: ON");

		if( !specular )
			SetWindowText(hButton3, L"Specular maps: OFF");
		else if( specular )
			SetWindowText(hButton3, L"Specular maps: ON");

		if( !normal )
			SetWindowText(hButton4, L"Normal maps: OFF");
		else if( normal )
			SetWindowText(hButton4, L"Normal maps: ON");

		if( !decals )
			SetWindowText(hButton5, L"Draw decals: OFF");
		else if( decals )
			SetWindowText(hButton5, L"Draw decals: ON");

		if( fps == 0 )
			SetWindowText(hButton6, L"FPSlimit: 333");
		else if( fps == 1 )
			SetWindowText(hButton6, L"FPSlimit: 125");
		else if( fps == 2 )
			SetWindowText(hButton6, L"FPSlimit: 250");

		if( !drawFps )
			SetWindowText(hButton7, L"FPSmeter: OFF");
		else if( drawFps )
			SetWindowText(hButton7, L"FPSmeter: ON");
	}

	DWORD WINAPI main( LPVOID param )
	{
		MSG Msg;

		UI_Init( (HMODULE)param );
		getIni();

		Sleep(1500);
		Patch::patch();

		while( GetMessage(&Msg, NULL, 0, 0) > 0 )
	    {
	        TranslateMessage( &Msg );
	        DispatchMessage( &Msg );
	        changeBtnText();
	    }

		UI_Shutdown();
		FreeLibraryAndExitThread( (HMODULE)param, 0 );
		return 0;
	}
}
