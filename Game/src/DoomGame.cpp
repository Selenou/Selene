#include <Selene.h>

class DoomGame : public Selene::Game
{
public:
	DoomGame()
	{
	}

	~DoomGame()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new DoomGame();
}