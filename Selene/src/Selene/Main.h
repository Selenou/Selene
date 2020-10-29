#pragma once

extern Selene::BaseApplication* Selene::CreateApplication();

int main(int argc, char** argv)
{
	Selene::Log::Init();
	Selene::Log::GetEngineLogger()->warn("This is a warning");
	Selene::Log::GetEngineLogger()->error("This is an error");

	auto app = Selene::CreateApplication();
	app->Run();
	delete app;
}