#include "slnpch.h"
#include "VulkanContext.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Selene
{
	void VulkanContext::Init()
	{
		SLN_INFO("Initializing Vulkan Rendering Context");

		int success = glfwVulkanSupported();
		SLN_ASSERT(success, "Failed to initialize Vulkan");
	}

	void VulkanContext::Destroy()
	{

	}

	void VulkanContext::SwapBuffers()
	{

	}
}