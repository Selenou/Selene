#include <Selene.h>

class TestLayer : public Selene::Layer
{
public:
	TestLayer() {}

	void Update() override 
	{
		//SLN_INFO("Update");
	}
};

class DoomGame : public Selene::Game
{
public:
	DoomGame()
	{
		PushLayer(new TestLayer());
	}

	~DoomGame()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new DoomGame();
}