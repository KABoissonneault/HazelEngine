#include <iostream>
#include <iomanip>
#include <algorithm>
#include <gsl.h>

#include "HE_String.h"
#include "HE_Assert.h"
#include "HazelEngine.h"
#define VKCPP_ENHANCED_MODE
#include <vulkan/vk_cpp.h>


using namespace std::string_literals;

namespace
{
	class CmdArgs
	{
	public:
		CmdArgs(gsl::span<gsl::czstring<> const> args)
		{
			ParseArgs(args);
		}

		bool PrintPhysicalDevices() const noexcept { return m_bPrintPhysicalDevices; }

		void ParseArgs(gsl::span<char const* const> args)
		{
			for (auto const pszArg : args)
			{
				if (pszArg == "--print-physical-devices"s || pszArg == "-ppd"s)
				{
					m_bPrintPhysicalDevices = true;
				}
			}
		}


	private:
		bool m_bPrintPhysicalDevices{ false };
	};	

	void Print(const vk::PhysicalDeviceProperties& pdp)
	{
		std::cout << "API Version: " << VK_VERSION_MAJOR(pdp.apiVersion()) << "." << VK_VERSION_MINOR(pdp.apiVersion()) << "." << VK_VERSION_PATCH(pdp.apiVersion()) << "\n"
			"Driver Version: " << pdp.driverVersion() << "\n"
			"Vendor ID: " << pdp.vendorID() << "\n"
			"Device ID: " << pdp.deviceID() << "\n"
			"Device Type: " << to_string(pdp.deviceType()) << "\n"
			"Device Name: " << pdp.deviceName() << "\n"
			<< std::endl;
	}

	void Print(const vk::QueueFamilyProperties& qfp)
	{
		std::cout << std::boolalpha << "Queue flags: "
			"Graphics = " << ((qfp.queueFlags() & vk::QueueFlagBits::eGraphics) != 0)  << ", "
			"Compute = " << ((qfp.queueFlags() & vk::QueueFlagBits::eCompute) != 0) << ", "
			"Transfer = " << ((qfp.queueFlags() & vk::QueueFlagBits::eTransfer) != 0) << ", "
			"Sparse Binding = " << ((qfp.queueFlags() & vk::QueueFlagBits::eSparseBinding) != 0) << "\n"
			"Queue Count: " << qfp.queueCount() << "\n"
			"Timestamp Support: " << (qfp.timestampValidBits() != 0) << "\n"
			"Timestamp significant bits count: " << qfp.timestampValidBits() << "\n"
			"Minimum Image Transfer Granularity: (" << qfp.minImageTransferGranularity().width() << ", " 
				<< qfp.minImageTransferGranularity().height() << ", "
				<< qfp.minImageTransferGranularity().depth() << ")\n"
			<< std::endl;
	}

	void Print(vk::PhysicalDevice pd)
	{
		auto const pdProperties = pd.getProperties();
		std::cout << "Physical Device Properties: " << std::endl;
		Print(pdProperties);

		auto const pdQueueFamilyProperties = pd.getQueueFamilyProperties();
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
	CmdArgs const args{ gsl::as_span( argv, argc ) };

	try
	{
		vk::ApplicationInfo const applicationInfo{ "VulkanTest", 0x1, "HazelEngine", HE::MakeVersion(0, 0, 1), VK_MAKE_VERSION(1, 0, 4) };
		auto const instanceCreateInfo = vk::InstanceCreateInfo{}
			.pApplicationInfo(&applicationInfo);
		auto const instance = vk::createInstance(instanceCreateInfo, nullptr);
		auto const destroyInstance = gsl::finally([instance]() { instance.destroy(nullptr); });

		vk::Result res;
		auto const physicalDevices = instance.enumeratePhysicalDevices(res);
		if (res == vk::Result::eIncomplete) std::cerr << "Physical Device Enumeration incomplete" << std::endl;

		for (std::size_t i = 0; i < physicalDevices.size(); ++i)
		{
			auto const& physicalDevice = physicalDevices[i];

			if (args.PrintPhysicalDevices())
			{
				std::cout << "Physical Device #" << i + 1 << ":" << std::endl;
				Print(physicalDevice);
			}

			auto const physicalDeviceQueueFamilyProperties = physicalDevice.getQueueFamilyProperties();
			auto const familyCount = physicalDeviceQueueFamilyProperties.size();

			auto const maxQueueCount = std::max_element(physicalDeviceQueueFamilyProperties.begin(), physicalDeviceQueueFamilyProperties.end(), [](auto const& prop1, auto const& prop2)
			{
				return prop1.queueCount() < prop2.queueCount();
			})->queueCount();

			std::vector<float> const priorities(maxQueueCount, 1.0f);

			auto const deviceQueueCreateInfos = [&physicalDeviceQueueFamilyProperties, &priorities, familyCount]()
			{
				std::vector<vk::DeviceQueueCreateInfo> ret(familyCount);
				for (uint32_t j = 0; j < familyCount; ++j)
				{
					ret[j] = vk::DeviceQueueCreateInfo{}
						.queueFamilyIndex(j)
						.pQueuePriorities(priorities.data())
						.queueCount(physicalDeviceQueueFamilyProperties[j].queueCount());
				}

				return ret;
			}();

			auto const physicalDeviceFeatures = physicalDevice.getFeatures();
			auto const deviceCreateInfo = vk::DeviceCreateInfo{}
				.pQueueCreateInfos(deviceQueueCreateInfos.data())
				.queueCreateInfoCount(gsl::narrow_cast<std::uint32_t>(deviceQueueCreateInfos.size()))
				.pEnabledFeatures(&physicalDeviceFeatures);
			
			auto const device = physicalDevice.createDevice(deviceCreateInfo, nullptr);
			auto const destroyDevice = gsl::finally([device]() { device.waitIdle(); device.destroy(nullptr); });
		}

	}
	catch (const std::runtime_error& e)
	{
		HE::LogError(to_string(e));
		return -1;
	}
	
	return 0;
}