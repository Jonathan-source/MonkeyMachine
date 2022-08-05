#include "EnginePCH.h"
#include "Window.h"

int64_t __stdcall MonkeyMachine::WndProc(void* hWnd, uint32_t msg, uint64_t wParam, int64_t lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(static_cast<HWND>(hWnd), msg, wParam, lParam);
}

MonkeyMachine::Window* MonkeyMachine::Window::Create(const WindowProps& props)
{
	return new Window(props);
}

MonkeyMachine::Window::Window(const WindowProps& props)
	: m_props(props)
{
    Initialize();
}

void MonkeyMachine::Window::Initialize()
{
    std::wstring title; 
    title.assign(m_props.title.begin(), m_props.title.end());
    const LPCWSTR CLASS_NAME = L"MyWindowClass";

    const auto moduleHandle = ::GetModuleHandle(nullptr);

    WNDCLASSEX wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)&WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = moduleHandle;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = CLASS_NAME;
    wcex.hIconSm = nullptr;

    if (!::RegisterClassExW(&wcex))
        ::MessageBoxA(nullptr, "Window Class Registration Failed!", "Fatal Error!", MB_ICONEXCLAMATION | MB_OK);

    HWND handle = ::CreateWindowExW
    (
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