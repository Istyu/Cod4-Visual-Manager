// stdafx.hpp: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define _USE_MATH_DEFINES
#define NOMINMAX

#ifndef DEV
#define DEV false
#endif

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <cstdint> // for uint32_t type

#include <WinSock2.h>
#include <unordered_map>

#include <winsock.h>
#include <stdint.h>
#include <ShlObj.h>
#include <timeapi.h>

#include <mutex>

#include <iostream>
#include <fstream>
#include <assert.h>
#include <ranges>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <utility>

#include <sstream>
#include <map>
#include <thread>
#include <filesystem>
#include <optional>
#include <queue>

using namespace std::literals;

#include <Urlmon.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <shellapi.h>
#include <wininet.h>
#include <Shlwapi.h>
#include <dwmapi.h>

#pragma comment (lib, "dwmapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winmm.Lib")
#pragma comment(lib, "dbghelp.lib")

// Ignore the warnings
#pragma warning(push)
#pragma warning(disable: 4005)
#pragma warning(disable: 4091)
#pragma warning(disable: 4100)
#pragma warning(disable: 4244)
#pragma warning(disable: 4389)
#pragma warning(disable: 4702)
#pragma warning(disable: 4800)
#pragma warning(disable: 4996) // _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 5054)
#pragma warning(disable: 6001)
#pragma warning(disable: 6011)
#pragma warning(disable: 6031)
#pragma warning(disable: 6255)
#pragma warning(disable: 6258)
#pragma warning(disable: 6386)
#pragma warning(disable: 6387)
#pragma warning(disable: 26812)

#include "..\includes\injector\injector.hpp"
//#include "..\includes\IniReader.h"

#include "Game\Structs.hpp"
#include "Game\Functions.hpp"
#include "Game\Dvars.hpp"
#include "Game\System.hpp"

#include "Components\Modules\_common.hpp"
#include "Components\Modules\_ui.hpp"

#include "Components\Loader.hpp"