#pragma once

extern Application* CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	auto app = CreateApplication(argc, argv);

	app->Run();

	delete app;

	return 0;
}