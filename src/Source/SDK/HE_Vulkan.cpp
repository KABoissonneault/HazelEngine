#include "HE_Vulkan.h"

#include <map>
#include <string>

#include "HE_String.h"

using namespace std::string_literals;

namespace vk
{
	ResultErrorException::ResultErrorException(VkResult e) 
		: m_sMessage{ "Vulkan returned error "s + to_string(e) } 
	{ }

	ResultErrorException::ResultErrorException(VkResult e, gsl::cstring_span<> sContext)
		: m_sMessage{ HE::Format("Vulkan returned error {0} from: {1}", e, sContext) }
	{ }

	const char* ResultErrorException::what() const
	{
		return m_sMessage.c_str();
	}

	namespace
	{
		template<typename... String>
		void CheckErrorImpl(VkResult result, std::initializer_list<VkResult> results, String... s)
		{
			auto const pError = std::find(begin(results), end(results), result);
			if (pError != end(results))
			{
				throw ResultErrorException{ result, s... };
			}
		}

		template<VkResult... Errors>
		void CheckError(VkResult err)
		{
			if (err != VK_SUCCESS)
			{
				CheckErrorImpl(err, { Errors... });
			}
		}

		template<VkResult... Errors>
		void CheckError(VkResult err, gsl::cstring_span<> sContext)
		{
			if (err != VK_SUCCESS)
			{
				CheckErrorImpl(err, { Errors... }, sContext);
			}
		}
	}

	VkInstanceCreateInfo MakeInstanceCreateInfo(const VkApplicationInfo* pApplicationInfo, 
		gsl::span<gsl::czstring<> const> enabledLayerNames,
		gsl::span<gsl::czstring<> const> enabledExtensionNames,
		const void* pNext) noexcept
	{
		VkInstanceCreateInfo ret;
		ret.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ret.pNext = pNext;
		ret.flags = 0;
		ret.pApplicationInfo = pApplicationInfo;
		ret.enabledLayerCount = static_cast<uint32_t>(pEnabledLayerNames.size());
		ret.ppEnabledLayerNames = pEnabledLayerNames.size() != 0 ? &*pEnabledLayerNames.begin() : nullptr;
		ret.enabledExtensionCount = static_cast<uint32_t>(pEnabledExtensionNames.size());
		ret.ppEnabledExtensionNames = pEnabledExtensionNames.size() != 0  ? &*pEnabledExtensionNames.begin() : nullptr;

		return ret;
	}

	VkApplicationInfo MakeApplicationInfo(const char* pApplicationName, uint32_t applicationVersion, const void* pNext) noexcept
	{
		VkApplicationInfo ret;
		ret.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		ret.pNext = pNext;
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
		CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY,
			VK_ERROR_INITIALIZATION_FAILED, VK_ERROR_LAYER_NOT_PRESENT,
			VK_ERROR_EXTENSION_NOT_PRESENT, VK_ERROR_INCOMPATIBLE_DRIVER>(err, "CreateInstance");
		return instance;
	}

	void DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) noexcept
	{
		vkDestroyInstance(instance, pAllocator);
	}

	std::vector<VkPhysicalDevice> EnumeratePhysicalDevices(VkInstance instance)
	{
		uint32_t physicalDeviceCount;
		auto const err1 = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
		CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY, VK_ERROR_INITIALIZATION_FAILED>(err1, "EnumeratePhysicalDevices");

		std::vector<VkPhysicalDevice> devices(physicalDeviceCount);
		auto const err2 = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, devices.data());
		CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY, VK_ERROR_INITIALIZATION_FAILED>(err2, "EnumeratePhysicalDevices");

		return devices;
	}

	VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice) noexcept
	{
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(physicalDevice, &props);
		return props;
	}

	std::vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice) noexcept
	{
		uint32_t physicalDeviceCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &physicalDeviceCount, nullptr);

		std::vector<VkQueueFamilyProperties> deviceQueueFamilyProperties(physicalDeviceCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &physicalDeviceCount, deviceQueueFamilyProperties.data());

		return deviceQueueFamilyProperties;
	}

	VkDeviceCreateInfo MakeDeviceCreateInfo( gsl::span<const VkDeviceQueueCreateInfo> queueCreateInfos,
		gsl::span<char const* const> enabledLayerNames,
		gsl::span<char const* const> enabledExtensionNames,
		VkPhysicalDeviceFeatures const& enabledFeatures,
		const void* pNext
		) noexcept
	{
		VkDeviceCreateInfo ret;
		ret.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		ret.pNext = pNext;
		ret.flags = 0;
		ret.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		ret.pQueueCreateInfos = queueCreateInfos.size() != 0 ? &*queueCreateInfos.begin() : nullptr;
		ret.enabledLayerCount = static_cast<uint32_t>(enabledLayerNames.size());
		ret.ppEnabledLayerNames = enabledLayerNames.size() != 0 ? &*enabledLayerNames.begin() : nullptr;
		ret.enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size());
		ret.ppEnabledExtensionNames = enabledExtensionNames.size() != 0 ? &*enabledExtensionNames.begin() : nullptr;
		ret.pEnabledFeatures = &enabledFeatures;

		return ret;
	}

	VkDevice CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& createInfo, const VkAllocationCallbacks* pAllocator)
	{
		VkDevice device;

		auto const err = vkCreateDevice(physicalDevice, &createInfo, pAllocator, &device);
		CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY,
			VK_ERROR_INITIALIZATION_FAILED, VK_ERROR_LAYER_NOT_PRESENT,
			VK_ERROR_EXTENSION_NOT_PRESENT, VK_ERROR_FEATURE_NOT_PRESENT,
			VK_ERROR_TOO_MANY_OBJECTS, VK_ERROR_DEVICE_LOST>(err);

		return device;
	}

	void DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) noexcept
	{
		vkDestroyDevice(device, pAllocator);
	}

	void DeviceWaitIdle(VkDevice device)
	{
		auto const err = vkDeviceWaitIdle(device);
		CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY,
			VK_ERROR_DEVICE_LOST>(err);
	}

	namespace PhysicalDeviceType
	{
		namespace
		{
			std::map<VkPhysicalDeviceType, std::string> const s_sPhysicalDeviceTypes{
				{VK_PHYSICAL_DEVICE_TYPE_OTHER, "Other"},
				{VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU, "Integrated GPU"},
				{VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU, "Discrete GPU"},
				{VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU, "Virtual GPU"},
				{VK_PHYSICAL_DEVICE_TYPE_CPU, "CPU"}
			};
		}

		gsl::cstring_span<> String(VkPhysicalDeviceType e)
		{
			return s_sPhysicalDeviceTypes.at(e);
		}
	}
}

std::string to_string(VkPhysicalDeviceType e) { auto const s = vk::PhysicalDeviceType::String(e); return{ s.begin(), s.end() }; }