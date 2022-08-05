/*=====================================================================

	This is an educational project with the single purpose of
	learning DirectX11 and demonstrate various graphical techniques.
	Author: Jonathan Helsing [github.com/Jonathan-source]

 ======================================================================*/

#pragma once

#include "EnginePCH.h"

#include "IApplication.h"

void CreateConsoleWindow(int bufferLines, int bufferColumns, int windowLines, int windowColumns);

#if defined(WIN32) | defined(_WIN32)

	extern MonkeyMachine::IApplication* CreateApplication();

	INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
	{
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);
		UNREFERENCED_PARAMETER(nCmdShow);

#if defined(DEBUG) | defined(_DEBUG)
		CreateConsoleWindow(500, 120, 32, 120);
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

		const auto app = CreateApplication();

		try {
			app->Run();
		}
		catch (const std::exception &error) {
			std::cout << error.what() << std::endl;
		}
		catch (const char* errorMsg) {
			std::cout << errorMsg << std::endl;
		}
	
		delete app;

		return EXIT_SUCCESS;
	}

	void CreateConsoleWindow(int bufferLines, int bufferColumns, int windowLines, int windowColumns)
	{
		// Our temp console info struct
		CONSOLE_SCREEN_BUFFER_INFO coninfo;

		// Get the console info and set the number of lines
		AllocConsole();
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = bufferLines;
		coninfo.dwSize.X = bufferColumns;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		SMALL_RECT rect{};
		rect.Left = 0;
		rect.Top = 0;
		rect.Right = windowColumns;
		rect.Bottom = windowLines;
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);

		FILE* stream;
		freopen_s(&stream, "CONIN$", "r", stdin);
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONOUT$", "w", stderr);

		// Prevent accidental console window close
		HWND consoleHandle = GetConsoleWindow();
		HMENU hmenu = GetSystemMenu(consoleHandle, FALSE);
		EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
	}

#endif