#pragma once

#include "Framework.h"

namespace MonkeyMachine
{
	class ENGINE_API IApplication
	{
	public:
		IApplication() = default;
		virtual ~IApplication() = default;

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
	};

} // end of namespace

