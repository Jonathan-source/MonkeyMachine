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
		virtual ~Window() = default;

		static Window* Create(const WindowProps& props = WindowProps());

		WindowProps GetProperties() const;

	private:
		Window(const WindowProps& props);

		WindowProps m_props;
	};

} // end of namespace