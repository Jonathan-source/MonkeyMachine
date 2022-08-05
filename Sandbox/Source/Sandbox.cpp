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

}

void Sandbox::OnUpdate(float deltaTime)
{

}

void Sandbox::OnRender()
{

}

void Sandbox::OnShutdown()
{
	std::cout << __FUNCTION__ << std::endl;
}
