#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define HInstance() GetModuleHandle(NULL)
#define SHADER(CODE) #CODE
#define SAFE_RELEASE(p) if(p) (p)->Release()
#define SAFE_DÉLETE(p) if(p) (delete p)

// DirectX 11 specific headers
#include <d3d11.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>

using namespace Microsoft::WRL;

// ============================================================================

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ============================================================================

// Standard
#include <string>
#include <string_view>
#include <exception>
#include <chrono>
#include <iostream>
#include <memory>
#include <cassert> 
#include <functional>
#include <sstream>

#include <vector>
#include <array>
#include <set>
#include <queue>
#include <unordered_map>
#include <stack>

#include <fcntl.h>
#include <io.h>
#include <crtdbg.h>


// Report an error to the Debug output in Visual Studio, display a message box with the error message and throw an exception.
inline void ReportErrorAndThrow(const std::string& file, int line, const std::string& function, const std::string& message)
{
    std::stringstream ss;

    DWORD errorCode = GetLastError();
    LPTSTR errorMessage = nullptr;

    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errorMessage, 0, nullptr);

    if (errorMessage)
    {
        ss << file << "(" << line << "): " << "error " << errorCode << ": " << errorMessage << std::endl;
        ::LocalFree(errorMessage);
    }
    else
    {
        ss << file << "(" << line << "): " << message << std::endl;
    }

    ::OutputDebugStringA(ss.str().c_str());
    ::MessageBoxA(nullptr, message.c_str(), function.c_str(), MB_ICONERROR);
    throw new std::exception(message.c_str());
}

// Report an error message and throw an std::exception.
#define ReportError( msg ) ::ReportErrorAndThrow( __FILE__, __LINE__, __FUNCTION__, (msg) )