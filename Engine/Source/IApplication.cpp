#include "EnginePCH.h"
#include "IApplication.h"

void MonkeyMachine::IApplication::Run()
{
	OnStartup();

	int frameCounter = 0;
	m_isRunning = true;
	while (m_isRunning)
	{
		// if input then
		OnInput();

		OnUpdate(frameCounter++);

		OnRender();
	}

	OnShutdown();
}

void MonkeyMachine::IApplication::Shutdown()
{
	m_isRunning = false;
}
