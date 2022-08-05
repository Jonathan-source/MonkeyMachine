#include "EnginePCH.h"
#include "Window.h"

MonkeyMachine::Window* MonkeyMachine::Window::Create(const WindowProps& props)
{
	return new Window(props);
}

MonkeyMachine::Window::Window(const WindowProps& props)
	: m_props(props)
{
}

MonkeyMachine::WindowProps MonkeyMachine::Window::GetProperties() const
{
	return m_props;
}