#include "EnginePCH.h"
#include "IApplication.h"
#include "Timer.h"


MonkeyMachine::IApplication::IApplication()
	: m_isRunning(true)
{
	m_pWindow = Window::Create();
}

MonkeyMachine::IApplication::~IApplication()
{
	SAFE_DÉLETE(m_pWindow);
}

void MonkeyMachine::IApplication::Run()
{
	OnStartup();

	Timer deltaTimer;

	while (m_pWindow->RunMessageLoop())
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
