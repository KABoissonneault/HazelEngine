/* THIS FILE IS GENERATED.  DO NOT EDIT. */

/*
 * Copyright (c) 2015-2016 The Khronos Group Inc.
 * Copyright (c) 2015-2016 Valve Corporation
 * Copyright (c) 2015-2016 LunarG, Inc.
 * Copyright (c) 2015 Google, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and/or associated documentation files (the "Materials"), to
 * deal in the Materials without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Materials, and to permit persons to whom the Materials
 * are furnished to do so, subject to the following conditions:
 *
 * The above copyright notice(s) and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE
 * USE OR OTHER DEALINGS IN THE MATERIALS
 *
 * Author: Tobin Ehlis <tobine@google.com>
 * Author: Courtney Goeltzenleuchter <courtneygo@google.com>
 * Author: Jon Ashburn <jon@lunarg.com>
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Mike Stroyan <stroyan@google.com>
 * Author: Tony Barbour <tony@LunarG.com>
 */

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1773
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include "vk_loader_platform.h"
#include "vulkan/vk_layer.h"
#include "threading.h"
#include "vk_layer_config.h"
#include "vk_layer_extension_utils.h"
#include "vk_enum_validate_helper.h"
#include "vk_struct_validate_helper.h"
#include "vk_layer_table.h"
#include "vk_layer_logging.h"


static LOADER_PLATFORM_THREAD_ONCE_DECLARATION(initOnce);

using namespace std;
static unordered_map<VkQueue, loader_platform_thread_id> VkQueueObjectsInUse;
static unordered_map<VkCommandBuffer, loader_platform_thread_id> VkCommandBufferObjectsInUse;
static unordered_map<VkDeviceMemory, loader_platform_thread_id> VkDeviceMemoryObjectsInUse;
static unordered_map<VkBuffer, loader_platform_thread_id> VkBufferObjectsInUse;
static unordered_map<VkImage, loader_platform_thread_id> VkImageObjectsInUse;
static unordered_map<VkDescriptorSet, loader_platform_thread_id> VkDescriptorSetObjectsInUse;
static unordered_map<VkDescriptorPool, loader_platform_thread_id> VkDescriptorPoolObjectsInUse;
static unordered_map<VkSemaphore, loader_platform_thread_id> VkSemaphoreObjectsInUse;
static int threadingLockInitialized = 0;
static loader_platform_thread_mutex threadingLock;
static loader_platform_thread_cond threadingCond;
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1799
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkQueue(const void* dispatchable_object, VkQueue object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkQueueObjectsInUse.find(object) == VkQueueObjectsInUse.end()) {
        VkQueueObjectsInUse[object] = tid;
    } else {
        if (VkQueueObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkQueue is simultaneously used in thread %ld and thread %ld",
                VkQueueObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkQueueObjectsInUse.find(object) != VkQueueObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkQueueObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkQueue is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkQueue(VkQueue object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkQueueObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkCommandBuffer(const void* dispatchable_object, VkCommandBuffer object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkCommandBufferObjectsInUse.find(object) == VkCommandBufferObjectsInUse.end()) {
        VkCommandBufferObjectsInUse[object] = tid;
    } else {
        if (VkCommandBufferObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkCommandBuffer is simultaneously used in thread %ld and thread %ld",
                VkCommandBufferObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkCommandBufferObjectsInUse.find(object) != VkCommandBufferObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkCommandBufferObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkCommandBuffer is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkCommandBuffer(VkCommandBuffer object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkCommandBufferObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkDeviceMemory(const void* dispatchable_object, VkDeviceMemory object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkDeviceMemoryObjectsInUse.find(object) == VkDeviceMemoryObjectsInUse.end()) {
        VkDeviceMemoryObjectsInUse[object] = tid;
    } else {
        if (VkDeviceMemoryObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkDeviceMemory is simultaneously used in thread %ld and thread %ld",
                VkDeviceMemoryObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkDeviceMemoryObjectsInUse.find(object) != VkDeviceMemoryObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkDeviceMemoryObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkDeviceMemory is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkDeviceMemory(VkDeviceMemory object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkDeviceMemoryObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkBuffer(const void* dispatchable_object, VkBuffer object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkBufferObjectsInUse.find(object) == VkBufferObjectsInUse.end()) {
        VkBufferObjectsInUse[object] = tid;
    } else {
        if (VkBufferObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkBuffer is simultaneously used in thread %ld and thread %ld",
                VkBufferObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkBufferObjectsInUse.find(object) != VkBufferObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkBufferObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkBuffer is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkBuffer(VkBuffer object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkBufferObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkImage(const void* dispatchable_object, VkImage object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkImageObjectsInUse.find(object) == VkImageObjectsInUse.end()) {
        VkImageObjectsInUse[object] = tid;
    } else {
        if (VkImageObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkImage is simultaneously used in thread %ld and thread %ld",
                VkImageObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkImageObjectsInUse.find(object) != VkImageObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkImageObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkImage is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkImage(VkImage object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkImageObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkDescriptorSet(const void* dispatchable_object, VkDescriptorSet object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkDescriptorSetObjectsInUse.find(object) == VkDescriptorSetObjectsInUse.end()) {
        VkDescriptorSetObjectsInUse[object] = tid;
    } else {
        if (VkDescriptorSetObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkDescriptorSet is simultaneously used in thread %ld and thread %ld",
                VkDescriptorSetObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkDescriptorSetObjectsInUse.find(object) != VkDescriptorSetObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkDescriptorSetObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkDescriptorSet is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkDescriptorSet(VkDescriptorSet object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkDescriptorSetObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkDescriptorPool(const void* dispatchable_object, VkDescriptorPool object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkDescriptorPoolObjectsInUse.find(object) == VkDescriptorPoolObjectsInUse.end()) {
        VkDescriptorPoolObjectsInUse[object] = tid;
    } else {
        if (VkDescriptorPoolObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkDescriptorPool is simultaneously used in thread %ld and thread %ld",
                VkDescriptorPoolObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkDescriptorPoolObjectsInUse.find(object) != VkDescriptorPoolObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkDescriptorPoolObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkDescriptorPool is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkDescriptorPool(VkDescriptorPool object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkDescriptorPoolObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1730
static void useVkSemaphore(const void* dispatchable_object, VkSemaphore object)
{
    loader_platform_thread_id tid = loader_platform_get_thread_id();
    loader_platform_thread_lock_mutex(&threadingLock);
    if (VkSemaphoreObjectsInUse.find(object) == VkSemaphoreObjectsInUse.end()) {
        VkSemaphoreObjectsInUse[object] = tid;
    } else {
        if (VkSemaphoreObjectsInUse[object] != tid) {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkSemaphore is simultaneously used in thread %ld and thread %ld",
                VkSemaphoreObjectsInUse[object], tid);
            // Wait for thread-safe access to object
            while (VkSemaphoreObjectsInUse.find(object) != VkSemaphoreObjectsInUse.end()) {
                loader_platform_thread_cond_wait(&threadingCond, &threadingLock);
            }
            VkSemaphoreObjectsInUse[object] = tid;
        } else {
            log_msg(mdd(dispatchable_object), VK_DEBUG_REPORT_ERROR_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, (uint64_t)(object),
                __LINE__, THREADING_CHECKER_MULTIPLE_THREADS, "THREADING",
                "THREADING ERROR : object of type VkSemaphore is recursively used in thread %ld",
                tid);
        }
    }
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1761
static void finishUsingVkSemaphore(VkSemaphore object)
{
    // Object is no longer in use
    loader_platform_thread_lock_mutex(&threadingLock);
    VkSemaphoreObjectsInUse.erase(object);
    loader_platform_thread_cond_broadcast(&threadingCond);
    loader_platform_thread_unlock_mutex(&threadingLock);
}
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1803

#include "vk_dispatch_table_helper.h"
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #728
static void init_threading(layer_data *my_data, const VkAllocationCallbacks *pAllocator)
{

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #732
    uint32_t report_flags = 0;
    uint32_t debug_action = 0;
    FILE *log_output = NULL;
    const char *strOpt;
    // initialize threading options
    report_flags = getLayerOptionFlags("threadingReportFlags", 0);
    getLayerOptionEnum("threadingDebugAction", (uint32_t *) &debug_action);

    if (debug_action & VK_DBG_LAYER_ACTION_LOG_MSG)
    {
        strOpt = getLayerOption("threadingLogFilename");
        log_output = getLayerLogOutput(strOpt, "threading");
        VkDebugReportCallbackCreateInfoEXT dbgCreateInfo;
        memset(&dbgCreateInfo, 0, sizeof(dbgCreateInfo));
        dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        dbgCreateInfo.flags = report_flags;
        dbgCreateInfo.pfnCallback = log_callback;
        dbgCreateInfo.pUserData = log_output;
        layer_create_msg_callback(my_data->report_data, &dbgCreateInfo, pAllocator,
                                  &my_data->logging_callback);
    }

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #756
    if (!threadingLockInitialized)
    {
        // TODO/TBD: Need to delete this mutex sometime.  How???
        loader_platform_thread_create_mutex(&threadingLock);
        loader_platform_thread_init_cond(&threadingCond);
        threadingLockInitialized = 1;
    }
}



VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    VkLayerInstanceCreateInfo *chain_info = get_chain_info(pCreateInfo, VK_LAYER_LINK_INFO);
    PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    PFN_vkCreateInstance fpCreateInstance = (PFN_vkCreateInstance) fpGetInstanceProcAddr(NULL, "vkCreateInstance");
    if (fpCreateInstance == NULL) {
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    // Advance the link info for the next element on the chain
    chain_info->u.pLayerInfo = chain_info->u.pLayerInfo->pNext;
    VkResult result = fpCreateInstance(pCreateInfo, pAllocator, pInstance);
    if (result != VK_SUCCESS) {
        return result;
    }
    VkLayerInstanceDispatchTable *pTable = initInstanceTable(*pInstance, fpGetInstanceProcAddr, threading_instance_table_map);
    layer_data *my_data = get_my_data_ptr(get_dispatch_key(*pInstance), layer_data_map);
    my_data->report_data = debug_report_create_instance(
            pTable,
            *pInstance,
            pCreateInfo->enabledExtensionCount,
            pCreateInfo->ppEnabledExtensionNames);
    init_threading(my_data, pAllocator);
    return result;
}


VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    dispatch_key key = get_dispatch_key(instance);
    VkLayerInstanceDispatchTable *pInstanceTable = get_dispatch_table(threading_instance_table_map, instance);
    pInstanceTable->DestroyInstance(instance, pAllocator);
    destroy_dispatch_table(threading_instance_table_map, key);

    // Clean up logging callback, if any
    layer_data *my_data = get_my_data_ptr(key, layer_data_map);
    if (my_data->logging_callback) {
        layer_destroy_msg_callback(my_data->report_data, my_data->logging_callback, pAllocator);
    }

    layer_debug_report_destroy_instance(my_data->report_data);
    layer_data_map.erase(pInstanceTable);

    threading_instance_table_map.erase(key);
}


// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1845
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
    VkLayerDeviceCreateInfo *chain_info = get_chain_info(pCreateInfo, VK_LAYER_LINK_INFO);
    PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr fpGetDeviceProcAddr = chain_info->u.pLayerInfo->pfnNextGetDeviceProcAddr;
    PFN_vkCreateDevice fpCreateDevice = (PFN_vkCreateDevice) fpGetInstanceProcAddr(NULL, "vkCreateDevice");
    if (fpCreateDevice == NULL) {
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    // Advance the link info for the next element on the chain
    chain_info->u.pLayerInfo = chain_info->u.pLayerInfo->pNext;
    VkResult result = fpCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
    if (result != VK_SUCCESS) {
        return result;
    }
    layer_data *my_instance_data = get_my_data_ptr(get_dispatch_key(physicalDevice), layer_data_map);
    layer_data *my_device_data = get_my_data_ptr(get_dispatch_key(*pDevice), layer_data_map);
    initDeviceTable(*pDevice, fpGetDeviceProcAddr, threading_device_table_map);
    my_device_data->report_data = layer_debug_report_create_device(my_instance_data->report_data, *pDevice);
    return result;
}


VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    dispatch_key key = get_dispatch_key(device);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->DestroyDevice(device, pAllocator);
    threading_device_table_map.erase(key);
}


// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #354

static const VkExtensionProperties instance_extensions[] = {
    {
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
        VK_EXT_DEBUG_REPORT_SPEC_VERSION
    }
};
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pCount,  VkExtensionProperties* pProperties)
{
    return util_GetExtensionProperties(1, instance_extensions, pCount, pProperties);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #377
static const VkLayerProperties globalLayerProps[] = {
    {
        "VK_LAYER_LUNARG_threading",
        VK_API_VERSION, // specVersion
        1, // implementationVersion
        "layer: threading",
    }
};

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #390

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t *pCount,  VkLayerProperties* pProperties)
{
    return util_GetLayerProperties(ARRAY_SIZE(globalLayerProps), globalLayerProps, pCount, pProperties);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #400
static const VkLayerProperties deviceLayerProps[] = {
    {
        "VK_LAYER_LUNARG_threading",
        VK_API_VERSION,
        1,
        "layer: threading",
    }
};
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t *pCount, VkLayerProperties* pProperties)
{
    return util_GetLayerProperties(ARRAY_SIZE(deviceLayerProps), deviceLayerProps, pCount, pProperties);
}


// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
    useVkQueue((const void *) queue, queue);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, queue);
    VkResult result = pDeviceTable->QueueSubmit(queue, submitCount, pSubmits, fence);
    finishUsingVkQueue(queue);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
    useVkDeviceMemory((const void *) device, memory);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->FreeMemory(device, memory, pAllocator);
    finishUsingVkDeviceMemory(memory);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)
{
    useVkDeviceMemory((const void *) device, memory);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result = pDeviceTable->MapMemory(device, memory, offset, size, flags, ppData);
    finishUsingVkDeviceMemory(memory);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(VkDevice device, VkDeviceMemory memory)
{
    useVkDeviceMemory((const void *) device, memory);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->UnmapMemory(device, memory);
    finishUsingVkDeviceMemory(memory);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1823
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
    for (uint32_t i=0; i<memoryRangeCount; i++) {
        useVkDeviceMemory((const void *) device, pMemoryRanges[i].memory);
    }
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result =  pDeviceTable->FlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    for (uint32_t i=0; i<memoryRangeCount; i++) {
        finishUsingVkDeviceMemory(pMemoryRanges[i].memory);
    }
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1823
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
    for (uint32_t i=0; i<memoryRangeCount; i++) {
        useVkDeviceMemory((const void *) device, pMemoryRanges[i].memory);
    }
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result =  pDeviceTable->InvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    for (uint32_t i=0; i<memoryRangeCount; i++) {
        finishUsingVkDeviceMemory(pMemoryRanges[i].memory);
    }
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    useVkBuffer((const void *) device, buffer);
    useVkDeviceMemory((const void *) device, memory);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result = pDeviceTable->BindBufferMemory(device, buffer, memory, memoryOffset);
    finishUsingVkBuffer(buffer);
    finishUsingVkDeviceMemory(memory);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    useVkImage((const void *) device, image);
    useVkDeviceMemory((const void *) device, memory);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result = pDeviceTable->BindImageMemory(device, image, memory, memoryOffset);
    finishUsingVkImage(image);
    finishUsingVkDeviceMemory(memory);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence)
{
    useVkQueue((const void *) queue, queue);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, queue);
    VkResult result = pDeviceTable->QueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
    finishUsingVkQueue(queue);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    useVkSemaphore((const void *) device, semaphore);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->DestroySemaphore(device, semaphore, pAllocator);
    finishUsingVkSemaphore(semaphore);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
    useVkBuffer((const void *) device, buffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->DestroyBuffer(device, buffer, pAllocator);
    finishUsingVkBuffer(buffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator)
{
    useVkImage((const void *) device, image);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->DestroyImage(device, image, pAllocator);
    finishUsingVkImage(image);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator)
{
    useVkDescriptorPool((const void *) device, descriptorPool);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    pDeviceTable->DestroyDescriptorPool(device, descriptorPool, pAllocator);
    finishUsingVkDescriptorPool(descriptorPool);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags)
{
    useVkDescriptorPool((const void *) device, descriptorPool);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result = pDeviceTable->ResetDescriptorPool(device, descriptorPool, flags);
    finishUsingVkDescriptorPool(descriptorPool);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1948
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
    useVkDescriptorPool((const void *) device, descriptorPool);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, device);
    VkResult result = pDeviceTable->FreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    finishUsingVkDescriptorPool(descriptorPool);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    VkResult result = pDeviceTable->BeginCommandBuffer(commandBuffer, pBeginInfo);
    finishUsingVkCommandBuffer(commandBuffer);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEndCommandBuffer(VkCommandBuffer commandBuffer)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    VkResult result = pDeviceTable->EndCommandBuffer(commandBuffer);
    finishUsingVkCommandBuffer(commandBuffer);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    VkResult result = pDeviceTable->ResetCommandBuffer(commandBuffer, flags);
    finishUsingVkCommandBuffer(commandBuffer);
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetLineWidth(commandBuffer, lineWidth);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4])
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetBlendConstants(commandBuffer, blendConstants);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetStencilReference(commandBuffer, faceMask, reference);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t x, uint32_t y, uint32_t z)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdDispatch(commandBuffer, x, y, z);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdDispatchIndirect(commandBuffer, buffer, offset);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const uint32_t* pData)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdSetEvent(commandBuffer, event, stageMask);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdResetEvent(commandBuffer, event, stageMask);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBeginQuery(commandBuffer, queryPool, query, flags);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdEndQuery(commandBuffer, queryPool, query);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdNextSubpass(commandBuffer, contents);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass(VkCommandBuffer commandBuffer)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdEndRenderPass(commandBuffer);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1872
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
    useVkCommandBuffer((const void *) commandBuffer, commandBuffer);
    VkLayerDispatchTable *pDeviceTable = get_dispatch_table(threading_device_table_map, commandBuffer);
    pDeviceTable->CmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
    finishUsingVkCommandBuffer(commandBuffer);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #461
static inline PFN_vkVoidFunction layer_intercept_proc(const char *name)
{
    if (!name || name[0] != 'v' || name[1] != 'k')
        return NULL;

    name += 2;
    if (!strcmp(name, "CreateInstance"))
        return (PFN_vkVoidFunction) vkCreateInstance;
    if (!strcmp(name, "DestroyInstance"))
        return (PFN_vkVoidFunction) vkDestroyInstance;
    if (!strcmp(name, "CreateDevice"))
        return (PFN_vkVoidFunction) vkCreateDevice;
    if (!strcmp(name, "DestroyDevice"))
        return (PFN_vkVoidFunction) vkDestroyDevice;
    if (!strcmp(name, "EnumerateInstanceExtensionProperties"))
        return (PFN_vkVoidFunction) vkEnumerateInstanceExtensionProperties;
    if (!strcmp(name, "EnumerateInstanceLayerProperties"))
        return (PFN_vkVoidFunction) vkEnumerateInstanceLayerProperties;
    if (!strcmp(name, "EnumerateDeviceLayerProperties"))
        return (PFN_vkVoidFunction) vkEnumerateDeviceLayerProperties;
    if (!strcmp(name, "QueueSubmit"))
        return (PFN_vkVoidFunction) vkQueueSubmit;
    if (!strcmp(name, "FreeMemory"))
        return (PFN_vkVoidFunction) vkFreeMemory;
    if (!strcmp(name, "MapMemory"))
        return (PFN_vkVoidFunction) vkMapMemory;
    if (!strcmp(name, "UnmapMemory"))
        return (PFN_vkVoidFunction) vkUnmapMemory;
    if (!strcmp(name, "FlushMappedMemoryRanges"))
        return (PFN_vkVoidFunction) vkFlushMappedMemoryRanges;
    if (!strcmp(name, "InvalidateMappedMemoryRanges"))
        return (PFN_vkVoidFunction) vkInvalidateMappedMemoryRanges;
    if (!strcmp(name, "BindBufferMemory"))
        return (PFN_vkVoidFunction) vkBindBufferMemory;
    if (!strcmp(name, "BindImageMemory"))
        return (PFN_vkVoidFunction) vkBindImageMemory;
    if (!strcmp(name, "QueueBindSparse"))
        return (PFN_vkVoidFunction) vkQueueBindSparse;
    if (!strcmp(name, "DestroySemaphore"))
        return (PFN_vkVoidFunction) vkDestroySemaphore;
    if (!strcmp(name, "DestroyBuffer"))
        return (PFN_vkVoidFunction) vkDestroyBuffer;
    if (!strcmp(name, "DestroyImage"))
        return (PFN_vkVoidFunction) vkDestroyImage;
    if (!strcmp(name, "DestroyDescriptorPool"))
        return (PFN_vkVoidFunction) vkDestroyDescriptorPool;
    if (!strcmp(name, "ResetDescriptorPool"))
        return (PFN_vkVoidFunction) vkResetDescriptorPool;
    if (!strcmp(name, "FreeDescriptorSets"))
        return (PFN_vkVoidFunction) vkFreeDescriptorSets;
    if (!strcmp(name, "BeginCommandBuffer"))
        return (PFN_vkVoidFunction) vkBeginCommandBuffer;
    if (!strcmp(name, "EndCommandBuffer"))
        return (PFN_vkVoidFunction) vkEndCommandBuffer;
    if (!strcmp(name, "ResetCommandBuffer"))
        return (PFN_vkVoidFunction) vkResetCommandBuffer;
    if (!strcmp(name, "CmdBindPipeline"))
        return (PFN_vkVoidFunction) vkCmdBindPipeline;
    if (!strcmp(name, "CmdSetViewport"))
        return (PFN_vkVoidFunction) vkCmdSetViewport;
    if (!strcmp(name, "CmdSetScissor"))
        return (PFN_vkVoidFunction) vkCmdSetScissor;
    if (!strcmp(name, "CmdSetLineWidth"))
        return (PFN_vkVoidFunction) vkCmdSetLineWidth;
    if (!strcmp(name, "CmdSetDepthBias"))
        return (PFN_vkVoidFunction) vkCmdSetDepthBias;
    if (!strcmp(name, "CmdSetBlendConstants"))
        return (PFN_vkVoidFunction) vkCmdSetBlendConstants;
    if (!strcmp(name, "CmdSetDepthBounds"))
        return (PFN_vkVoidFunction) vkCmdSetDepthBounds;
    if (!strcmp(name, "CmdSetStencilCompareMask"))
        return (PFN_vkVoidFunction) vkCmdSetStencilCompareMask;
    if (!strcmp(name, "CmdSetStencilWriteMask"))
        return (PFN_vkVoidFunction) vkCmdSetStencilWriteMask;
    if (!strcmp(name, "CmdSetStencilReference"))
        return (PFN_vkVoidFunction) vkCmdSetStencilReference;
    if (!strcmp(name, "CmdBindDescriptorSets"))
        return (PFN_vkVoidFunction) vkCmdBindDescriptorSets;
    if (!strcmp(name, "CmdBindIndexBuffer"))
        return (PFN_vkVoidFunction) vkCmdBindIndexBuffer;
    if (!strcmp(name, "CmdBindVertexBuffers"))
        return (PFN_vkVoidFunction) vkCmdBindVertexBuffers;
    if (!strcmp(name, "CmdDraw"))
        return (PFN_vkVoidFunction) vkCmdDraw;
    if (!strcmp(name, "CmdDrawIndexed"))
        return (PFN_vkVoidFunction) vkCmdDrawIndexed;
    if (!strcmp(name, "CmdDrawIndirect"))
        return (PFN_vkVoidFunction) vkCmdDrawIndirect;
    if (!strcmp(name, "CmdDrawIndexedIndirect"))
        return (PFN_vkVoidFunction) vkCmdDrawIndexedIndirect;
    if (!strcmp(name, "CmdDispatch"))
        return (PFN_vkVoidFunction) vkCmdDispatch;
    if (!strcmp(name, "CmdDispatchIndirect"))
        return (PFN_vkVoidFunction) vkCmdDispatchIndirect;
    if (!strcmp(name, "CmdCopyBuffer"))
        return (PFN_vkVoidFunction) vkCmdCopyBuffer;
    if (!strcmp(name, "CmdCopyImage"))
        return (PFN_vkVoidFunction) vkCmdCopyImage;
    if (!strcmp(name, "CmdBlitImage"))
        return (PFN_vkVoidFunction) vkCmdBlitImage;
    if (!strcmp(name, "CmdCopyBufferToImage"))
        return (PFN_vkVoidFunction) vkCmdCopyBufferToImage;
    if (!strcmp(name, "CmdCopyImageToBuffer"))
        return (PFN_vkVoidFunction) vkCmdCopyImageToBuffer;
    if (!strcmp(name, "CmdUpdateBuffer"))
        return (PFN_vkVoidFunction) vkCmdUpdateBuffer;
    if (!strcmp(name, "CmdFillBuffer"))
        return (PFN_vkVoidFunction) vkCmdFillBuffer;
    if (!strcmp(name, "CmdClearColorImage"))
        return (PFN_vkVoidFunction) vkCmdClearColorImage;
    if (!strcmp(name, "CmdClearDepthStencilImage"))
        return (PFN_vkVoidFunction) vkCmdClearDepthStencilImage;
    if (!strcmp(name, "CmdClearAttachments"))
        return (PFN_vkVoidFunction) vkCmdClearAttachments;
    if (!strcmp(name, "CmdResolveImage"))
        return (PFN_vkVoidFunction) vkCmdResolveImage;
    if (!strcmp(name, "CmdSetEvent"))
        return (PFN_vkVoidFunction) vkCmdSetEvent;
    if (!strcmp(name, "CmdResetEvent"))
        return (PFN_vkVoidFunction) vkCmdResetEvent;
    if (!strcmp(name, "CmdWaitEvents"))
        return (PFN_vkVoidFunction) vkCmdWaitEvents;
    if (!strcmp(name, "CmdPipelineBarrier"))
        return (PFN_vkVoidFunction) vkCmdPipelineBarrier;
    if (!strcmp(name, "CmdBeginQuery"))
        return (PFN_vkVoidFunction) vkCmdBeginQuery;
    if (!strcmp(name, "CmdEndQuery"))
        return (PFN_vkVoidFunction) vkCmdEndQuery;
    if (!strcmp(name, "CmdResetQueryPool"))
        return (PFN_vkVoidFunction) vkCmdResetQueryPool;
    if (!strcmp(name, "CmdWriteTimestamp"))
        return (PFN_vkVoidFunction) vkCmdWriteTimestamp;
    if (!strcmp(name, "CmdCopyQueryPoolResults"))
        return (PFN_vkVoidFunction) vkCmdCopyQueryPoolResults;
    if (!strcmp(name, "CmdPushConstants"))
        return (PFN_vkVoidFunction) vkCmdPushConstants;
    if (!strcmp(name, "CmdBeginRenderPass"))
        return (PFN_vkVoidFunction) vkCmdBeginRenderPass;
    if (!strcmp(name, "CmdNextSubpass"))
        return (PFN_vkVoidFunction) vkCmdNextSubpass;
    if (!strcmp(name, "CmdEndRenderPass"))
        return (PFN_vkVoidFunction) vkCmdEndRenderPass;
    if (!strcmp(name, "CmdExecuteCommands"))
        return (PFN_vkVoidFunction) vkCmdExecuteCommands;

    return NULL;
}
static inline PFN_vkVoidFunction layer_intercept_instance_proc(const char *name)
{
    if (!name || name[0] != 'v' || name[1] != 'k')
        return NULL;

    name += 2;
    if (!strcmp(name, "DestroyInstance"))
        return (PFN_vkVoidFunction) vkDestroyInstance;
    if (!strcmp(name, "EnumerateInstanceExtensionProperties"))
        return (PFN_vkVoidFunction) vkEnumerateInstanceExtensionProperties;
    if (!strcmp(name, "EnumerateInstanceLayerProperties"))
        return (PFN_vkVoidFunction) vkEnumerateInstanceLayerProperties;
    if (!strcmp(name, "EnumerateDeviceLayerProperties"))
        return (PFN_vkVoidFunction) vkEnumerateDeviceLayerProperties;

    return NULL;
}

VK_LAYER_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* funcName)
{
    PFN_vkVoidFunction addr;
    if (!strcmp("vkGetDeviceProcAddr", funcName)) {
        return (PFN_vkVoidFunction) vkGetDeviceProcAddr;
    }

    addr = layer_intercept_proc(funcName);
    if (addr)
        return addr;
    if (device == VK_NULL_HANDLE) {
        return NULL;
    }


    if (get_dispatch_table(threading_device_table_map, device)->GetDeviceProcAddr == NULL)
        return NULL;
    return get_dispatch_table(threading_device_table_map, device)->GetDeviceProcAddr(device, funcName);
}

VK_LAYER_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* funcName)
{
    PFN_vkVoidFunction addr;
    if (!strcmp(funcName, "vkGetInstanceProcAddr"))
        return (PFN_vkVoidFunction) vkGetInstanceProcAddr;
    if (!strcmp(funcName, "vkCreateInstance"))
        return (PFN_vkVoidFunction) vkCreateInstance;
    if (!strcmp(funcName, "vkCreateDevice"))
        return (PFN_vkVoidFunction) vkCreateDevice;
    addr = layer_intercept_instance_proc(funcName);
    if (addr) {
        return addr;    }
    if (instance == VK_NULL_HANDLE) {
        return NULL;
    }

    layer_data *my_data = get_my_data_ptr(get_dispatch_key(instance), layer_data_map);
    addr = debug_report_get_instance_proc_addr(my_data->report_data, funcName);
    if (addr) {
        return addr;
    }

    if (get_dispatch_table(threading_instance_table_map, instance)->GetInstanceProcAddr == NULL) {
        return NULL;
    }
    return get_dispatch_table(threading_instance_table_map, instance)->GetInstanceProcAddr(instance, funcName);
}


// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #292
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
        VkInstance                                   instance,
        const VkDebugReportCallbackCreateInfoEXT*    pCreateInfo,
        const VkAllocationCallbacks*                 pAllocator,
        VkDebugReportCallbackEXT*                    pCallback)
{
    VkLayerInstanceDispatchTable *pInstanceTable = get_dispatch_table(threading_instance_table_map, instance);
    VkResult result = pInstanceTable->CreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
    if (VK_SUCCESS == result) {
        layer_data *my_data = get_my_data_ptr(get_dispatch_key(instance), layer_data_map);
        result = layer_create_msg_callback(my_data->report_data,
                                           pCreateInfo,
                                           pAllocator,
                                           pCallback);
    }
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #323
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT msgCallback, const VkAllocationCallbacks *pAllocator)
{
    VkLayerInstanceDispatchTable *pInstanceTable = get_dispatch_table(threading_instance_table_map, instance);
    pInstanceTable->DestroyDebugReportCallbackEXT(instance, msgCallback, pAllocator);
    layer_data *my_data = get_my_data_ptr(get_dispatch_key(instance), layer_data_map);
    layer_destroy_msg_callback(my_data->report_data, msgCallback, pAllocator);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #339
VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT    flags, VkDebugReportObjectTypeEXT objType, uint64_t object, size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg)
{
    VkLayerInstanceDispatchTable *pInstanceTable = get_dispatch_table(threading_instance_table_map, instance);
    pInstanceTable->DebugReportMessageEXT(instance, flags, objType, object, location, msgCode, pLayerPrefix, pMsg);
}
