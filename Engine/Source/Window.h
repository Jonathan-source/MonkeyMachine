#pragma once

// Forward declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Defined in the Application class.

class Window
{
public:
	Window();
	virtual ~Window();

    void ShowWindow();

    void HideWindow();

    void CloseWindow();

    const std::string& GetWindowName() const;

    uint32_t GetWindowWidth() const;

    uint32_t GetWindowHeight() const;

    bool IsVSync() const;

    void SetVSync(bool vSync);

    bool IsFullScreen() const;

    void SetFullScreen(bool fullscreen);

    void OnInitialize();

    void UpdateWindowSize(int32_t x, int32_t y);

    void UpdateMouseWheel(int32_t delta);

    void UpdateMouseFocus(bool state);

    void UpdateKeyFocus(bool state);

    void UpdateKeyState();

    void UpdateMouseState(int32_t button, bool state);

    void Terminate();

private:
    uint32_t m_width;
    uint32_t m_height;

    bool m_isVSync;
    bool m_isFullScreen;

    std::string m_title;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//switch (uMsg)
	//{
	//case WM_CREATE:
	//{
	//	LOG_INFO("WindowExA was created.")
	//		break;
	//}

	//case WM_MOUSEMOVE:
	//{
	//	// Thanks @ForAbby (Discord)
	//	uint16_t x = lParam & 0xFFFF; uint16_t y = (lParam >> 16) & 0xFFFF;
	//	int16_t ix = *(int16_t*)&x;   int16_t iy = *(int16_t*)&y;
	//	UpdateMouse(ix, iy);
	//	return 0;
	//}

	//case WM_SIZE:			UpdateWindowSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF);	return 0;
	//case WM_MOUSEWHEEL:		UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));           return 0;
	//case WM_MOUSELEAVE:		UpdateMouseFocus(false);                                    return 0;
	//case WM_SETFOCUS:		UpdateKeyFocus(true);                                       return 0;
	//case WM_KILLFOCUS:		UpdateKeyFocus(false);                                      return 0;
	//case WM_KEYDOWN:		UpdateKeyState(mapKeys[wParam], true);                      return 0;
	//case WM_KEYUP:			UpdateKeyState(mapKeys[wParam], false);                     return 0;
	//case WM_SYSKEYDOWN:		UpdateKeyState(mapKeys[wParam], true);						return 0;
	//case WM_SYSKEYUP:		UpdateKeyState(mapKeys[wParam], false);						return 0;
	//case WM_LBUTTONDOWN:	UpdateMouseState(0, true);                                  return 0;
	//case WM_LBUTTONUP:		UpdateMouseState(0, false);                                 return 0;
	//case WM_RBUTTONDOWN:	UpdateMouseState(1, true);                                  return 0;
	//case WM_RBUTTONUP:		UpdateMouseState(1, false);                                 return 0;
	//case WM_MBUTTONDOWN:	UpdateMouseState(2, true);                                  return 0;
	//case WM_MBUTTONUP:		UpdateMouseState(2, false);                                 return 0;
	//case WM_CLOSE:			Terminate();                                                return 0;
	//case WM_DESTROY:		PostQuitMessage(0); DestroyWindow(hWnd);					return 0;
	//default:
	//	break;
	//}

	// Resize(width, height) == (UINT)(UINT64)lParam & 0xFFFF, (UINT)(UINT64)lParam >> 16)

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

