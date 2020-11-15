#include "slnpch.h"
#include "VulkanContext.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Selene
{
	void VulkanContext::Init()
	{
		SLN_ENGINE_INFO("Initializing Vulkan");

		int success = glfwVulkanSupported();

		if (!success)
		{
			SLN_ENGINE_CRITICAL("Failed to initialize Vulkan");
		}
	}
}