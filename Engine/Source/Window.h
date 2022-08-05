#pragma once

#include "Framework.h"

namespace MonkeyMachine
{
	struct WindowProps
	{
		std::string title;
		uint32_t width;
		uint32_t height;
	
		WindowProps(const std::string& title = "MonkeyMachine",
			uint32_t width = 800u,
			uint32_t height = 600u)
			: title(title), width(width), height(height)
		{
		}
	};

	class Window
	{
	public:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		Window(Window&&) = delete;
		virtual ~Window();

		static Window* Create(const WindowProps& props = WindowProps());

		bool Loop();

		WindowProps GetProperties() const;

		void OnResize(uint32_t width, uint32_t height);

	public:
		// Callbacks
		std::function<void(uint32_t, uint32_t)> onResize;

		static int64_t __stdcall WndProc(void* hWnd, uint32_t msg, uint64_t wParam, int64_t lParam);

	private:
		Window(const WindowProps& props);

		WindowProps m_props;

		void Initialize();
	};

} // end of namespace