#include "#projectName.h"

#include "#sceneName.h"
#include "Core/EntryPoint.h"

Application* CreateApplication(int argc, char** argv)
{
	return new #projectName();
}

#projectName::#projectName()
	: Application()
{
	AddScene<#sceneName>("#sceneName");
}

#projectName::~#projectName()
{

}

void #projectName::Begin()
{
	Application::Begin();
	PrintHirarchiesOnConsole();
}

void #projectName::Update()
{
	Application::Update();
}