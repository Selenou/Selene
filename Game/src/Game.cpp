#include <Selene.h>

class Game : public Selene::BaseApplication 
{
public:
	Game()
	{
	}

	~Game()
	{
	}
};

Selene::BaseApplication* Selene::CreateApplication() 
{
	return new Game();
}