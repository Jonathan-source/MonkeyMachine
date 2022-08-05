#include "EnginePCH.h"
#include "Window.h"

const LPCWSTR CLASS_NAME = L"MyWindowClass";

int64_t __stdcall MonkeyMachine::Window::WndProc(void* hWnd, uint32_t msg, uint64_t wParam, int64_t lParam)
{
    auto* referenceWindow = (Window*)::GetWindowLongPtr(static_cast<HWND>(hWnd), 0);
    if (!referenceWindow)
    {
        return ::DefWindowProc(static_cast<HWND>(hWnd), msg, wParam, lParam);
    }

    switch (msg)
    {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) 
            {
                ::CloseWindow(static_cast<HWND>(hWnd));
                ::PostQuitMessage(0);
                return 0;
            }
            break;
        case WM_CLOSE:
        case WM_DESTROY:
        {
            ::CloseWindow(static_cast<HWND>(hWnd));
            ::PostQuitMessage(0);
            return 0;
        }
        case WM_DISPLAYCHANGE:
        case WM_SIZE:
        {
            uint32_t width = static_cast<uint32_t>(lParam & 0xffff);
            uint32_t height = static_cast<uint32_t>((lParam >> 16) & 0xffff);
            // static_cast<uint32_t>(LOWORD(lParam)), static_cast<uint32_t>(HIWORD(lParam))
            referenceWindow->OnResize(width, height);

            if (referenceWindow->onResize)
                referenceWindow->onResize(width, height);

            break;
        }
        default:
            break;
    }

    return ::DefWindowProc(static_cast<HWND>(hWnd), msg, wParam, lParam);
}

MonkeyMachine::Window* MonkeyMachine::Window::Create(const WindowProps& props)
{
	return new Window(props);
}

MonkeyMachine::Window::Window(const WindowProps& props)
	: m_props(props)
    , onResize(nullptr)
{
    Initialize();
}

MonkeyMachine::Window::~Window()
{
    ::UnregisterClass(CLASS_NAME, ::GetModuleHandle(nullptr));
}

void MonkeyMachine::Window::Initialize()
{
    std::wstring title; 
    title.assign(m_props.title.begin(), m_props.title.end());

    const auto moduleHandle = ::GetModuleHandle(nullptr);

    WNDCLASSEX windowDesc{};
    windowDesc.cbSize = sizeof(WNDCLASSEX);
    windowDesc.style = CS_HREDRAW | CS_VREDRAW;
    windowDesc.lpfnWndProc = (WNDPROC)&WndProc;
    windowDesc.cbClsExtra = 0;
    windowDesc.cbWndExtra = sizeof(this);
    windowDesc.hInstance = moduleHandle;
    windowDesc.hIcon = nullptr;
    windowDesc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowDesc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 2);
    windowDesc.lpszMenuName = nullptr;
    windowDesc.lpszClassName = CLASS_NAME;
    windowDesc.hIconSm = nullptr;

    if(!::RegisterClassEx(&windowDesc))
        ::MessageBoxA(nullptr, "Window Class Registration Failed!", "Fatal Error!", MB_ICONEXCLAMATION | MB_OK);

    HWND handle = ::CreateWindowEx(
        0, //WS_EX_CLIENTEDGE,
        CLASS_NAME,
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_props.width, m_props.height,
        nullptr, nullptr, moduleHandle, nullptr
    );

    if (!handle)
    {
        MessageBox(nullptr, L"Window Creation Failed!", L"Fatal Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // Save this class instance in the per - window memory.
    ::SetWindowLongPtr(static_cast<HWND>(handle), 0, (LONG_PTR)this);

    bool fullscreen = false;
    if (fullscreen) ::ShowWindow(handle, SW_SHOWMAXIMIZED);
    else ::ShowWindow(handle, SW_SHOWNORMAL);
    ::UpdateWindow(handle);
    ::SetFocus(handle);

    // We need to resend the initial WM_SIZE message since the first one arrives before our per-instance memory is set (thus getting ignored).
    // Without this, the UI scaling is off until the next WM_SIZE message.

    RECT clientRect;
    ::GetClientRect(static_cast<HWND>(handle), &clientRect);
    const auto clientWidth = clientRect.right - clientRect.left;
    const auto clientHeight = clientRect.bottom - clientRect.top;

    ::PostMessage(static_cast<HWND>(handle), WM_SIZE, SIZE_RESTORED, (clientWidth & 0xFFFF) | ((clientHeight & 0xFFFF) << 16));
}

void MonkeyMachine::Window::OnResize(uint32_t width, uint32_t height)
{
    m_props.width = width;
    m_props.height = height;
}

MonkeyMachine::WindowProps MonkeyMachine::Window::GetProperties() const
{
	return m_props;
}

bool MonkeyMachine::Window::Loop()
{
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT) return false;
    }
    return true;
}