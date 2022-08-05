#pragma once

#include "Framework.h"

#include "Window.h"

namespace MonkeyMachine
{
	class ENGINE_API IApplication
	{
	public:
		IApplication();
		IApplication(const IApplication&) = delete;
		IApplication& operator=(const IApplication&) = delete;
		IApplication& operator=(IApplication&&) = delete;
		IApplication(IApplication&&) = delete;
		virtual ~IApplication();

		void Run();

		void Shutdown();

	protected:
		virtual void OnStartup() = 0;

		virtual void OnInput(/* input event goes here */) = 0;

		virtual void OnUpdate(float deltaTime) = 0;

		virtual void OnRender() = 0;

		virtual void OnShutdown() = 0;
	
	private:
		bool m_isRunning;

		Window* m_window;
	};

} // end of namespace

