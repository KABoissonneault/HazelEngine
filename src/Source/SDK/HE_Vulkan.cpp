#include "HE_Vulkan.h"

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
		CheckError<VK_ERROR_OUT_OF_HOST_MEMORY, VK_ERROR_OUT_OF_DEVICE_MEMORY,
			VK_ERROR_INITIALIZATION_FAILED, VK_ERROR_LAYER_NOT_PRESENT,
			VK_ERROR_EXTENSION_NOT_PRESENT, VK_ERROR_INCOMPATIBLE_DRIVER>(err, "CreateInstance");
		return instance;
	}

	void DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) noexcept
	{
		vkDestroyInstance(instance, pAllocator);
	}
}