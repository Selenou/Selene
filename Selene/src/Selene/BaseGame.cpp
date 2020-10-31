#include "slnpch.h"
#include "BaseGame.h"

#include <GLFW/glfw3.h>

namespace Selene {

	BaseGame::BaseGame()
	{

	}

	BaseGame::~BaseGame()
	{

	}

	void BaseGame::Run()
	{
		GLFWwindow* window;
		glfwInit();
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		glfwMakeContextCurrent(window);
		
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
	}

}