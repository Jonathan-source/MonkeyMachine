#include "EnginePCH.h"
#include "IApplication.h"
#include "Timer.h"

MonkeyMachine::IApplication::IApplication()
	: m_isRunning(true)
{
	m_window = Window::Create();
}

MonkeyMachine::IApplication::~IApplication()
{
	delete m_window;
}

void MonkeyMachine::IApplication::Run()
{
	OnStartup();

	Timer deltaTimer;

	while (m_window->Loop())
	{
		// if input then
		//OnInput();

		OnUpdate(deltaTimer.ElapsedMillis());

		//OnRender();

		deltaTimer.Reset();
	}

	OnShutdown();
}

void MonkeyMachine::IApplication::Shutdown()
{
	m_isRunning = false;
}
