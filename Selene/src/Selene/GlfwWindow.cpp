#include "slnpch.h"
#include "GlfwWindow.h"
//#include "stb_image.h"

namespace Selene {

	Window* Window::Create(const WindowData& data)
	{
		return new GlfwWindow(data);
	}

	GlfwWindow::GlfwWindow(const WindowData & data)
	{
		Init(data);
	}

	GlfwWindow::~GlfwWindow()
	{
		Destroy();
	}

	void GlfwWindow::Init(const WindowData & data)
	{
		m_Data.Title = data.Title;
		m_Data.Width = data.Width;
		m_Data.Height = data.Height;

		int success = glfwInit();
		SLN_ENGINE_INFO("Initializing Glfw");

		if (!success)
		{
			SLN_ENGINE_ERROR("Failed to initialize Glfw");
			//TODO : Manage error
		}

		m_Window = glfwCreateWindow(m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		SLN_ENGINE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (m_Window == NULL)
		{
			SLN_ENGINE_ERROR("Failed to create GLFW window");
			//TODO : Manage error
		}

		/* need to place image in Game/
		GLFWimage images[2];
		int width, height, channels;
		std::string str = "moon.png";
		stbi_uc* iconImage = stbi_load(str.c_str(), &width, &height, &channels, 0);
		images[0].height = height;
		images[0].width = width;
		images[0].pixels = iconImage;
		glfwSetWindowIcon(m_Window, 1, images);
		stbi_image_free(iconImage);
		*/

		glfwMakeContextCurrent(m_Window);
		SetVSync(true);
	}

	void GlfwWindow::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void GlfwWindow::Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void GlfwWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
	}

}
