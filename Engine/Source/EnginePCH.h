#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define HInstance() GetModuleHandle(NULL)
#define SHADER(CODE) #CODE

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

#include <vector>
#include <array>
#include <set>
#include <queue>
#include <unordered_map>
#include <stack>

#include <fcntl.h>
#include <io.h>
#include <crtdbg.h>
