#include "slnpch.h"
#include <glad/glad.h>
#include "GlfwWindow.h"

#include "EventSystem/WindowEvent.h"
#include "EventSystem/MouseEvent.h"
#include "EventSystem/KeyEvent.h"

namespace Selene 
{
	// Forward declarations for Glfw callbacks
	void OnError(int error, const char* description);
	void OnWindowClose(GLFWwindow* window);
	void OnWindowResize(GLFWwindow* window, int width, int height);
	void OnMouseButtonAction(GLFWwindow* window, int button, int action, int mods);
	void OnKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnCharType(GLFWwindow* window, unsigned int codepoint);

	Window* Window::Create(const WindowSettings& settings)
	{
		return new GlfwWindow(settings);
	}

	GlfwWindow::GlfwWindow(const WindowSettings & settings)
	{
		m_Data.Title = settings.Title;
		m_Data.Width = settings.Width;
		m_Data.Height = settings.Height;

		Init();
	}

	GlfwWindow::~GlfwWindow()
	{
		Destroy();
	}

	void GlfwWindow::Init()
	{
		// Init Glfw
		SLN_ENGINE_INFO("Initializing Glfw");
		int glfwInitSuccess = glfwInit();
		
		if (!glfwInitSuccess)
		{
			SLN_ENGINE_CRITICAL("Failed to initialize Glfw");
		}
		
		// Create window
		SLN_ENGINE_INFO("Creating window [{0} ({1}, {2}])", m_Data.Title, m_Data.Width, m_Data.Height);
		m_Window = glfwCreateWindow(m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		if (m_Window == NULL)
		{
			SLN_ENGINE_CRITICAL("Failed to create GLFW window");
		}
		
		// Create OpenGL Context
		glfwMakeContextCurrent(m_Window);

		// Init Glad
		SLN_ENGINE_INFO("Initializing Glad");
		int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!gladInitSuccess)
		{
			SLN_ENGINE_CRITICAL("Failed to initialize Glad");
		}

		// Glfw additional settings
		SetVSync(true);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		// Set callbacks
		glfwSetErrorCallback(OnError);
		glfwSetWindowCloseCallback(m_Window, OnWindowClose);
		glfwSetWindowSizeCallback(m_Window, OnWindowResize);
		glfwSetMouseButtonCallback(m_Window, OnMouseButtonAction);
		glfwSetKeyCallback(m_Window, OnKeyAction);
		glfwSetCharCallback(m_Window, OnCharType);

		// OpenGl Infos
		SLN_ENGINE_INFO("OpenGL Vendor : {0}", glGetString(GL_VENDOR));
		SLN_ENGINE_INFO("OpenGL Renderer : {0}", glGetString(GL_RENDERER));
		SLN_ENGINE_INFO("OpenGL Version : {0}", glGetString(GL_VERSION));
		SLN_ENGINE_INFO("OpenGL Shading Language Version : {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
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
		m_Data.VSync = enabled;
	}

	// Glfw callbacks implementation

	void OnError(int error, const char * description)
	{
		SLN_ENGINE_ERROR("Glfw Error ({0}): {1}", error, description);
	}

	void OnWindowClose(GLFWwindow * window)
	{
		GlfwWindowData& data = *(static_cast<GlfwWindowData*>(glfwGetWindowUserPointer(window)));
		data.EventCallback(WindowCloseEvent());
	}

	void OnWindowResize(GLFWwindow * window, int width, int height)
	{
		GlfwWindowData& data = *(static_cast<GlfwWindowData*>(glfwGetWindowUserPointer(window)));
		data.EventCallback(WindowResizeEvent(width, height));
	}

	void OnMouseButtonAction(GLFWwindow * window, int button, int action, int mods)
	{
		GlfwWindowData& data = *(static_cast<GlfwWindowData*>(glfwGetWindowUserPointer(window)));

		switch (action)
		{
			case GLFW_PRESS:
				data.EventCallback(MouseButtonPressEvent(button));
				break;
			case GLFW_RELEASE:
				data.EventCallback(MouseButtonReleaseEvent(button));
				break;
		}
	}

	void OnKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GlfwWindowData& data = *(static_cast<GlfwWindowData*>(glfwGetWindowUserPointer(window)));

		switch (action)
		{
			case GLFW_PRESS:
				data.EventCallback(KeyPressEvent(key,false));
				break;
			case GLFW_RELEASE:
				data.EventCallback(KeyReleaseEvent(key));
				break;
			case GLFW_REPEAT:
				data.EventCallback(KeyPressEvent(key, true));
				break;
		}
	}

	void OnCharType(GLFWwindow* window, unsigned int codepoint)
	{
		GlfwWindowData& data = *(static_cast<GlfwWindowData*>(glfwGetWindowUserPointer(window)));
		data.EventCallback(KeyTypeEvent(codepoint));
	}
}