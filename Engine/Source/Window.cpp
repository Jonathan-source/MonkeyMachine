#include "EnginePCH.h"
#include "Window.h"

#define WINDOW_CLASS_NAME "MonkeyWindowClass"


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
        {
            if (wParam == VK_ESCAPE)
            {
                ::CloseWindow(static_cast<HWND>(hWnd));
                ::DestroyWindow(static_cast<HWND>(hWnd));
                ::PostQuitMessage(0);
                return 0;
            }

            unsigned char keycode = static_cast<unsigned char>(wParam);
            std::cout << keycode << std::endl;

            break;
        }
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
            uint32_t width = static_cast<uint32_t>(lParam & 0xffff); // static_cast<uint32_t>(LOWORD(lParam))
            uint32_t height = static_cast<uint32_t>((lParam >> 16) & 0xffff); // static_cast<uint32_t>(HIWORD(lParam))
            referenceWindow->SetSize(width, height);

            if (referenceWindow->OnResize)
                referenceWindow->OnResize(width, height);

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
    , OnResize(nullptr)
{
    RegisterWindowClass();
    CreateRenderWindow();
}

void MonkeyMachine::Window::RegisterWindowClass()
{
    m_hInstance = ::GetModuleHandle(nullptr);

    WNDCLASSEX windowDesc{};
    windowDesc.cbSize = sizeof(WNDCLASSEX);
    windowDesc.style = CS_HREDRAW | CS_VREDRAW;
    windowDesc.lpfnWndProc = (WNDPROC)&WndProc;
    windowDesc.cbClsExtra = 0;
    windowDesc.cbWndExtra = sizeof(this);
    windowDesc.hInstance = m_hInstance;
    windowDesc.hIcon = nullptr;
    windowDesc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowDesc.hbrBackground = (HBRUSH)::CreateSolidBrush(RGB(100, 149, 237));
    windowDesc.lpszMenuName = nullptr;
    windowDesc.lpszClassName = WINDOW_CLASS_NAME;
    windowDesc.hIconSm = nullptr;

    if (!::RegisterClassEx(&windowDesc))
    {
        ReportError("Window Class Registration Failed!");
    }
}

void MonkeyMachine::Window::CreateRenderWindow()
{
    int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

    RECT windowRect = { 0, 0, (LONG)m_props.width, (LONG)m_props.height };

    ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    m_props.width = windowRect.right - windowRect.left;
    m_props.height = windowRect.bottom - windowRect.top;

    int windowX = (screenWidth - m_props.width) / 2;
    int windowY = (screenHeight - m_props.height) / 2;

    HWND windowHandle = ::CreateWindowEx(NULL,
        WINDOW_CLASS_NAME,
        m_props.title.c_str(),
        WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
        windowX, windowY, m_props.width, m_props.height,
        nullptr, nullptr, m_hInstance, nullptr
    );

    if (!windowHandle)
    {
        ReportError("Failed to create render window.");
    }

    // Save this class instance in the per - window memory.
    ::SetWindowLongPtr(static_cast<HWND>(windowHandle), 0, (LONG_PTR)this);

    if (m_props.isFullscreen) ::ShowWindow(windowHandle, SW_SHOWMAXIMIZED);
    else ::ShowWindow(windowHandle, SW_SHOWNORMAL);
    ::UpdateWindow(windowHandle);
    ::SetFocus(windowHandle);

    // We need to resend the initial WM_SIZE message since the first one 
    // arrives before our per-instance memory is set. Without this, the UI
    // scaling is off until the next WM_SIZE message.

    RECT clientRect{};
    ::GetClientRect(static_cast<HWND>(windowHandle), &clientRect);
    const auto clientWidth = clientRect.right - clientRect.left;
    const auto clientHeight = clientRect.bottom - clientRect.top;

    ::PostMessage(static_cast<HWND>(windowHandle), WM_SIZE, SIZE_RESTORED, (clientWidth & 0xFFFF) | ((clientHeight & 0xFFFF) << 16));
}

MonkeyMachine::Window::~Window()
{
    if (!UnregisterClass(WINDOW_CLASS_NAME, m_hInstance))
    {
        ReportError("Failed to unregister render window class");
    }
}

void MonkeyMachine::Window::SetSize(uint32_t width, uint32_t height)
{
    m_props.width = width;
    m_props.height = height;
}

MonkeyMachine::WindowProps MonkeyMachine::Window::GetProperties() const
{
	return m_props;
}

bool MonkeyMachine::Window::RunMessageLoop()
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