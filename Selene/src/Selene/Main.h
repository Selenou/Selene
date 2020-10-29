#pragma once

extern Selene::BaseApplication* Selene::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Selene::CreateApplication();
	app->Run();
	delete app;
}