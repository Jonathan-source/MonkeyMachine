#include "pch.h"
#include "Sandbox.h"

using namespace MonkeyMachine;

ENTRYAPP(Sandbox)

void Sandbox::OnStartup()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Sandbox::OnInput()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Sandbox::OnUpdate(float deltaTime)
{
	std::cout << __FUNCTION__ << std::endl;
}

void Sandbox::OnRender()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Sandbox::OnShutdown()
{
	std::cout << __FUNCTION__ << std::endl;
}
