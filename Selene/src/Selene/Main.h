#pragma once

extern Selene::BaseGame* Selene::CreateGame();

int main(int argc, char** argv)
{
	Selene::Log::Init();
	SLN_ENGINE_WARN("This is a warning");
	SLN_ENGINE_INFO("This is an error");

	auto game = Selene::CreateGame();
	game->Run();
	delete game;
}