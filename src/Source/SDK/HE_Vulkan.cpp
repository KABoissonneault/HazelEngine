#include "HE_Vulkan.h"

namespace vk
{
	VkInstanceCreateInfo MakeInstanceCreateInfo(const VkApplicationInfo* pApplicationInfo, 
		gsl::span<const char* const> pEnabledLayerNames, 
		gsl::span<const char* const> pEnabledExtensionNames)
	{
		VkInstanceCreateInfo ret;
		ret.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ret.pNext = nullptr;
		ret.flags = 0;
		ret.pApplicationInfo = pApplicationInfo;
		ret.enabledLayerCount = static_cast<uint32_t>(pEnabledLayerNames.size());
		ret.ppEnabledExtensionNames = &*pEnabledLayerNames.begin();
		ret.enabledExtensionCount = static_cast<uint32_t>(pEnabledExtensionNames.size());
		ret.ppEnabledExtensionNames = &*pEnabledExtensionNames.begin();

		return ret;
	}

	VkApplicationInfo MakeApplicationInfo(const char* pApplicationName, uint32_t applicationVersion)
	{
		VkApplicationInfo ret;
		ret.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		ret.pNext = nullptr;
		ret.pApplicationName = pApplicationName;
		ret.applicationVersion = applicationVersion;
		ret.pEngineName = "HazelEngine";
		ret.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		ret.apiVersion = VK_API_VERSION;

		return ret;
	}

	VkInstance CreateInstance(const VkInstanceCreateInfo& pCreateInfo, const VkAllocationCallbacks* pAllocator)
	{
		VkInstance instance;
		auto const err = vkCreateInstance(&pCreateInfo, pAllocator, &instance);
		Private::CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY,
			VK_ERROR_INITIALIZATION_FAILED, VK_ERROR_LAYER_NOT_PRESENT,
			VK_ERROR_EXTENSION_NOT_PRESENT, VK_ERROR_INCOMPATIBLE_DRIVER>(err, "CreateInstance");
		return instance;
	}

	void DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) noexcept
	{
		vkDestroyInstance(instance, pAllocator);
	}
}