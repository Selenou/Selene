#pragma once

extern Selene::Game* Selene::CreateGame();

int main(int argc, char** argv)
{
	Selene::Log::Init();

	auto game = Selene::CreateGame();
	game->Run();
	delete game;
}