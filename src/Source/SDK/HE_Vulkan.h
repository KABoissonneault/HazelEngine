#pragma once

#include <vulkan\vulkan.h>

#include <exception>
#include <string_span.h>


#include "HE_String.h"
#include "TMP_Helper.h"

namespace vk
{
	/*
		VkInstanceCreateInfo MakeInstanceCreateInfo(const VkApplicationInfo* pApplicationInfo, 
			gsl::span<const char* const> pEnabledLayerNames = {}, 
			gsl::span<const char* const> pEnabledExtensionNames = {});

		• pApplicationInfo is NULL or a pointer to an instance of VkApplicationInfo. If not NULL, this information
		helps implementations recognize behavior inherent to classes of applications. VkApplicationInfo is defined in
		detail below.
		• pEnabledLayerNames is an array of null-terminated UTF-8 strings containing
		the names of layers to enable.
		• pEnabledExtensionNames is an array of null-terminated UTF-8 strings
		containing the names of extensions to enable.

		Valid Usage:
		• If pApplicationInfo is not NULL, pApplicationInfo must be a pointer to a valid VkApplicationInfo
		structure
		• Any given element of pEnabledLayerNames must be the name of a layer present on the system, exactly
		matching a string returned in the VkLayerProperties structure by
		vkEnumerateInstanceLayerProperties
		• Any given element of pEnabledExtensionNames must be the name of an extension present on the system,
		exactly matching a string returned in the VkExtensionProperties structure by
		vkEnumerateInstanceExtensionProperties
		• If an extension listed in pEnabledExtensionNames is provided as part of a layer, then both the layer and
		extension must be enabled to enable that extension
	*/
	VkInstanceCreateInfo MakeInstanceCreateInfo(const VkApplicationInfo* pApplicationInfo, 
		gsl::span<const char* const> pEnabledLayerNames = {}, 
		gsl::span<const char* const> pEnabledExtensionNames = {});

	/*
		VkApplicationInfo MakeApplicationInfo(const char* pApplicationName, uint32_t applicationVersion);

		• pApplicationName is a pointer to a null-terminated UTF-8 string containing the name of the application.
		• applicationVersion is an unsigned integer variable containing the developer-supplied version number of the
		application.
		• For the engine name, the engine version and the API version, the function assumes "HazelEngine" with the proper version
		and uses VK_API_VERSION

		Valid Usage:
		• If pApplicationName is not NULL, pApplicationName must be a null-terminated string
	*/
	VkApplicationInfo MakeApplicationInfo(const char* pApplicationName, uint32_t applicationVersion);
	
	/*
		VkInstance CreateInstance(const VkInstanceCreateInfo& createInfo, const VkAllocationCallbacks* pAllocator);

		• createInfo refers to an instance of VkInstanceCreateInfo controlling creation of the instance.
		• pAllocator controls host memory allocation
		• returns a VkInstance handle in which the resulting instance is returned.

		Valid Usage:
		• createInfo must refer to a valid VkInstanceCreateInfo structure
		• If pAllocator is not NULL, pAllocator must be a pointer to a valid VkAllocationCallbacks structure
	*/
	VkInstance CreateInstance(const VkInstanceCreateInfo& createInfo, const VkAllocationCallbacks* pAllocator = nullptr);

	/*
		void DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator = nullptr);

		• instance is the handle of the instance to destroy.
		• pAllocator controls host memory allocation

		Valid Usage
		• If instance is not NULL, instance must be a valid VkInstance handle
		• If pAllocator is not NULL, pAllocator must be a pointer to a valid VkAllocationCallbacks structure
		• All child objects created using instance must have been destroyed prior to destroying instance
		• If VkAllocationCallbacks were provided when instance was created, a compatible set of callbacks must
		be provided here
		• If no VkAllocationCallbacks were provided when instance was created, pAllocator must be NULL

		Host Synchronization
		• Host access to instance must be externally synchronized
	*/
	void DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator = nullptr) noexcept;



	using namespace std::string_literals;
	class ResultErrorException : public std::exception
	{
	public:
		ResultErrorException(VkResult e) : m_sMessage{ "Vulkan returned error "s + to_string(e)} { }
		ResultErrorException(VkResult e, gsl::cstring_span<> sContext)
			: m_sMessage{ HE::Format("Vulkan returned error {0} from: {1}", e, sContext) } 
		{ }

		virtual const char* what() const override
		{
			return m_sMessage.c_str();
		}

	private:
		std::string m_sMessage;
	};

	namespace Private
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
}