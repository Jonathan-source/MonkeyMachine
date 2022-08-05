#include <MonkeyMachine.h>

class Sandbox : public MonkeyMachine::IApplication
{
public:
	Sandbox() = default;
	virtual ~Sandbox() = default;

	// Inherited via IApplication
	virtual void OnStartup() override;

	virtual void OnInput() override;

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnRender() override;

	virtual void OnShutdown() override;

private:

};