#include <Selene.h>

class Game : public Selene::BaseGame
{
public:
	Game()
	{
	}

	~Game()
	{
	}
};

Selene::BaseGame* Selene::CreateGame() 
{
	return new Game();
}