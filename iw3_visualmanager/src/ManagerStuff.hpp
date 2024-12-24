#pragma once

namespace Manager
{
	//DWORD WINAPI Init( LPVOID param );

	//class menu
	//{
	//public:
	//	menu();
	//	~menu();

		// Global variables
		//static const char *g_szClassName = L"myWindow" L"myWindowClass";
		static HWND hButton; // Filmtweak
		static HWND hButton2; // Fullbright
		static HWND hButton3; // Specular
		static HWND hButton4; // Normal
		static HWND hButton5; // Draw decals
		static HWND hButton6; // FPSlimit
		static HWND hButton7; // FPSmeter
		static HWND hTrackbar;
		static HWND hLabel;

		static HWND hwnd;

		static int borderless;

		LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
		void UI_Init( HMODULE hInstance );
		void UI_Shutdown( void );
		DWORD WINAPI main( LPVOID param );
	//};
}