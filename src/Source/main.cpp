#include <iostream>
#include <iomanip>
#include <gsl.h>

#include "HE_String.h"
#include "HE_Vulkan.h"

using namespace std::string_literals;

namespace
{
	bool s_bPrintPhysicalDevices{ false };

	void ParseArgs(gsl::span<char const* const> args)
	{
		for (auto const pszArg : args)
		{
			if (pszArg == "--print-physical-devices"s || pszArg == "-ppd"s)
			{
				s_bPrintPhysicalDevices = true;
			}
		}
	}

	void Print(const VkPhysicalDeviceProperties& pdp)
	{
		std::cout << "API Version: " << VK_VERSION_MAJOR(pdp.apiVersion) << "." << VK_VERSION_MINOR(pdp.apiVersion) << "." << VK_VERSION_PATCH(pdp.apiVersion) << "\n"
			"Driver Version: " << pdp.driverVersion << "\n"
			"Vendor ID: " << pdp.vendorID << "\n"
			"Device ID: " << pdp.deviceID << "\n"
			"Device Type: " << to_string(pdp.deviceType) << "\n"
			"Device Name: " << pdp.deviceName << "\n"
			<< std::endl;
	}

	void Print(const VkQueueFamilyProperties& qfp)
	{
		std::cout << std::boolalpha << "Queue flags: "
			"Graphics = " << ((qfp.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)  << ", "
			"Compute = " << ((qfp.queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) << ", " 
			"Transfer = " << ((qfp.queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) << ", "
			"Sparse Binding = " << ((qfp.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0) << "\n"
			"Queue Count: " << qfp.queueCount << "\n"
			"Timestamp Support: " << (qfp.timestampValidBits != 0) << "\n"
			"Timestamp significant bits count: " << qfp.timestampValidBits << "\n"
			"Minimum Image Transfer Granularity: (" << qfp.minImageTransferGranularity.width << ", " 
				<< qfp.minImageTransferGranularity.height << ", "
				<< qfp.minImageTransferGranularity.depth << ")\n"
			<< std::endl;
	}

	void Print(VkPhysicalDevice pd)
	{
		auto const pdProperties = vk::GetPhysicalDeviceProperties(pd);
		std::cout << "Physical Device Properties: " << std::endl;
		Print(pdProperties);

		auto const pdQueueFamilyProperties = vk::GetPhysicalDeviceQueueFamilyProperties(pd);
		int i = 1;
		for (auto const& queueFamilyProperty : pdQueueFamilyProperties)
		{
			std::cout << "Queue Family Properties #" << i << ":" << std::endl;
			Print(queueFamilyProperty);
			++i;
		}
	}
}



int main(int const argc, char const* const argv[])
{
	ParseArgs({ argv, argc });

	try
	{
		auto const applicationInfo = vk::MakeApplicationInfo("VulkanTest", VK_MAKE_VERSION(0, 0, 1));
		auto const instanceCreateInfo = vk::MakeInstanceCreateInfo(&applicationInfo);
		auto const instance = vk::CreateInstance(instanceCreateInfo);
		auto const destroyInstance = gsl::finally([instance]() { vk::DestroyInstance(instance); });

		auto const physicalDevices = vk::EnumeratePhysicalDevices(instance);

		for (std::size_t i = 0; i < physicalDevices.size(); ++i)
		{
			auto const& physicalDevice = physicalDevices[i];

			if (s_bPrintPhysicalDevices)
			{
				std::cout << "Physical Device #" << i + 1 << ":" << std::endl;
				Print(physicalDevice);
			}

			auto const physicalDeviceQueueFamilyProperties = vk::GetPhysicalDeviceQueueFamilyProperties(physicalDevice);
			auto const familyCount = physicalDeviceQueueFamilyProperties.size();
			auto const deviceQueueCreateInfos = [&physicalDeviceQueueFamilyProperties, familyCount]()
			{
				std::vector<VkDeviceQueueCreateInfo> ret(familyCount);
				for (uint32_t j = 0; j < familyCount; ++j)
				{
					std::vector<float> const priorities(physicalDeviceQueueFamilyProperties[j].queueCount, 1.0f);
					ret[j] = vk::MakeDeviceQueueCreateInfo(j, gsl::as_span(priorities));
				}

				return ret;
			}();

			auto const physicalDeviceFeatures = vk::GetPhysicalDeviceFeatures(physicalDevice);
			auto const deviceCreateInfo = vk::MakeDeviceCreateInfo(gsl::as_span(deviceQueueCreateInfos), {}, {}, physicalDeviceFeatures);
			
			auto const device = vk::CreateDevice(physicalDevice, deviceCreateInfo);
			auto const destroyDevice = gsl::finally([device]() { vk::DeviceWaitIdle(device, std::nothrow); vk::DestroyDevice(device); });


		}

	}
	catch (const vk::ResultErrorException& e)
	{
		HE::LogError(to_string(e));
		return -1;
	}
	
	return 0;
}