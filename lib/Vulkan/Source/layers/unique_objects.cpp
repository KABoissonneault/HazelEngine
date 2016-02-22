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

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1428
#include "unique_objects.h"

static LOADER_PLATFORM_THREAD_ONCE_DECLARATION(initOnce);

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    return explicit_CreateInstance(pCreateInfo, pAllocator, pInstance);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
    return explicit_CreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #354

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pCount,  VkExtensionProperties* pProperties)
{
    return util_GetExtensionProperties(0, NULL, pCount, pProperties);
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #377
static const VkLayerProperties globalLayerProps[] = {
    {
        "VK_LAYER_GOOGLE_unique_objects",
        VK_API_VERSION, // specVersion
        1, // implementationVersion
        "layer: unique_objects",
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
        "VK_LAYER_GOOGLE_unique_objects",
        VK_API_VERSION,
        1,
        "layer: unique_objects",
    }
};
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t *pCount, VkLayerProperties* pProperties)
{
    return util_GetLayerProperties(ARRAY_SIZE(deviceLayerProps), deviceLayerProps, pCount, pProperties);
}


VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
// STRUCT USES:{'pSubmits[submitCount]': {'pSignalSemaphores[signalSemaphoreCount]': 'VkSemaphore', 'pWaitSemaphores[waitSemaphoreCount]': 'VkSemaphore'}, 'fence': 'VkFence'}
    std::vector<VkSemaphore> original_pSignalSemaphores = {};
    std::vector<VkSemaphore> original_pWaitSemaphores = {};
    if (fence) {
        VkFence* pfence = (VkFence*)&fence;
        *pfence = (VkFence)((VkUniqueObject*)fence)->actualObject;
    }
    if (pSubmits) {
        for (uint32_t idx0=0; idx0<submitCount; ++idx0) {
            if (pSubmits[idx0].pSignalSemaphores) {
                for (uint32_t idx1=0; idx1<pSubmits[idx0].signalSemaphoreCount; ++idx1) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pSubmits[idx0].pSignalSemaphores[idx1]);
                    original_pSignalSemaphores.push_back(pSubmits[idx0].pSignalSemaphores[idx1]);
                    *(pSemaphore) = (VkSemaphore)((VkUniqueObject*)pSubmits[idx0].pSignalSemaphores[idx1])->actualObject;
                }
            }
            if (pSubmits[idx0].pWaitSemaphores) {
                for (uint32_t idx2=0; idx2<pSubmits[idx0].waitSemaphoreCount; ++idx2) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pSubmits[idx0].pWaitSemaphores[idx2]);
                    original_pWaitSemaphores.push_back(pSubmits[idx0].pWaitSemaphores[idx2]);
                    *(pSemaphore) = (VkSemaphore)((VkUniqueObject*)pSubmits[idx0].pWaitSemaphores[idx2])->actualObject;
                }
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, queue)->QueueSubmit(queue, submitCount, pSubmits, fence);
    if (pSubmits) {
        for (uint32_t idx0=0; idx0<submitCount; ++idx0) {
            if (pSubmits[idx0].pSignalSemaphores) {
                for (uint32_t idx1=0; idx1<pSubmits[idx0].signalSemaphoreCount; ++idx1) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pSubmits[idx0].pSignalSemaphores[idx1]);
                    *(pSemaphore) = original_pSignalSemaphores.front();
                    original_pSignalSemaphores.erase(original_pSignalSemaphores.begin());
                }
            }
            if (pSubmits[idx0].pWaitSemaphores) {
                for (uint32_t idx2=0; idx2<pSubmits[idx0].waitSemaphoreCount; ++idx2) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pSubmits[idx0].pWaitSemaphores[idx2]);
                    *(pSemaphore) = original_pWaitSemaphores.front();
                    original_pWaitSemaphores.erase(original_pWaitSemaphores.begin());
                }
            }
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueDeviceMemory = new VkUniqueObject();
        uniqueDeviceMemory->actualObject = (uint64_t)*pMemory;
        *pMemory = (VkDeviceMemory)uniqueDeviceMemory;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'memory': 'VkDeviceMemory'}
    VkDeviceMemory local_memory = memory;
    if (memory) {
        VkDeviceMemory* pmemory = (VkDeviceMemory*)&memory;
        *pmemory = (VkDeviceMemory)((VkUniqueObject*)memory)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->FreeMemory(device, memory, pAllocator);
    delete (VkUniqueObject*)local_memory;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)
{
// STRUCT USES:{'memory': 'VkDeviceMemory'}
    if (memory) {
        VkDeviceMemory* pmemory = (VkDeviceMemory*)&memory;
        *pmemory = (VkDeviceMemory)((VkUniqueObject*)memory)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->MapMemory(device, memory, offset, size, flags, ppData);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(VkDevice device, VkDeviceMemory memory)
{
// STRUCT USES:{'memory': 'VkDeviceMemory'}
    if (memory) {
        VkDeviceMemory* pmemory = (VkDeviceMemory*)&memory;
        *pmemory = (VkDeviceMemory)((VkUniqueObject*)memory)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->UnmapMemory(device, memory);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
// STRUCT USES:{'pMemoryRanges[memoryRangeCount]': {'memory': 'VkDeviceMemory'}}
    std::vector<VkDeviceMemory> original_memory = {};
    if (pMemoryRanges) {
        for (uint32_t idx0=0; idx0<memoryRangeCount; ++idx0) {
            if (pMemoryRanges[idx0].memory) {
                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pMemoryRanges[idx0].memory);
                original_memory.push_back(pMemoryRanges[idx0].memory);
                *(pDeviceMemory) = (VkDeviceMemory)((VkUniqueObject*)pMemoryRanges[idx0].memory)->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->FlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    if (pMemoryRanges) {
        for (uint32_t idx0=0; idx0<memoryRangeCount; ++idx0) {
            if (pMemoryRanges[idx0].memory) {
                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pMemoryRanges[idx0].memory);
                *(pDeviceMemory) = original_memory.front();
                original_memory.erase(original_memory.begin());
            }
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
// STRUCT USES:{'pMemoryRanges[memoryRangeCount]': {'memory': 'VkDeviceMemory'}}
    std::vector<VkDeviceMemory> original_memory = {};
    if (pMemoryRanges) {
        for (uint32_t idx0=0; idx0<memoryRangeCount; ++idx0) {
            if (pMemoryRanges[idx0].memory) {
                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pMemoryRanges[idx0].memory);
                original_memory.push_back(pMemoryRanges[idx0].memory);
                *(pDeviceMemory) = (VkDeviceMemory)((VkUniqueObject*)pMemoryRanges[idx0].memory)->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->InvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    if (pMemoryRanges) {
        for (uint32_t idx0=0; idx0<memoryRangeCount; ++idx0) {
            if (pMemoryRanges[idx0].memory) {
                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pMemoryRanges[idx0].memory);
                *(pDeviceMemory) = original_memory.front();
                original_memory.erase(original_memory.begin());
            }
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes)
{
// STRUCT USES:{'memory': 'VkDeviceMemory'}
    if (memory) {
        VkDeviceMemory* pmemory = (VkDeviceMemory*)&memory;
        *pmemory = (VkDeviceMemory)((VkUniqueObject*)memory)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->GetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
// STRUCT USES:{'memory': 'VkDeviceMemory', 'buffer': 'VkBuffer'}
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
    if (memory) {
        VkDeviceMemory* pmemory = (VkDeviceMemory*)&memory;
        *pmemory = (VkDeviceMemory)((VkUniqueObject*)memory)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->BindBufferMemory(device, buffer, memory, memoryOffset);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
// STRUCT USES:{'memory': 'VkDeviceMemory', 'image': 'VkImage'}
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
    if (memory) {
        VkDeviceMemory* pmemory = (VkDeviceMemory*)&memory;
        *pmemory = (VkDeviceMemory)((VkUniqueObject*)memory)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->BindImageMemory(device, image, memory, memoryOffset);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements)
{
// STRUCT USES:{'buffer': 'VkBuffer'}
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->GetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements)
{
// STRUCT USES:{'image': 'VkImage'}
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->GetImageMemoryRequirements(device, image, pMemoryRequirements);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements)
{
// STRUCT USES:{'image': 'VkImage'}
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->GetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence)
{
// STRUCT USES:{'pBindInfo[bindInfoCount]': {'pImageOpaqueBinds[imageOpaqueBindCount]': {'pBinds[bindCount]': {'memory': 'VkDeviceMemory'}, 'image': 'VkImage'}, 'pImageBinds[imageBindCount]': {'pBinds[bindCount]': {'memory': 'VkDeviceMemory'}, 'image': 'VkImage'}, 'pWaitSemaphores[waitSemaphoreCount]': 'VkSemaphore', 'pSignalSemaphores[signalSemaphoreCount]': 'VkSemaphore', 'pBufferBinds[bufferBindCount]': {'pBinds[bindCount]': {'memory': 'VkDeviceMemory'}, 'buffer': 'VkBuffer'}}, 'fence': 'VkFence'}
    std::vector<VkBuffer> original_buffer = {};
    std::vector<VkDeviceMemory> original_memory = {};
    std::vector<VkImage> original_image = {};
    std::vector<VkSemaphore> original_pSignalSemaphores = {};
    std::vector<VkSemaphore> original_pWaitSemaphores = {};
    if (fence) {
        VkFence* pfence = (VkFence*)&fence;
        *pfence = (VkFence)((VkUniqueObject*)fence)->actualObject;
    }
    if (pBindInfo) {
        for (uint32_t idx0=0; idx0<bindInfoCount; ++idx0) {
            if (pBindInfo[idx0].pBufferBinds) {
                for (uint32_t idx1=0; idx1<pBindInfo[idx0].bufferBindCount; ++idx1) {
                    if (pBindInfo[idx0].pBufferBinds[idx1].buffer) {
                        VkBuffer* pBuffer = (VkBuffer*)&(pBindInfo[idx0].pBufferBinds[idx1].buffer);
                        original_buffer.push_back(pBindInfo[idx0].pBufferBinds[idx1].buffer);
                        *(pBuffer) = (VkBuffer)((VkUniqueObject*)pBindInfo[idx0].pBufferBinds[idx1].buffer)->actualObject;
                    }
                    if (pBindInfo[idx0].pBufferBinds[idx1].pBinds) {
                        for (uint32_t idx2=0; idx2<pBindInfo[idx0].pBufferBinds[idx1].bindCount; ++idx2) {
                            if (pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory) {
                                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory);
                                original_memory.push_back(pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory);
                                *(pDeviceMemory) = (VkDeviceMemory)((VkUniqueObject*)pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory)->actualObject;
                            }
                        }
                    }
                }
            }
            if (pBindInfo[idx0].pImageBinds) {
                for (uint32_t idx2=0; idx2<pBindInfo[idx0].imageBindCount; ++idx2) {
                    if (pBindInfo[idx0].pImageBinds[idx2].image) {
                        VkImage* pImage = (VkImage*)&(pBindInfo[idx0].pImageBinds[idx2].image);
                        original_image.push_back(pBindInfo[idx0].pImageBinds[idx2].image);
                        *(pImage) = (VkImage)((VkUniqueObject*)pBindInfo[idx0].pImageBinds[idx2].image)->actualObject;
                    }
                    if (pBindInfo[idx0].pImageBinds[idx2].pBinds) {
                        for (uint32_t idx3=0; idx3<pBindInfo[idx0].pImageBinds[idx2].bindCount; ++idx3) {
                            if (pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory) {
                                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory);
                                original_memory.push_back(pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory);
                                *(pDeviceMemory) = (VkDeviceMemory)((VkUniqueObject*)pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory)->actualObject;
                            }
                        }
                    }
                }
            }
            if (pBindInfo[idx0].pImageOpaqueBinds) {
                for (uint32_t idx3=0; idx3<pBindInfo[idx0].imageOpaqueBindCount; ++idx3) {
                    if (pBindInfo[idx0].pImageOpaqueBinds[idx3].image) {
                        VkImage* pImage = (VkImage*)&(pBindInfo[idx0].pImageOpaqueBinds[idx3].image);
                        original_image.push_back(pBindInfo[idx0].pImageOpaqueBinds[idx3].image);
                        *(pImage) = (VkImage)((VkUniqueObject*)pBindInfo[idx0].pImageOpaqueBinds[idx3].image)->actualObject;
                    }
                    if (pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds) {
                        for (uint32_t idx4=0; idx4<pBindInfo[idx0].pImageOpaqueBinds[idx3].bindCount; ++idx4) {
                            if (pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory) {
                                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory);
                                original_memory.push_back(pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory);
                                *(pDeviceMemory) = (VkDeviceMemory)((VkUniqueObject*)pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory)->actualObject;
                            }
                        }
                    }
                }
            }
            if (pBindInfo[idx0].pSignalSemaphores) {
                for (uint32_t idx4=0; idx4<pBindInfo[idx0].signalSemaphoreCount; ++idx4) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pBindInfo[idx0].pSignalSemaphores[idx4]);
                    original_pSignalSemaphores.push_back(pBindInfo[idx0].pSignalSemaphores[idx4]);
                    *(pSemaphore) = (VkSemaphore)((VkUniqueObject*)pBindInfo[idx0].pSignalSemaphores[idx4])->actualObject;
                }
            }
            if (pBindInfo[idx0].pWaitSemaphores) {
                for (uint32_t idx5=0; idx5<pBindInfo[idx0].waitSemaphoreCount; ++idx5) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pBindInfo[idx0].pWaitSemaphores[idx5]);
                    original_pWaitSemaphores.push_back(pBindInfo[idx0].pWaitSemaphores[idx5]);
                    *(pSemaphore) = (VkSemaphore)((VkUniqueObject*)pBindInfo[idx0].pWaitSemaphores[idx5])->actualObject;
                }
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, queue)->QueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
    if (pBindInfo) {
        for (uint32_t idx0=0; idx0<bindInfoCount; ++idx0) {
            if (pBindInfo[idx0].pBufferBinds) {
                for (uint32_t idx1=0; idx1<pBindInfo[idx0].bufferBindCount; ++idx1) {
                    if (pBindInfo[idx0].pBufferBinds[idx1].buffer) {
                        VkBuffer* pBuffer = (VkBuffer*)&(pBindInfo[idx0].pBufferBinds[idx1].buffer);
                        *(pBuffer) = original_buffer.front();
                        original_buffer.erase(original_buffer.begin());
                    }
                    if (pBindInfo[idx0].pBufferBinds[idx1].pBinds) {
                        for (uint32_t idx2=0; idx2<pBindInfo[idx0].pBufferBinds[idx1].bindCount; ++idx2) {
                            if (pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory) {
                                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory);
                                *(pDeviceMemory) = original_memory.front();
                                original_memory.erase(original_memory.begin());
                            }
                        }
                    }
                }
            }
            if (pBindInfo[idx0].pImageBinds) {
                for (uint32_t idx2=0; idx2<pBindInfo[idx0].imageBindCount; ++idx2) {
                    if (pBindInfo[idx0].pImageBinds[idx2].image) {
                        VkImage* pImage = (VkImage*)&(pBindInfo[idx0].pImageBinds[idx2].image);
                        *(pImage) = original_image.front();
                        original_image.erase(original_image.begin());
                    }
                    if (pBindInfo[idx0].pImageBinds[idx2].pBinds) {
                        for (uint32_t idx3=0; idx3<pBindInfo[idx0].pImageBinds[idx2].bindCount; ++idx3) {
                            if (pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory) {
                                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory);
                                *(pDeviceMemory) = original_memory.front();
                                original_memory.erase(original_memory.begin());
                            }
                        }
                    }
                }
            }
            if (pBindInfo[idx0].pImageOpaqueBinds) {
                for (uint32_t idx3=0; idx3<pBindInfo[idx0].imageOpaqueBindCount; ++idx3) {
                    if (pBindInfo[idx0].pImageOpaqueBinds[idx3].image) {
                        VkImage* pImage = (VkImage*)&(pBindInfo[idx0].pImageOpaqueBinds[idx3].image);
                        *(pImage) = original_image.front();
                        original_image.erase(original_image.begin());
                    }
                    if (pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds) {
                        for (uint32_t idx4=0; idx4<pBindInfo[idx0].pImageOpaqueBinds[idx3].bindCount; ++idx4) {
                            if (pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory) {
                                VkDeviceMemory* pDeviceMemory = (VkDeviceMemory*)&(pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory);
                                *(pDeviceMemory) = original_memory.front();
                                original_memory.erase(original_memory.begin());
                            }
                        }
                    }
                }
            }
            if (pBindInfo[idx0].pSignalSemaphores) {
                for (uint32_t idx4=0; idx4<pBindInfo[idx0].signalSemaphoreCount; ++idx4) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pBindInfo[idx0].pSignalSemaphores[idx4]);
                    *(pSemaphore) = original_pSignalSemaphores.front();
                    original_pSignalSemaphores.erase(original_pSignalSemaphores.begin());
                }
            }
            if (pBindInfo[idx0].pWaitSemaphores) {
                for (uint32_t idx5=0; idx5<pBindInfo[idx0].waitSemaphoreCount; ++idx5) {
                    VkSemaphore* pSemaphore = (VkSemaphore*)&(pBindInfo[idx0].pWaitSemaphores[idx5]);
                    *(pSemaphore) = original_pWaitSemaphores.front();
                    original_pWaitSemaphores.erase(original_pWaitSemaphores.begin());
                }
            }
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateFence(device, pCreateInfo, pAllocator, pFence);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueFence = new VkUniqueObject();
        uniqueFence->actualObject = (uint64_t)*pFence;
        *pFence = (VkFence)uniqueFence;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'fence': 'VkFence'}
    VkFence local_fence = fence;
    if (fence) {
        VkFence* pfence = (VkFence*)&fence;
        *pfence = (VkFence)((VkUniqueObject*)fence)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyFence(device, fence, pAllocator);
    delete (VkUniqueObject*)local_fence;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences)
{
// STRUCT USES:{'pFences[fenceCount]': 'VkFence'}
    std::vector<VkFence> original_pFences = {};
    if (pFences) {
        for (uint32_t idx0=0; idx0<fenceCount; ++idx0) {
            VkFence* pFence = (VkFence*)&(pFences[idx0]);
            original_pFences.push_back(pFences[idx0]);
            *(pFence) = (VkFence)((VkUniqueObject*)pFences[idx0])->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetFences(device, fenceCount, pFences);
    if (pFences) {
        for (uint32_t idx0=0; idx0<fenceCount; ++idx0) {
            VkFence* pFence = (VkFence*)&(pFences[idx0]);
            *(pFence) = original_pFences.front();
            original_pFences.erase(original_pFences.begin());
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceStatus(VkDevice device, VkFence fence)
{
// STRUCT USES:{'fence': 'VkFence'}
    if (fence) {
        VkFence* pfence = (VkFence*)&fence;
        *pfence = (VkFence)((VkUniqueObject*)fence)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetFenceStatus(device, fence);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout)
{
// STRUCT USES:{'pFences[fenceCount]': 'VkFence'}
    std::vector<VkFence> original_pFences = {};
    if (pFences) {
        for (uint32_t idx0=0; idx0<fenceCount; ++idx0) {
            VkFence* pFence = (VkFence*)&(pFences[idx0]);
            original_pFences.push_back(pFences[idx0]);
            *(pFence) = (VkFence)((VkUniqueObject*)pFences[idx0])->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->WaitForFences(device, fenceCount, pFences, waitAll, timeout);
    if (pFences) {
        for (uint32_t idx0=0; idx0<fenceCount; ++idx0) {
            VkFence* pFence = (VkFence*)&(pFences[idx0]);
            *(pFence) = original_pFences.front();
            original_pFences.erase(original_pFences.begin());
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueSemaphore = new VkUniqueObject();
        uniqueSemaphore->actualObject = (uint64_t)*pSemaphore;
        *pSemaphore = (VkSemaphore)uniqueSemaphore;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'semaphore': 'VkSemaphore'}
    VkSemaphore local_semaphore = semaphore;
    if (semaphore) {
        VkSemaphore* psemaphore = (VkSemaphore*)&semaphore;
        *psemaphore = (VkSemaphore)((VkUniqueObject*)semaphore)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroySemaphore(device, semaphore, pAllocator);
    delete (VkUniqueObject*)local_semaphore;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateEvent(device, pCreateInfo, pAllocator, pEvent);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueEvent = new VkUniqueObject();
        uniqueEvent->actualObject = (uint64_t)*pEvent;
        *pEvent = (VkEvent)uniqueEvent;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'event': 'VkEvent'}
    VkEvent local_event = event;
    if (event) {
        VkEvent* pevent = (VkEvent*)&event;
        *pevent = (VkEvent)((VkUniqueObject*)event)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyEvent(device, event, pAllocator);
    delete (VkUniqueObject*)local_event;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetEventStatus(VkDevice device, VkEvent event)
{
// STRUCT USES:{'event': 'VkEvent'}
    if (event) {
        VkEvent* pevent = (VkEvent*)&event;
        *pevent = (VkEvent)((VkUniqueObject*)event)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetEventStatus(device, event);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkSetEvent(VkDevice device, VkEvent event)
{
// STRUCT USES:{'event': 'VkEvent'}
    if (event) {
        VkEvent* pevent = (VkEvent*)&event;
        *pevent = (VkEvent)((VkUniqueObject*)event)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->SetEvent(device, event);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetEvent(VkDevice device, VkEvent event)
{
// STRUCT USES:{'event': 'VkEvent'}
    if (event) {
        VkEvent* pevent = (VkEvent*)&event;
        *pevent = (VkEvent)((VkUniqueObject*)event)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetEvent(device, event);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueQueryPool = new VkUniqueObject();
        uniqueQueryPool->actualObject = (uint64_t)*pQueryPool;
        *pQueryPool = (VkQueryPool)uniqueQueryPool;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'queryPool': 'VkQueryPool'}
    VkQueryPool local_queryPool = queryPool;
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyQueryPool(device, queryPool, pAllocator);
    delete (VkUniqueObject*)local_queryPool;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags)
{
// STRUCT USES:{'queryPool': 'VkQueryPool'}
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueBuffer = new VkUniqueObject();
        uniqueBuffer->actualObject = (uint64_t)*pBuffer;
        *pBuffer = (VkBuffer)uniqueBuffer;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'buffer': 'VkBuffer'}
    VkBuffer local_buffer = buffer;
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyBuffer(device, buffer, pAllocator);
    delete (VkUniqueObject*)local_buffer;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView)
{
// STRUCT USES:{'pCreateInfo': {'buffer': 'VkBuffer'}}
    VkBuffer local_buffer = VK_NULL_HANDLE;
    if (pCreateInfo) {
        local_buffer = pCreateInfo->buffer;
        if (pCreateInfo->buffer) {
            VkBuffer* pbuffer = (VkBuffer*)&pCreateInfo->buffer;
            *pbuffer = (VkBuffer)((VkUniqueObject*)pCreateInfo->buffer)->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateBufferView(device, pCreateInfo, pAllocator, pView);
    if (pCreateInfo) {
        if (pCreateInfo->buffer) {
            VkBuffer* pbuffer = (VkBuffer*)&pCreateInfo->buffer;
            *pbuffer = local_buffer;
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueBufferView = new VkUniqueObject();
        uniqueBufferView->actualObject = (uint64_t)*pView;
        *pView = (VkBufferView)uniqueBufferView;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'bufferView': 'VkBufferView'}
    VkBufferView local_bufferView = bufferView;
    if (bufferView) {
        VkBufferView* pbufferView = (VkBufferView*)&bufferView;
        *pbufferView = (VkBufferView)((VkUniqueObject*)bufferView)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyBufferView(device, bufferView, pAllocator);
    delete (VkUniqueObject*)local_bufferView;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateImage(device, pCreateInfo, pAllocator, pImage);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueImage = new VkUniqueObject();
        uniqueImage->actualObject = (uint64_t)*pImage;
        *pImage = (VkImage)uniqueImage;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'image': 'VkImage'}
    VkImage local_image = image;
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyImage(device, image, pAllocator);
    delete (VkUniqueObject*)local_image;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout)
{
// STRUCT USES:{'image': 'VkImage'}
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->GetImageSubresourceLayout(device, image, pSubresource, pLayout);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView)
{
// STRUCT USES:{'pCreateInfo': {'image': 'VkImage'}}
    VkImage local_image = VK_NULL_HANDLE;
    if (pCreateInfo) {
        local_image = pCreateInfo->image;
        if (pCreateInfo->image) {
            VkImage* pimage = (VkImage*)&pCreateInfo->image;
            *pimage = (VkImage)((VkUniqueObject*)pCreateInfo->image)->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateImageView(device, pCreateInfo, pAllocator, pView);
    if (pCreateInfo) {
        if (pCreateInfo->image) {
            VkImage* pimage = (VkImage*)&pCreateInfo->image;
            *pimage = local_image;
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueImageView = new VkUniqueObject();
        uniqueImageView->actualObject = (uint64_t)*pView;
        *pView = (VkImageView)uniqueImageView;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'imageView': 'VkImageView'}
    VkImageView local_imageView = imageView;
    if (imageView) {
        VkImageView* pimageView = (VkImageView*)&imageView;
        *pimageView = (VkImageView)((VkUniqueObject*)imageView)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyImageView(device, imageView, pAllocator);
    delete (VkUniqueObject*)local_imageView;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueShaderModule = new VkUniqueObject();
        uniqueShaderModule->actualObject = (uint64_t)*pShaderModule;
        *pShaderModule = (VkShaderModule)uniqueShaderModule;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'shaderModule': 'VkShaderModule'}
    VkShaderModule local_shaderModule = shaderModule;
    if (shaderModule) {
        VkShaderModule* pshaderModule = (VkShaderModule*)&shaderModule;
        *pshaderModule = (VkShaderModule)((VkUniqueObject*)shaderModule)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyShaderModule(device, shaderModule, pAllocator);
    delete (VkUniqueObject*)local_shaderModule;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniquePipelineCache = new VkUniqueObject();
        uniquePipelineCache->actualObject = (uint64_t)*pPipelineCache;
        *pPipelineCache = (VkPipelineCache)uniquePipelineCache;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'pipelineCache': 'VkPipelineCache'}
    VkPipelineCache local_pipelineCache = pipelineCache;
    if (pipelineCache) {
        VkPipelineCache* ppipelineCache = (VkPipelineCache*)&pipelineCache;
        *ppipelineCache = (VkPipelineCache)((VkUniqueObject*)pipelineCache)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyPipelineCache(device, pipelineCache, pAllocator);
    delete (VkUniqueObject*)local_pipelineCache;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData)
{
// STRUCT USES:{'pipelineCache': 'VkPipelineCache'}
    if (pipelineCache) {
        VkPipelineCache* ppipelineCache = (VkPipelineCache*)&pipelineCache;
        *ppipelineCache = (VkPipelineCache)((VkUniqueObject*)pipelineCache)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetPipelineCacheData(device, pipelineCache, pDataSize, pData);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches)
{
// STRUCT USES:{'dstCache': 'VkPipelineCache', 'pSrcCaches[srcCacheCount]': 'VkPipelineCache'}
    std::vector<VkPipelineCache> original_pSrcCaches = {};
    if (dstCache) {
        VkPipelineCache* pdstCache = (VkPipelineCache*)&dstCache;
        *pdstCache = (VkPipelineCache)((VkUniqueObject*)dstCache)->actualObject;
    }
    if (pSrcCaches) {
        for (uint32_t idx0=0; idx0<srcCacheCount; ++idx0) {
            VkPipelineCache* pPipelineCache = (VkPipelineCache*)&(pSrcCaches[idx0]);
            original_pSrcCaches.push_back(pSrcCaches[idx0]);
            *(pPipelineCache) = (VkPipelineCache)((VkUniqueObject*)pSrcCaches[idx0])->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->MergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
    if (pSrcCaches) {
        for (uint32_t idx0=0; idx0<srcCacheCount; ++idx0) {
            VkPipelineCache* pPipelineCache = (VkPipelineCache*)&(pSrcCaches[idx0]);
            *(pPipelineCache) = original_pSrcCaches.front();
            original_pSrcCaches.erase(original_pSrcCaches.begin());
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    return explicit_CreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    return explicit_CreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'pipeline': 'VkPipeline'}
    VkPipeline local_pipeline = pipeline;
    if (pipeline) {
        VkPipeline* ppipeline = (VkPipeline*)&pipeline;
        *ppipeline = (VkPipeline)((VkUniqueObject*)pipeline)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyPipeline(device, pipeline, pAllocator);
    delete (VkUniqueObject*)local_pipeline;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
// STRUCT USES:{'pCreateInfo': {'pSetLayouts[setLayoutCount]': 'VkDescriptorSetLayout'}}
    std::vector<VkDescriptorSetLayout> original_pSetLayouts = {};
    if (pCreateInfo) {
        if (pCreateInfo->pSetLayouts) {
            for (uint32_t idx0=0; idx0<pCreateInfo->setLayoutCount; ++idx0) {
                VkDescriptorSetLayout* pDescriptorSetLayout = (VkDescriptorSetLayout*)&(pCreateInfo->pSetLayouts[idx0]);
                original_pSetLayouts.push_back(pCreateInfo->pSetLayouts[idx0]);
                *(pDescriptorSetLayout) = (VkDescriptorSetLayout)((VkUniqueObject*)pCreateInfo->pSetLayouts[idx0])->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
    if (pCreateInfo) {
        if (pCreateInfo->pSetLayouts) {
            for (uint32_t idx0=0; idx0<pCreateInfo->setLayoutCount; ++idx0) {
                VkDescriptorSetLayout* pDescriptorSetLayout = (VkDescriptorSetLayout*)&(pCreateInfo->pSetLayouts[idx0]);
                *(pDescriptorSetLayout) = original_pSetLayouts.front();
                original_pSetLayouts.erase(original_pSetLayouts.begin());
            }
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniquePipelineLayout = new VkUniqueObject();
        uniquePipelineLayout->actualObject = (uint64_t)*pPipelineLayout;
        *pPipelineLayout = (VkPipelineLayout)uniquePipelineLayout;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'pipelineLayout': 'VkPipelineLayout'}
    VkPipelineLayout local_pipelineLayout = pipelineLayout;
    if (pipelineLayout) {
        VkPipelineLayout* ppipelineLayout = (VkPipelineLayout*)&pipelineLayout;
        *ppipelineLayout = (VkPipelineLayout)((VkUniqueObject*)pipelineLayout)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyPipelineLayout(device, pipelineLayout, pAllocator);
    delete (VkUniqueObject*)local_pipelineLayout;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateSampler(device, pCreateInfo, pAllocator, pSampler);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueSampler = new VkUniqueObject();
        uniqueSampler->actualObject = (uint64_t)*pSampler;
        *pSampler = (VkSampler)uniqueSampler;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'sampler': 'VkSampler'}
    VkSampler local_sampler = sampler;
    if (sampler) {
        VkSampler* psampler = (VkSampler*)&sampler;
        *psampler = (VkSampler)((VkUniqueObject*)sampler)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroySampler(device, sampler, pAllocator);
    delete (VkUniqueObject*)local_sampler;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout)
{
// STRUCT USES:{'pCreateInfo': {'pBindings[bindingCount]': {'pImmutableSamplers[descriptorCount]': 'VkSampler'}}}
    std::vector<VkSampler> original_pImmutableSamplers = {};
    if (pCreateInfo) {
        if (pCreateInfo->pBindings) {
            for (uint32_t idx0=0; idx0<pCreateInfo->bindingCount; ++idx0) {
                if (pCreateInfo->pBindings[idx0].pImmutableSamplers) {
                    for (uint32_t idx1=0; idx1<pCreateInfo->pBindings[idx0].descriptorCount; ++idx1) {
                        VkSampler* pSampler = (VkSampler*)&(pCreateInfo->pBindings[idx0].pImmutableSamplers[idx1]);
                        original_pImmutableSamplers.push_back(pCreateInfo->pBindings[idx0].pImmutableSamplers[idx1]);
                        *(pSampler) = (VkSampler)((VkUniqueObject*)pCreateInfo->pBindings[idx0].pImmutableSamplers[idx1])->actualObject;
                    }
                }
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
    if (pCreateInfo) {
        if (pCreateInfo->pBindings) {
            for (uint32_t idx0=0; idx0<pCreateInfo->bindingCount; ++idx0) {
                if (pCreateInfo->pBindings[idx0].pImmutableSamplers) {
                    for (uint32_t idx1=0; idx1<pCreateInfo->pBindings[idx0].descriptorCount; ++idx1) {
                        VkSampler* pSampler = (VkSampler*)&(pCreateInfo->pBindings[idx0].pImmutableSamplers[idx1]);
                        *(pSampler) = original_pImmutableSamplers.front();
                        original_pImmutableSamplers.erase(original_pImmutableSamplers.begin());
                    }
                }
            }
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueDescriptorSetLayout = new VkUniqueObject();
        uniqueDescriptorSetLayout->actualObject = (uint64_t)*pSetLayout;
        *pSetLayout = (VkDescriptorSetLayout)uniqueDescriptorSetLayout;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'descriptorSetLayout': 'VkDescriptorSetLayout'}
    VkDescriptorSetLayout local_descriptorSetLayout = descriptorSetLayout;
    if (descriptorSetLayout) {
        VkDescriptorSetLayout* pdescriptorSetLayout = (VkDescriptorSetLayout*)&descriptorSetLayout;
        *pdescriptorSetLayout = (VkDescriptorSetLayout)((VkUniqueObject*)descriptorSetLayout)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
    delete (VkUniqueObject*)local_descriptorSetLayout;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueDescriptorPool = new VkUniqueObject();
        uniqueDescriptorPool->actualObject = (uint64_t)*pDescriptorPool;
        *pDescriptorPool = (VkDescriptorPool)uniqueDescriptorPool;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'descriptorPool': 'VkDescriptorPool'}
    VkDescriptorPool local_descriptorPool = descriptorPool;
    if (descriptorPool) {
        VkDescriptorPool* pdescriptorPool = (VkDescriptorPool*)&descriptorPool;
        *pdescriptorPool = (VkDescriptorPool)((VkUniqueObject*)descriptorPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyDescriptorPool(device, descriptorPool, pAllocator);
    delete (VkUniqueObject*)local_descriptorPool;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags)
{
// STRUCT USES:{'descriptorPool': 'VkDescriptorPool'}
    if (descriptorPool) {
        VkDescriptorPool* pdescriptorPool = (VkDescriptorPool*)&descriptorPool;
        *pdescriptorPool = (VkDescriptorPool)((VkUniqueObject*)descriptorPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetDescriptorPool(device, descriptorPool, flags);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets)
{
// STRUCT USES:{'pAllocateInfo': {'descriptorPool': 'VkDescriptorPool', 'pSetLayouts[descriptorSetCount]': 'VkDescriptorSetLayout'}}
    VkDescriptorPool local_descriptorPool = VK_NULL_HANDLE;
    std::vector<VkDescriptorSetLayout> original_pSetLayouts = {};
    if (pAllocateInfo) {
        local_descriptorPool = pAllocateInfo->descriptorPool;
        if (pAllocateInfo->descriptorPool) {
            VkDescriptorPool* pdescriptorPool = (VkDescriptorPool*)&pAllocateInfo->descriptorPool;
            *pdescriptorPool = (VkDescriptorPool)((VkUniqueObject*)pAllocateInfo->descriptorPool)->actualObject;
        }
        if (pAllocateInfo->pSetLayouts) {
            for (uint32_t idx0=0; idx0<pAllocateInfo->descriptorSetCount; ++idx0) {
                VkDescriptorSetLayout* pDescriptorSetLayout = (VkDescriptorSetLayout*)&(pAllocateInfo->pSetLayouts[idx0]);
                original_pSetLayouts.push_back(pAllocateInfo->pSetLayouts[idx0]);
                *(pDescriptorSetLayout) = (VkDescriptorSetLayout)((VkUniqueObject*)pAllocateInfo->pSetLayouts[idx0])->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
    if (pAllocateInfo) {
        if (pAllocateInfo->descriptorPool) {
            VkDescriptorPool* pdescriptorPool = (VkDescriptorPool*)&pAllocateInfo->descriptorPool;
            *pdescriptorPool = local_descriptorPool;
        }
        if (pAllocateInfo->pSetLayouts) {
            for (uint32_t idx0=0; idx0<pAllocateInfo->descriptorSetCount; ++idx0) {
                VkDescriptorSetLayout* pDescriptorSetLayout = (VkDescriptorSetLayout*)&(pAllocateInfo->pSetLayouts[idx0]);
                *(pDescriptorSetLayout) = original_pSetLayouts.front();
                original_pSetLayouts.erase(original_pSetLayouts.begin());
            }
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1604
        std::vector<VkUniqueObject*> uniqueDescriptorSets = {};
        for (uint32_t i=0; i<pAllocateInfo->descriptorSetCount; ++i) {
            uniqueDescriptorSets.push_back(new VkUniqueObject());
            uniqueDescriptorSets[i]->actualObject = (uint64_t)pDescriptorSets[i];
            pDescriptorSets[i] = (VkDescriptorSet)uniqueDescriptorSets[i];
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
// STRUCT USES:{'descriptorPool': 'VkDescriptorPool', 'pDescriptorSets[descriptorSetCount]': 'VkDescriptorSet'}
    std::vector<VkDescriptorSet> original_pDescriptorSets = {};
    if (descriptorPool) {
        VkDescriptorPool* pdescriptorPool = (VkDescriptorPool*)&descriptorPool;
        *pdescriptorPool = (VkDescriptorPool)((VkUniqueObject*)descriptorPool)->actualObject;
    }
    if (pDescriptorSets) {
        for (uint32_t idx0=0; idx0<descriptorSetCount; ++idx0) {
            VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorSets[idx0]);
            original_pDescriptorSets.push_back(pDescriptorSets[idx0]);
            *(pDescriptorSet) = (VkDescriptorSet)((VkUniqueObject*)pDescriptorSets[idx0])->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->FreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    if (pDescriptorSets) {
        for (uint32_t idx0=0; idx0<descriptorSetCount; ++idx0) {
            VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorSets[idx0]);
            *(pDescriptorSet) = original_pDescriptorSets.front();
            original_pDescriptorSets.erase(original_pDescriptorSets.begin());
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies)
{
// STRUCT USES:{'pDescriptorCopies[descriptorCopyCount]': {'srcSet': 'VkDescriptorSet', 'dstSet': 'VkDescriptorSet'}, 'pDescriptorWrites[descriptorWriteCount]': {'pTexelBufferView[descriptorCount]': 'VkBufferView', 'pBufferInfo[descriptorCount]': {'buffer': 'VkBuffer'}, 'dstSet': 'VkDescriptorSet', 'pImageInfo[descriptorCount]': {'imageView': 'VkImageView', 'sampler': 'VkSampler'}}}
    std::vector<VkDescriptorSet> original_dstSet = {};
    std::vector<VkDescriptorSet> original_srcSet = {};
    std::vector<VkBuffer> original_buffer = {};
    std::vector<VkImageView> original_imageView = {};
    std::vector<VkSampler> original_sampler = {};
    std::vector<VkBufferView> original_pTexelBufferView = {};
    if (pDescriptorCopies) {
        for (uint32_t idx0=0; idx0<descriptorCopyCount; ++idx0) {
            if (pDescriptorCopies[idx0].dstSet) {
                VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorCopies[idx0].dstSet);
                original_dstSet.push_back(pDescriptorCopies[idx0].dstSet);
                *(pDescriptorSet) = (VkDescriptorSet)((VkUniqueObject*)pDescriptorCopies[idx0].dstSet)->actualObject;
            }
            if (pDescriptorCopies[idx0].srcSet) {
                VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorCopies[idx0].srcSet);
                original_srcSet.push_back(pDescriptorCopies[idx0].srcSet);
                *(pDescriptorSet) = (VkDescriptorSet)((VkUniqueObject*)pDescriptorCopies[idx0].srcSet)->actualObject;
            }
        }
    }
    if (pDescriptorWrites) {
        for (uint32_t idx1=0; idx1<descriptorWriteCount; ++idx1) {
            if (pDescriptorWrites[idx1].dstSet) {
                VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorWrites[idx1].dstSet);
                original_dstSet.push_back(pDescriptorWrites[idx1].dstSet);
                *(pDescriptorSet) = (VkDescriptorSet)((VkUniqueObject*)pDescriptorWrites[idx1].dstSet)->actualObject;
            }
            if (pDescriptorWrites[idx1].pBufferInfo) {
                for (uint32_t idx2=0; idx2<pDescriptorWrites[idx1].descriptorCount; ++idx2) {
                    if (pDescriptorWrites[idx1].pBufferInfo[idx2].buffer) {
                        VkBuffer* pBuffer = (VkBuffer*)&(pDescriptorWrites[idx1].pBufferInfo[idx2].buffer);
                        original_buffer.push_back(pDescriptorWrites[idx1].pBufferInfo[idx2].buffer);
                        *(pBuffer) = (VkBuffer)((VkUniqueObject*)pDescriptorWrites[idx1].pBufferInfo[idx2].buffer)->actualObject;
                    }
                }
            }
            if (pDescriptorWrites[idx1].pImageInfo) {
                for (uint32_t idx3=0; idx3<pDescriptorWrites[idx1].descriptorCount; ++idx3) {
                    if (pDescriptorWrites[idx1].pImageInfo[idx3].imageView) {
                        VkImageView* pImageView = (VkImageView*)&(pDescriptorWrites[idx1].pImageInfo[idx3].imageView);
                        original_imageView.push_back(pDescriptorWrites[idx1].pImageInfo[idx3].imageView);
                        *(pImageView) = (VkImageView)((VkUniqueObject*)pDescriptorWrites[idx1].pImageInfo[idx3].imageView)->actualObject;
                    }
                    if (pDescriptorWrites[idx1].pImageInfo[idx3].sampler) {
                        VkSampler* pSampler = (VkSampler*)&(pDescriptorWrites[idx1].pImageInfo[idx3].sampler);
                        original_sampler.push_back(pDescriptorWrites[idx1].pImageInfo[idx3].sampler);
                        *(pSampler) = (VkSampler)((VkUniqueObject*)pDescriptorWrites[idx1].pImageInfo[idx3].sampler)->actualObject;
                    }
                }
            }
            if (pDescriptorWrites[idx1].pTexelBufferView) {
                for (uint32_t idx4=0; idx4<pDescriptorWrites[idx1].descriptorCount; ++idx4) {
                    VkBufferView* pBufferView = (VkBufferView*)&(pDescriptorWrites[idx1].pTexelBufferView[idx4]);
                    original_pTexelBufferView.push_back(pDescriptorWrites[idx1].pTexelBufferView[idx4]);
                    *(pBufferView) = (VkBufferView)((VkUniqueObject*)pDescriptorWrites[idx1].pTexelBufferView[idx4])->actualObject;
                }
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->UpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    if (pDescriptorCopies) {
        for (uint32_t idx0=0; idx0<descriptorCopyCount; ++idx0) {
            if (pDescriptorCopies[idx0].dstSet) {
                VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorCopies[idx0].dstSet);
                *(pDescriptorSet) = original_dstSet.front();
                original_dstSet.erase(original_dstSet.begin());
            }
            if (pDescriptorCopies[idx0].srcSet) {
                VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorCopies[idx0].srcSet);
                *(pDescriptorSet) = original_srcSet.front();
                original_srcSet.erase(original_srcSet.begin());
            }
        }
    }
    if (pDescriptorWrites) {
        for (uint32_t idx1=0; idx1<descriptorWriteCount; ++idx1) {
            if (pDescriptorWrites[idx1].dstSet) {
                VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorWrites[idx1].dstSet);
                *(pDescriptorSet) = original_dstSet.front();
                original_dstSet.erase(original_dstSet.begin());
            }
            if (pDescriptorWrites[idx1].pBufferInfo) {
                for (uint32_t idx2=0; idx2<pDescriptorWrites[idx1].descriptorCount; ++idx2) {
                    if (pDescriptorWrites[idx1].pBufferInfo[idx2].buffer) {
                        VkBuffer* pBuffer = (VkBuffer*)&(pDescriptorWrites[idx1].pBufferInfo[idx2].buffer);
                        *(pBuffer) = original_buffer.front();
                        original_buffer.erase(original_buffer.begin());
                    }
                }
            }
            if (pDescriptorWrites[idx1].pImageInfo) {
                for (uint32_t idx3=0; idx3<pDescriptorWrites[idx1].descriptorCount; ++idx3) {
                    if (pDescriptorWrites[idx1].pImageInfo[idx3].imageView) {
                        VkImageView* pImageView = (VkImageView*)&(pDescriptorWrites[idx1].pImageInfo[idx3].imageView);
                        *(pImageView) = original_imageView.front();
                        original_imageView.erase(original_imageView.begin());
                    }
                    if (pDescriptorWrites[idx1].pImageInfo[idx3].sampler) {
                        VkSampler* pSampler = (VkSampler*)&(pDescriptorWrites[idx1].pImageInfo[idx3].sampler);
                        *(pSampler) = original_sampler.front();
                        original_sampler.erase(original_sampler.begin());
                    }
                }
            }
            if (pDescriptorWrites[idx1].pTexelBufferView) {
                for (uint32_t idx4=0; idx4<pDescriptorWrites[idx1].descriptorCount; ++idx4) {
                    VkBufferView* pBufferView = (VkBufferView*)&(pDescriptorWrites[idx1].pTexelBufferView[idx4]);
                    *(pBufferView) = original_pTexelBufferView.front();
                    original_pTexelBufferView.erase(original_pTexelBufferView.begin());
                }
            }
        }
    }
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer)
{
// STRUCT USES:{'pCreateInfo': {'pAttachments[attachmentCount]': 'VkImageView', 'renderPass': 'VkRenderPass'}}
    std::vector<VkImageView> original_pAttachments = {};
    std::vector<VkRenderPass> original_renderPass = {};
    if (pCreateInfo) {
        if (pCreateInfo->pAttachments) {
            for (uint32_t idx0=0; idx0<pCreateInfo->attachmentCount; ++idx0) {
                VkImageView* pImageView = (VkImageView*)&(pCreateInfo->pAttachments[idx0]);
                original_pAttachments.push_back(pCreateInfo->pAttachments[idx0]);
                *(pImageView) = (VkImageView)((VkUniqueObject*)pCreateInfo->pAttachments[idx0])->actualObject;
            }
        }
        if (pCreateInfo->renderPass) {
            VkRenderPass* pRenderPass = (VkRenderPass*)&(pCreateInfo->renderPass);
            original_renderPass.push_back(pCreateInfo->renderPass);
            *(pRenderPass) = (VkRenderPass)((VkUniqueObject*)pCreateInfo->renderPass)->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
    if (pCreateInfo) {
        if (pCreateInfo->pAttachments) {
            for (uint32_t idx0=0; idx0<pCreateInfo->attachmentCount; ++idx0) {
                VkImageView* pImageView = (VkImageView*)&(pCreateInfo->pAttachments[idx0]);
                *(pImageView) = original_pAttachments.front();
                original_pAttachments.erase(original_pAttachments.begin());
            }
        }
        if (pCreateInfo->renderPass) {
            VkRenderPass* pRenderPass = (VkRenderPass*)&(pCreateInfo->renderPass);
            *(pRenderPass) = original_renderPass.front();
            original_renderPass.erase(original_renderPass.begin());
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueFramebuffer = new VkUniqueObject();
        uniqueFramebuffer->actualObject = (uint64_t)*pFramebuffer;
        *pFramebuffer = (VkFramebuffer)uniqueFramebuffer;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'framebuffer': 'VkFramebuffer'}
    VkFramebuffer local_framebuffer = framebuffer;
    if (framebuffer) {
        VkFramebuffer* pframebuffer = (VkFramebuffer*)&framebuffer;
        *pframebuffer = (VkFramebuffer)((VkUniqueObject*)framebuffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyFramebuffer(device, framebuffer, pAllocator);
    delete (VkUniqueObject*)local_framebuffer;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueRenderPass = new VkUniqueObject();
        uniqueRenderPass->actualObject = (uint64_t)*pRenderPass;
        *pRenderPass = (VkRenderPass)uniqueRenderPass;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'renderPass': 'VkRenderPass'}
    VkRenderPass local_renderPass = renderPass;
    if (renderPass) {
        VkRenderPass* prenderPass = (VkRenderPass*)&renderPass;
        *prenderPass = (VkRenderPass)((VkUniqueObject*)renderPass)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyRenderPass(device, renderPass, pAllocator);
    delete (VkUniqueObject*)local_renderPass;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity)
{
// STRUCT USES:{'renderPass': 'VkRenderPass'}
    if (renderPass) {
        VkRenderPass* prenderPass = (VkRenderPass*)&renderPass;
        *prenderPass = (VkRenderPass)((VkUniqueObject*)renderPass)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->GetRenderAreaGranularity(device, renderPass, pGranularity);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueCommandPool = new VkUniqueObject();
        uniqueCommandPool->actualObject = (uint64_t)*pCommandPool;
        *pCommandPool = (VkCommandPool)uniqueCommandPool;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'commandPool': 'VkCommandPool'}
    VkCommandPool local_commandPool = commandPool;
    if (commandPool) {
        VkCommandPool* pcommandPool = (VkCommandPool*)&commandPool;
        *pcommandPool = (VkCommandPool)((VkUniqueObject*)commandPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyCommandPool(device, commandPool, pAllocator);
    delete (VkUniqueObject*)local_commandPool;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags)
{
// STRUCT USES:{'commandPool': 'VkCommandPool'}
    if (commandPool) {
        VkCommandPool* pcommandPool = (VkCommandPool*)&commandPool;
        *pcommandPool = (VkCommandPool)((VkUniqueObject*)commandPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetCommandPool(device, commandPool, flags);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
// STRUCT USES:{'pAllocateInfo': {'commandPool': 'VkCommandPool'}}
    VkCommandPool local_commandPool = VK_NULL_HANDLE;
    if (pAllocateInfo) {
        local_commandPool = pAllocateInfo->commandPool;
        if (pAllocateInfo->commandPool) {
            VkCommandPool* pcommandPool = (VkCommandPool*)&pAllocateInfo->commandPool;
            *pcommandPool = (VkCommandPool)((VkUniqueObject*)pAllocateInfo->commandPool)->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
    if (pAllocateInfo) {
        if (pAllocateInfo->commandPool) {
            VkCommandPool* pcommandPool = (VkCommandPool*)&pAllocateInfo->commandPool;
            *pcommandPool = local_commandPool;
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
// STRUCT USES:{'commandPool': 'VkCommandPool'}
    if (commandPool) {
        VkCommandPool* pcommandPool = (VkCommandPool*)&commandPool;
        *pcommandPool = (VkCommandPool)((VkUniqueObject*)commandPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->FreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo)
{
// STRUCT USES:{'pBeginInfo': {'pInheritanceInfo': {'framebuffer': 'VkFramebuffer', 'renderPass': 'VkRenderPass'}}}
    VkFramebuffer local_framebuffer = VK_NULL_HANDLE;
    VkRenderPass local_renderPass = VK_NULL_HANDLE;
    if (pBeginInfo) {
        if (pBeginInfo->pInheritanceInfo) {
            local_renderPass = pBeginInfo->pInheritanceInfo->renderPass;
            local_framebuffer = pBeginInfo->pInheritanceInfo->framebuffer;
            if (pBeginInfo->pInheritanceInfo->framebuffer) {
                VkFramebuffer* pframebuffer = (VkFramebuffer*)&pBeginInfo->pInheritanceInfo->framebuffer;
                *pframebuffer = (VkFramebuffer)((VkUniqueObject*)pBeginInfo->pInheritanceInfo->framebuffer)->actualObject;
            }
            if (pBeginInfo->pInheritanceInfo->renderPass) {
                VkRenderPass* prenderPass = (VkRenderPass*)&pBeginInfo->pInheritanceInfo->renderPass;
                *prenderPass = (VkRenderPass)((VkUniqueObject*)pBeginInfo->pInheritanceInfo->renderPass)->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, commandBuffer)->BeginCommandBuffer(commandBuffer, pBeginInfo);
    if (pBeginInfo) {
        if (pBeginInfo->pInheritanceInfo) {
            if (pBeginInfo->pInheritanceInfo->framebuffer) {
                VkFramebuffer* pframebuffer = (VkFramebuffer*)&pBeginInfo->pInheritanceInfo->framebuffer;
                *pframebuffer = local_framebuffer;
            }
            if (pBeginInfo->pInheritanceInfo->renderPass) {
                VkRenderPass* prenderPass = (VkRenderPass*)&pBeginInfo->pInheritanceInfo->renderPass;
                *prenderPass = local_renderPass;
            }
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
// STRUCT USES:{'pipeline': 'VkPipeline'}
    if (pipeline) {
        VkPipeline* ppipeline = (VkPipeline*)&pipeline;
        *ppipeline = (VkPipeline)((VkUniqueObject*)pipeline)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets)
{
// STRUCT USES:{'layout': 'VkPipelineLayout', 'pDescriptorSets[descriptorSetCount]': 'VkDescriptorSet'}
    std::vector<VkDescriptorSet> original_pDescriptorSets = {};
    if (layout) {
        VkPipelineLayout* playout = (VkPipelineLayout*)&layout;
        *playout = (VkPipelineLayout)((VkUniqueObject*)layout)->actualObject;
    }
    if (pDescriptorSets) {
        for (uint32_t idx0=0; idx0<descriptorSetCount; ++idx0) {
            VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorSets[idx0]);
            original_pDescriptorSets.push_back(pDescriptorSets[idx0]);
            *(pDescriptorSet) = (VkDescriptorSet)((VkUniqueObject*)pDescriptorSets[idx0])->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    if (pDescriptorSets) {
        for (uint32_t idx0=0; idx0<descriptorSetCount; ++idx0) {
            VkDescriptorSet* pDescriptorSet = (VkDescriptorSet*)&(pDescriptorSets[idx0]);
            *(pDescriptorSet) = original_pDescriptorSets.front();
            original_pDescriptorSets.erase(original_pDescriptorSets.begin());
        }
    }
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType)
{
// STRUCT USES:{'buffer': 'VkBuffer'}
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets)
{
// STRUCT USES:{'pBuffers[bindingCount]': 'VkBuffer'}
    std::vector<VkBuffer> original_pBuffers = {};
    if (pBuffers) {
        for (uint32_t idx0=0; idx0<bindingCount; ++idx0) {
            VkBuffer* pBuffer = (VkBuffer*)&(pBuffers[idx0]);
            original_pBuffers.push_back(pBuffers[idx0]);
            *(pBuffer) = (VkBuffer)((VkUniqueObject*)pBuffers[idx0])->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    if (pBuffers) {
        for (uint32_t idx0=0; idx0<bindingCount; ++idx0) {
            VkBuffer* pBuffer = (VkBuffer*)&(pBuffers[idx0]);
            *(pBuffer) = original_pBuffers.front();
            original_pBuffers.erase(original_pBuffers.begin());
        }
    }
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
// STRUCT USES:{'buffer': 'VkBuffer'}
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
// STRUCT USES:{'buffer': 'VkBuffer'}
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset)
{
// STRUCT USES:{'buffer': 'VkBuffer'}
    if (buffer) {
        VkBuffer* pbuffer = (VkBuffer*)&buffer;
        *pbuffer = (VkBuffer)((VkUniqueObject*)buffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdDispatchIndirect(commandBuffer, buffer, offset);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions)
{
// STRUCT USES:{'dstBuffer': 'VkBuffer', 'srcBuffer': 'VkBuffer'}
    if (dstBuffer) {
        VkBuffer* pdstBuffer = (VkBuffer*)&dstBuffer;
        *pdstBuffer = (VkBuffer)((VkUniqueObject*)dstBuffer)->actualObject;
    }
    if (srcBuffer) {
        VkBuffer* psrcBuffer = (VkBuffer*)&srcBuffer;
        *psrcBuffer = (VkBuffer)((VkUniqueObject*)srcBuffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions)
{
// STRUCT USES:{'srcImage': 'VkImage', 'dstImage': 'VkImage'}
    if (dstImage) {
        VkImage* pdstImage = (VkImage*)&dstImage;
        *pdstImage = (VkImage)((VkUniqueObject*)dstImage)->actualObject;
    }
    if (srcImage) {
        VkImage* psrcImage = (VkImage*)&srcImage;
        *psrcImage = (VkImage)((VkUniqueObject*)srcImage)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter)
{
// STRUCT USES:{'srcImage': 'VkImage', 'dstImage': 'VkImage'}
    if (dstImage) {
        VkImage* pdstImage = (VkImage*)&dstImage;
        *pdstImage = (VkImage)((VkUniqueObject*)dstImage)->actualObject;
    }
    if (srcImage) {
        VkImage* psrcImage = (VkImage*)&srcImage;
        *psrcImage = (VkImage)((VkUniqueObject*)srcImage)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
// STRUCT USES:{'srcBuffer': 'VkBuffer', 'dstImage': 'VkImage'}
    if (dstImage) {
        VkImage* pdstImage = (VkImage*)&dstImage;
        *pdstImage = (VkImage)((VkUniqueObject*)dstImage)->actualObject;
    }
    if (srcBuffer) {
        VkBuffer* psrcBuffer = (VkBuffer*)&srcBuffer;
        *psrcBuffer = (VkBuffer)((VkUniqueObject*)srcBuffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
// STRUCT USES:{'dstBuffer': 'VkBuffer', 'srcImage': 'VkImage'}
    if (dstBuffer) {
        VkBuffer* pdstBuffer = (VkBuffer*)&dstBuffer;
        *pdstBuffer = (VkBuffer)((VkUniqueObject*)dstBuffer)->actualObject;
    }
    if (srcImage) {
        VkImage* psrcImage = (VkImage*)&srcImage;
        *psrcImage = (VkImage)((VkUniqueObject*)srcImage)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const uint32_t* pData)
{
// STRUCT USES:{'dstBuffer': 'VkBuffer'}
    if (dstBuffer) {
        VkBuffer* pdstBuffer = (VkBuffer*)&dstBuffer;
        *pdstBuffer = (VkBuffer)((VkUniqueObject*)dstBuffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data)
{
// STRUCT USES:{'dstBuffer': 'VkBuffer'}
    if (dstBuffer) {
        VkBuffer* pdstBuffer = (VkBuffer*)&dstBuffer;
        *pdstBuffer = (VkBuffer)((VkUniqueObject*)dstBuffer)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
// STRUCT USES:{'image': 'VkImage'}
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
// STRUCT USES:{'image': 'VkImage'}
    if (image) {
        VkImage* pimage = (VkImage*)&image;
        *pimage = (VkImage)((VkUniqueObject*)image)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions)
{
// STRUCT USES:{'srcImage': 'VkImage', 'dstImage': 'VkImage'}
    if (dstImage) {
        VkImage* pdstImage = (VkImage*)&dstImage;
        *pdstImage = (VkImage)((VkUniqueObject*)dstImage)->actualObject;
    }
    if (srcImage) {
        VkImage* psrcImage = (VkImage*)&srcImage;
        *psrcImage = (VkImage)((VkUniqueObject*)srcImage)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
// STRUCT USES:{'event': 'VkEvent'}
    if (event) {
        VkEvent* pevent = (VkEvent*)&event;
        *pevent = (VkEvent)((VkUniqueObject*)event)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdSetEvent(commandBuffer, event, stageMask);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
// STRUCT USES:{'event': 'VkEvent'}
    if (event) {
        VkEvent* pevent = (VkEvent*)&event;
        *pevent = (VkEvent)((VkUniqueObject*)event)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdResetEvent(commandBuffer, event, stageMask);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
// STRUCT USES:{'pEvents[eventCount]': 'VkEvent', 'pBufferMemoryBarriers[bufferMemoryBarrierCount]': {'buffer': 'VkBuffer'}, 'pImageMemoryBarriers[imageMemoryBarrierCount]': {'image': 'VkImage'}}
    std::vector<VkBuffer> original_buffer = {};
    std::vector<VkEvent> original_pEvents = {};
    std::vector<VkImage> original_image = {};
    if (pBufferMemoryBarriers) {
        for (uint32_t idx0=0; idx0<bufferMemoryBarrierCount; ++idx0) {
            if (pBufferMemoryBarriers[idx0].buffer) {
                VkBuffer* pBuffer = (VkBuffer*)&(pBufferMemoryBarriers[idx0].buffer);
                original_buffer.push_back(pBufferMemoryBarriers[idx0].buffer);
                *(pBuffer) = (VkBuffer)((VkUniqueObject*)pBufferMemoryBarriers[idx0].buffer)->actualObject;
            }
        }
    }
    if (pEvents) {
        for (uint32_t idx1=0; idx1<eventCount; ++idx1) {
            VkEvent* pEvent = (VkEvent*)&(pEvents[idx1]);
            original_pEvents.push_back(pEvents[idx1]);
            *(pEvent) = (VkEvent)((VkUniqueObject*)pEvents[idx1])->actualObject;
        }
    }
    if (pImageMemoryBarriers) {
        for (uint32_t idx2=0; idx2<imageMemoryBarrierCount; ++idx2) {
            if (pImageMemoryBarriers[idx2].image) {
                VkImage* pImage = (VkImage*)&(pImageMemoryBarriers[idx2].image);
                original_image.push_back(pImageMemoryBarriers[idx2].image);
                *(pImage) = (VkImage)((VkUniqueObject*)pImageMemoryBarriers[idx2].image)->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    if (pBufferMemoryBarriers) {
        for (uint32_t idx0=0; idx0<bufferMemoryBarrierCount; ++idx0) {
            if (pBufferMemoryBarriers[idx0].buffer) {
                VkBuffer* pBuffer = (VkBuffer*)&(pBufferMemoryBarriers[idx0].buffer);
                *(pBuffer) = original_buffer.front();
                original_buffer.erase(original_buffer.begin());
            }
        }
    }
    if (pEvents) {
        for (uint32_t idx1=0; idx1<eventCount; ++idx1) {
            VkEvent* pEvent = (VkEvent*)&(pEvents[idx1]);
            *(pEvent) = original_pEvents.front();
            original_pEvents.erase(original_pEvents.begin());
        }
    }
    if (pImageMemoryBarriers) {
        for (uint32_t idx2=0; idx2<imageMemoryBarrierCount; ++idx2) {
            if (pImageMemoryBarriers[idx2].image) {
                VkImage* pImage = (VkImage*)&(pImageMemoryBarriers[idx2].image);
                *(pImage) = original_image.front();
                original_image.erase(original_image.begin());
            }
        }
    }
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
// STRUCT USES:{'pBufferMemoryBarriers[bufferMemoryBarrierCount]': {'buffer': 'VkBuffer'}, 'pImageMemoryBarriers[imageMemoryBarrierCount]': {'image': 'VkImage'}}
    std::vector<VkBuffer> original_buffer = {};
    std::vector<VkImage> original_image = {};
    if (pBufferMemoryBarriers) {
        for (uint32_t idx0=0; idx0<bufferMemoryBarrierCount; ++idx0) {
            if (pBufferMemoryBarriers[idx0].buffer) {
                VkBuffer* pBuffer = (VkBuffer*)&(pBufferMemoryBarriers[idx0].buffer);
                original_buffer.push_back(pBufferMemoryBarriers[idx0].buffer);
                *(pBuffer) = (VkBuffer)((VkUniqueObject*)pBufferMemoryBarriers[idx0].buffer)->actualObject;
            }
        }
    }
    if (pImageMemoryBarriers) {
        for (uint32_t idx1=0; idx1<imageMemoryBarrierCount; ++idx1) {
            if (pImageMemoryBarriers[idx1].image) {
                VkImage* pImage = (VkImage*)&(pImageMemoryBarriers[idx1].image);
                original_image.push_back(pImageMemoryBarriers[idx1].image);
                *(pImage) = (VkImage)((VkUniqueObject*)pImageMemoryBarriers[idx1].image)->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    if (pBufferMemoryBarriers) {
        for (uint32_t idx0=0; idx0<bufferMemoryBarrierCount; ++idx0) {
            if (pBufferMemoryBarriers[idx0].buffer) {
                VkBuffer* pBuffer = (VkBuffer*)&(pBufferMemoryBarriers[idx0].buffer);
                *(pBuffer) = original_buffer.front();
                original_buffer.erase(original_buffer.begin());
            }
        }
    }
    if (pImageMemoryBarriers) {
        for (uint32_t idx1=0; idx1<imageMemoryBarrierCount; ++idx1) {
            if (pImageMemoryBarriers[idx1].image) {
                VkImage* pImage = (VkImage*)&(pImageMemoryBarriers[idx1].image);
                *(pImage) = original_image.front();
                original_image.erase(original_image.begin());
            }
        }
    }
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags)
{
// STRUCT USES:{'queryPool': 'VkQueryPool'}
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBeginQuery(commandBuffer, queryPool, query, flags);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query)
{
// STRUCT USES:{'queryPool': 'VkQueryPool'}
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdEndQuery(commandBuffer, queryPool, query);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
// STRUCT USES:{'queryPool': 'VkQueryPool'}
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query)
{
// STRUCT USES:{'queryPool': 'VkQueryPool'}
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags)
{
// STRUCT USES:{'queryPool': 'VkQueryPool', 'dstBuffer': 'VkBuffer'}
    if (dstBuffer) {
        VkBuffer* pdstBuffer = (VkBuffer*)&dstBuffer;
        *pdstBuffer = (VkBuffer)((VkUniqueObject*)dstBuffer)->actualObject;
    }
    if (queryPool) {
        VkQueryPool* pqueryPool = (VkQueryPool*)&queryPool;
        *pqueryPool = (VkQueryPool)((VkUniqueObject*)queryPool)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues)
{
// STRUCT USES:{'layout': 'VkPipelineLayout'}
    if (layout) {
        VkPipelineLayout* playout = (VkPipelineLayout*)&layout;
        *playout = (VkPipelineLayout)((VkUniqueObject*)layout)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents)
{
// STRUCT USES:{'pRenderPassBegin': {'framebuffer': 'VkFramebuffer', 'renderPass': 'VkRenderPass'}}
    VkFramebuffer local_framebuffer = VK_NULL_HANDLE;
    VkRenderPass local_renderPass = VK_NULL_HANDLE;
    if (pRenderPassBegin) {
        local_renderPass = pRenderPassBegin->renderPass;
        local_framebuffer = pRenderPassBegin->framebuffer;
        if (pRenderPassBegin->framebuffer) {
            VkFramebuffer* pframebuffer = (VkFramebuffer*)&pRenderPassBegin->framebuffer;
            *pframebuffer = (VkFramebuffer)((VkUniqueObject*)pRenderPassBegin->framebuffer)->actualObject;
        }
        if (pRenderPassBegin->renderPass) {
            VkRenderPass* prenderPass = (VkRenderPass*)&pRenderPassBegin->renderPass;
            *prenderPass = (VkRenderPass)((VkUniqueObject*)pRenderPassBegin->renderPass)->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
    if (pRenderPassBegin) {
        if (pRenderPassBegin->framebuffer) {
            VkFramebuffer* pframebuffer = (VkFramebuffer*)&pRenderPassBegin->framebuffer;
            *pframebuffer = local_framebuffer;
        }
        if (pRenderPassBegin->renderPass) {
            VkRenderPass* prenderPass = (VkRenderPass*)&pRenderPassBegin->renderPass;
            *prenderPass = local_renderPass;
        }
    }
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'surface': 'VkSurfaceKHR'}
    VkSurfaceKHR local_surface = surface;
    if (surface) {
        VkSurfaceKHR* psurface = (VkSurfaceKHR*)&surface;
        *psurface = (VkSurfaceKHR)((VkUniqueObject*)surface)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_instance_table_map, instance)->DestroySurfaceKHR(instance, surface, pAllocator);
    delete (VkUniqueObject*)local_surface;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported)
{
// STRUCT USES:{'surface': 'VkSurfaceKHR'}
    if (surface) {
        VkSurfaceKHR* psurface = (VkSurfaceKHR*)&surface;
        *psurface = (VkSurfaceKHR)((VkUniqueObject*)surface)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities)
{
// STRUCT USES:{'surface': 'VkSurfaceKHR'}
    if (surface) {
        VkSurfaceKHR* psurface = (VkSurfaceKHR*)&surface;
        *psurface = (VkSurfaceKHR)((VkUniqueObject*)surface)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats)
{
// STRUCT USES:{'surface': 'VkSurfaceKHR'}
    if (surface) {
        VkSurfaceKHR* psurface = (VkSurfaceKHR*)&surface;
        *psurface = (VkSurfaceKHR)((VkUniqueObject*)surface)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
// STRUCT USES:{'surface': 'VkSurfaceKHR'}
    if (surface) {
        VkSurfaceKHR* psurface = (VkSurfaceKHR*)&surface;
        *psurface = (VkSurfaceKHR)((VkUniqueObject*)surface)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
// STRUCT USES:{'pCreateInfo': {'oldSwapchain': 'VkSwapchainKHR', 'surface': 'VkSurfaceKHR'}}
    VkSwapchainKHR local_oldSwapchain = VK_NULL_HANDLE;
    VkSurfaceKHR local_surface = VK_NULL_HANDLE;
    if (pCreateInfo) {
        local_surface = pCreateInfo->surface;
        local_oldSwapchain = pCreateInfo->oldSwapchain;
        if (pCreateInfo->oldSwapchain) {
            VkSwapchainKHR* poldSwapchain = (VkSwapchainKHR*)&pCreateInfo->oldSwapchain;
            *poldSwapchain = (VkSwapchainKHR)((VkUniqueObject*)pCreateInfo->oldSwapchain)->actualObject;
        }
        if (pCreateInfo->surface) {
            VkSurfaceKHR* psurface = (VkSurfaceKHR*)&pCreateInfo->surface;
            *psurface = (VkSurfaceKHR)((VkUniqueObject*)pCreateInfo->surface)->actualObject;
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
    if (pCreateInfo) {
        if (pCreateInfo->oldSwapchain) {
            VkSwapchainKHR* poldSwapchain = (VkSwapchainKHR*)&pCreateInfo->oldSwapchain;
            *poldSwapchain = local_oldSwapchain;
        }
        if (pCreateInfo->surface) {
            VkSurfaceKHR* psurface = (VkSurfaceKHR*)&pCreateInfo->surface;
            *psurface = local_surface;
        }
    }
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueSwapchainKHR = new VkUniqueObject();
        uniqueSwapchainKHR->actualObject = (uint64_t)*pSwapchain;
        *pSwapchain = (VkSwapchainKHR)uniqueSwapchainKHR;
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
// STRUCT USES:{'swapchain': 'VkSwapchainKHR'}
    VkSwapchainKHR local_swapchain = swapchain;
    if (swapchain) {
        VkSwapchainKHR* pswapchain = (VkSwapchainKHR*)&swapchain;
        *pswapchain = (VkSwapchainKHR)((VkUniqueObject*)swapchain)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    get_dispatch_table(unique_objects_device_table_map, device)->DestroySwapchainKHR(device, swapchain, pAllocator);
    delete (VkUniqueObject*)local_swapchain;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
    return explicit_GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
// STRUCT USES:{'swapchain': 'VkSwapchainKHR', 'semaphore': 'VkSemaphore', 'fence': 'VkFence'}
    if (fence) {
        VkFence* pfence = (VkFence*)&fence;
        *pfence = (VkFence)((VkUniqueObject*)fence)->actualObject;
    }
    if (semaphore) {
        VkSemaphore* psemaphore = (VkSemaphore*)&semaphore;
        *psemaphore = (VkSemaphore)((VkUniqueObject*)semaphore)->actualObject;
    }
    if (swapchain) {
        VkSwapchainKHR* pswapchain = (VkSwapchainKHR*)&swapchain;
        *pswapchain = (VkSwapchainKHR)((VkUniqueObject*)swapchain)->actualObject;
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
// STRUCT USES:{'pPresentInfo': {'pWaitSemaphores[waitSemaphoreCount]': 'VkSemaphore', 'pSwapchains[swapchainCount]': 'VkSwapchainKHR'}}
    std::vector<VkSwapchainKHR> original_pSwapchains = {};
    std::vector<VkSemaphore> original_pWaitSemaphores = {};
    if (pPresentInfo) {
        if (pPresentInfo->pSwapchains) {
            for (uint32_t idx0=0; idx0<pPresentInfo->swapchainCount; ++idx0) {
                VkSwapchainKHR* pSwapchainKHR = (VkSwapchainKHR*)&(pPresentInfo->pSwapchains[idx0]);
                original_pSwapchains.push_back(pPresentInfo->pSwapchains[idx0]);
                *(pSwapchainKHR) = (VkSwapchainKHR)((VkUniqueObject*)pPresentInfo->pSwapchains[idx0])->actualObject;
            }
        }
        if (pPresentInfo->pWaitSemaphores) {
            for (uint32_t idx1=0; idx1<pPresentInfo->waitSemaphoreCount; ++idx1) {
                VkSemaphore* pSemaphore = (VkSemaphore*)&(pPresentInfo->pWaitSemaphores[idx1]);
                original_pWaitSemaphores.push_back(pPresentInfo->pWaitSemaphores[idx1]);
                *(pSemaphore) = (VkSemaphore)((VkUniqueObject*)pPresentInfo->pWaitSemaphores[idx1])->actualObject;
            }
        }
    }
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_device_table_map, queue)->QueuePresentKHR(queue, pPresentInfo);
    if (pPresentInfo) {
        if (pPresentInfo->pSwapchains) {
            for (uint32_t idx0=0; idx0<pPresentInfo->swapchainCount; ++idx0) {
                VkSwapchainKHR* pSwapchainKHR = (VkSwapchainKHR*)&(pPresentInfo->pSwapchains[idx0]);
                *(pSwapchainKHR) = original_pSwapchains.front();
                original_pSwapchains.erase(original_pSwapchains.begin());
            }
        }
        if (pPresentInfo->pWaitSemaphores) {
            for (uint32_t idx1=0; idx1<pPresentInfo->waitSemaphoreCount; ++idx1) {
                VkSemaphore* pSemaphore = (VkSemaphore*)&(pPresentInfo->pWaitSemaphores[idx1]);
                *(pSemaphore) = original_pWaitSemaphores.front();
                original_pWaitSemaphores.erase(original_pWaitSemaphores.begin());
            }
        }
    }
    return result;
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1640
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, instance)->CreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    if (VK_SUCCESS == result) {
// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #1615
        VkUniqueObject* uniqueSurfaceKHR = new VkUniqueObject();
        uniqueSurfaceKHR->actualObject = (uint64_t)*pSurface;
        *pSurface = (VkSurfaceKHR)uniqueSurfaceKHR;
    }
    return result;
}

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #461
static inline PFN_vkVoidFunction layer_intercept_proc(const char *name)
{
    if (!name || name[0] != 'v' || name[1] != 'k')
        return NULL;

    name += 2;
    if (!strcmp(name, "CreateInstance"))
        return (PFN_vkVoidFunction) vkCreateInstance;
    if (!strcmp(name, "CreateDevice"))
        return (PFN_vkVoidFunction) vkCreateDevice;
    if (!strcmp(name, "EnumerateInstanceExtensionProperties"))
        return (PFN_vkVoidFunction) vkEnumerateInstanceExtensionProperties;
    if (!strcmp(name, "EnumerateInstanceLayerProperties"))
        return (PFN_vkVoidFunction) vkEnumerateInstanceLayerProperties;
    if (!strcmp(name, "EnumerateDeviceLayerProperties"))
        return (PFN_vkVoidFunction) vkEnumerateDeviceLayerProperties;
    if (!strcmp(name, "QueueSubmit"))
        return (PFN_vkVoidFunction) vkQueueSubmit;
    if (!strcmp(name, "AllocateMemory"))
        return (PFN_vkVoidFunction) vkAllocateMemory;
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
    if (!strcmp(name, "GetDeviceMemoryCommitment"))
        return (PFN_vkVoidFunction) vkGetDeviceMemoryCommitment;
    if (!strcmp(name, "BindBufferMemory"))
        return (PFN_vkVoidFunction) vkBindBufferMemory;
    if (!strcmp(name, "BindImageMemory"))
        return (PFN_vkVoidFunction) vkBindImageMemory;
    if (!strcmp(name, "GetBufferMemoryRequirements"))
        return (PFN_vkVoidFunction) vkGetBufferMemoryRequirements;
    if (!strcmp(name, "GetImageMemoryRequirements"))
        return (PFN_vkVoidFunction) vkGetImageMemoryRequirements;
    if (!strcmp(name, "GetImageSparseMemoryRequirements"))
        return (PFN_vkVoidFunction) vkGetImageSparseMemoryRequirements;
    if (!strcmp(name, "QueueBindSparse"))
        return (PFN_vkVoidFunction) vkQueueBindSparse;
    if (!strcmp(name, "CreateFence"))
        return (PFN_vkVoidFunction) vkCreateFence;
    if (!strcmp(name, "DestroyFence"))
        return (PFN_vkVoidFunction) vkDestroyFence;
    if (!strcmp(name, "ResetFences"))
        return (PFN_vkVoidFunction) vkResetFences;
    if (!strcmp(name, "GetFenceStatus"))
        return (PFN_vkVoidFunction) vkGetFenceStatus;
    if (!strcmp(name, "WaitForFences"))
        return (PFN_vkVoidFunction) vkWaitForFences;
    if (!strcmp(name, "CreateSemaphore"))
        return (PFN_vkVoidFunction) vkCreateSemaphore;
    if (!strcmp(name, "DestroySemaphore"))
        return (PFN_vkVoidFunction) vkDestroySemaphore;
    if (!strcmp(name, "CreateEvent"))
        return (PFN_vkVoidFunction) vkCreateEvent;
    if (!strcmp(name, "DestroyEvent"))
        return (PFN_vkVoidFunction) vkDestroyEvent;
    if (!strcmp(name, "GetEventStatus"))
        return (PFN_vkVoidFunction) vkGetEventStatus;
    if (!strcmp(name, "SetEvent"))
        return (PFN_vkVoidFunction) vkSetEvent;
    if (!strcmp(name, "ResetEvent"))
        return (PFN_vkVoidFunction) vkResetEvent;
    if (!strcmp(name, "CreateQueryPool"))
        return (PFN_vkVoidFunction) vkCreateQueryPool;
    if (!strcmp(name, "DestroyQueryPool"))
        return (PFN_vkVoidFunction) vkDestroyQueryPool;
    if (!strcmp(name, "GetQueryPoolResults"))
        return (PFN_vkVoidFunction) vkGetQueryPoolResults;
    if (!strcmp(name, "CreateBuffer"))
        return (PFN_vkVoidFunction) vkCreateBuffer;
    if (!strcmp(name, "DestroyBuffer"))
        return (PFN_vkVoidFunction) vkDestroyBuffer;
    if (!strcmp(name, "CreateBufferView"))
        return (PFN_vkVoidFunction) vkCreateBufferView;
    if (!strcmp(name, "DestroyBufferView"))
        return (PFN_vkVoidFunction) vkDestroyBufferView;
    if (!strcmp(name, "CreateImage"))
        return (PFN_vkVoidFunction) vkCreateImage;
    if (!strcmp(name, "DestroyImage"))
        return (PFN_vkVoidFunction) vkDestroyImage;
    if (!strcmp(name, "GetImageSubresourceLayout"))
        return (PFN_vkVoidFunction) vkGetImageSubresourceLayout;
    if (!strcmp(name, "CreateImageView"))
        return (PFN_vkVoidFunction) vkCreateImageView;
    if (!strcmp(name, "DestroyImageView"))
        return (PFN_vkVoidFunction) vkDestroyImageView;
    if (!strcmp(name, "CreateShaderModule"))
        return (PFN_vkVoidFunction) vkCreateShaderModule;
    if (!strcmp(name, "DestroyShaderModule"))
        return (PFN_vkVoidFunction) vkDestroyShaderModule;
    if (!strcmp(name, "CreatePipelineCache"))
        return (PFN_vkVoidFunction) vkCreatePipelineCache;
    if (!strcmp(name, "DestroyPipelineCache"))
        return (PFN_vkVoidFunction) vkDestroyPipelineCache;
    if (!strcmp(name, "GetPipelineCacheData"))
        return (PFN_vkVoidFunction) vkGetPipelineCacheData;
    if (!strcmp(name, "MergePipelineCaches"))
        return (PFN_vkVoidFunction) vkMergePipelineCaches;
    if (!strcmp(name, "CreateGraphicsPipelines"))
        return (PFN_vkVoidFunction) vkCreateGraphicsPipelines;
    if (!strcmp(name, "CreateComputePipelines"))
        return (PFN_vkVoidFunction) vkCreateComputePipelines;
    if (!strcmp(name, "DestroyPipeline"))
        return (PFN_vkVoidFunction) vkDestroyPipeline;
    if (!strcmp(name, "CreatePipelineLayout"))
        return (PFN_vkVoidFunction) vkCreatePipelineLayout;
    if (!strcmp(name, "DestroyPipelineLayout"))
        return (PFN_vkVoidFunction) vkDestroyPipelineLayout;
    if (!strcmp(name, "CreateSampler"))
        return (PFN_vkVoidFunction) vkCreateSampler;
    if (!strcmp(name, "DestroySampler"))
        return (PFN_vkVoidFunction) vkDestroySampler;
    if (!strcmp(name, "CreateDescriptorSetLayout"))
        return (PFN_vkVoidFunction) vkCreateDescriptorSetLayout;
    if (!strcmp(name, "DestroyDescriptorSetLayout"))
        return (PFN_vkVoidFunction) vkDestroyDescriptorSetLayout;
    if (!strcmp(name, "CreateDescriptorPool"))
        return (PFN_vkVoidFunction) vkCreateDescriptorPool;
    if (!strcmp(name, "DestroyDescriptorPool"))
        return (PFN_vkVoidFunction) vkDestroyDescriptorPool;
    if (!strcmp(name, "ResetDescriptorPool"))
        return (PFN_vkVoidFunction) vkResetDescriptorPool;
    if (!strcmp(name, "AllocateDescriptorSets"))
        return (PFN_vkVoidFunction) vkAllocateDescriptorSets;
    if (!strcmp(name, "FreeDescriptorSets"))
        return (PFN_vkVoidFunction) vkFreeDescriptorSets;
    if (!strcmp(name, "UpdateDescriptorSets"))
        return (PFN_vkVoidFunction) vkUpdateDescriptorSets;
    if (!strcmp(name, "CreateFramebuffer"))
        return (PFN_vkVoidFunction) vkCreateFramebuffer;
    if (!strcmp(name, "DestroyFramebuffer"))
        return (PFN_vkVoidFunction) vkDestroyFramebuffer;
    if (!strcmp(name, "CreateRenderPass"))
        return (PFN_vkVoidFunction) vkCreateRenderPass;
    if (!strcmp(name, "DestroyRenderPass"))
        return (PFN_vkVoidFunction) vkDestroyRenderPass;
    if (!strcmp(name, "GetRenderAreaGranularity"))
        return (PFN_vkVoidFunction) vkGetRenderAreaGranularity;
    if (!strcmp(name, "CreateCommandPool"))
        return (PFN_vkVoidFunction) vkCreateCommandPool;
    if (!strcmp(name, "DestroyCommandPool"))
        return (PFN_vkVoidFunction) vkDestroyCommandPool;
    if (!strcmp(name, "ResetCommandPool"))
        return (PFN_vkVoidFunction) vkResetCommandPool;
    if (!strcmp(name, "AllocateCommandBuffers"))
        return (PFN_vkVoidFunction) vkAllocateCommandBuffers;
    if (!strcmp(name, "FreeCommandBuffers"))
        return (PFN_vkVoidFunction) vkFreeCommandBuffers;
    if (!strcmp(name, "BeginCommandBuffer"))
        return (PFN_vkVoidFunction) vkBeginCommandBuffer;
    if (!strcmp(name, "CmdBindPipeline"))
        return (PFN_vkVoidFunction) vkCmdBindPipeline;
    if (!strcmp(name, "CmdBindDescriptorSets"))
        return (PFN_vkVoidFunction) vkCmdBindDescriptorSets;
    if (!strcmp(name, "CmdBindIndexBuffer"))
        return (PFN_vkVoidFunction) vkCmdBindIndexBuffer;
    if (!strcmp(name, "CmdBindVertexBuffers"))
        return (PFN_vkVoidFunction) vkCmdBindVertexBuffers;
    if (!strcmp(name, "CmdDrawIndirect"))
        return (PFN_vkVoidFunction) vkCmdDrawIndirect;
    if (!strcmp(name, "CmdDrawIndexedIndirect"))
        return (PFN_vkVoidFunction) vkCmdDrawIndexedIndirect;
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

    return NULL;
}
static inline PFN_vkVoidFunction layer_intercept_instance_proc(const char *name)
{
    if (!name || name[0] != 'v' || name[1] != 'k')
        return NULL;

    name += 2;
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

// CODEGEN : file C:/releasebuild/LoaderAndValidationLayers/vk-layer-generate.py line #526
    layer_data *my_device_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
    if (my_device_data->wsi_enabled) {
        if (!strcmp("vkCreateSwapchainKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkCreateSwapchainKHR);
        if (!strcmp("vkDestroySwapchainKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkDestroySwapchainKHR);
        if (!strcmp("vkGetSwapchainImagesKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetSwapchainImagesKHR);
        if (!strcmp("vkAcquireNextImageKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkAcquireNextImageKHR);
        if (!strcmp("vkQueuePresentKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkQueuePresentKHR);
    }


    if (get_dispatch_table(unique_objects_device_table_map, device)->GetDeviceProcAddr == NULL)
        return NULL;
    return get_dispatch_table(unique_objects_device_table_map, device)->GetDeviceProcAddr(device, funcName);
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

    VkLayerInstanceDispatchTable* pTable = get_dispatch_table(unique_objects_instance_table_map, instance);
    if (instanceExtMap.size() != 0 && instanceExtMap[pTable].wsi_enabled)
    {
        if (!strcmp("vkGetPhysicalDeviceSurfaceSupportKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetPhysicalDeviceSurfaceSupportKHR);
        if (!strcmp("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
        if (!strcmp("vkGetPhysicalDeviceSurfaceFormatsKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetPhysicalDeviceSurfaceFormatsKHR);
        if (!strcmp("vkGetPhysicalDeviceSurfacePresentModesKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetPhysicalDeviceSurfacePresentModesKHR);
#ifdef VK_USE_PLATFORM_WIN32_KHR
        if (!strcmp("vkCreateWin32SurfaceKHR", funcName))
            return reinterpret_cast<PFN_vkVoidFunction>(vkCreateWin32SurfaceKHR);
#endif  // VK_USE_PLATFORM_WIN32_KHR
    }

    if (get_dispatch_table(unique_objects_instance_table_map, instance)->GetInstanceProcAddr == NULL) {
        return NULL;
    }
    return get_dispatch_table(unique_objects_instance_table_map, instance)->GetInstanceProcAddr(instance, funcName);
}

