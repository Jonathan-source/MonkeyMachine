#include "pch.h"

#include <MonkeyMachine.h>

class Sandbox : public MonkeyMachine::IApplication
{
public:
	Sandbox() = default;
	virtual ~Sandbox() = default;
};

int main()
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Print();
	delete sandbox;

	return 0;
}