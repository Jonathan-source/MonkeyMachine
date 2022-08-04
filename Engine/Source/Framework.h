#pragma once

#define ENTRYAPP(x) IApplication* CreateApplication() { return new x(); }

#ifdef _WIN32
	#ifdef BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error MonkeyMachine only supports Windows!
#endif