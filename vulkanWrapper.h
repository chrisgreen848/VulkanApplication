#pragma once
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <fstream>
#include "vertex.h"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanWrapper
{
public:
	VulkanWrapper(uint32_t width, uint32_t height);
	~VulkanWrapper();

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() 
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails 
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};


	void initWindow();
	void initialiseVulkan();
	void mainloop();
	void cleanUp();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createImageViews();
	void createGraphicsPipeline();
	void createRenderPass();
	void createFrameBuffers();
	void createCommandPool();
	void createVertexBuffers();
	void createIndexBuffer();
	void createDescriptorSetLayout();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void createCommandBuffers();
	void createSyncObjects();
	void recreateSwapchain();
	void cleanUpSwapchain();

	void drawFrame();


	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	void createInstance();
	void selectPhysicalDevice();
	void handleExtensions();
	bool checkValidationLayerSupport();
	void setupDebugMessager();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	VulkanWrapper::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	std::vector<const char*> getRequiredExtensions();
	const std::vector<const char*> m_deviceExtensions = {	VK_KHR_SWAPCHAIN_EXTENSION_NAME	};

	void setFrameBufferResized(bool resized) { m_framebufferResized = resized; }

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	void createTexureImage();

	//const std::vector<Vertex> m_vertices = {
	//{{0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
	//{{1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	//{{-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
	//};

	const std::vector<Vertex> m_vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> m_indices = {
	0, 1, 2, 2, 3, 0
	};

private:
	GLFWwindow* m_window;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

	uint32_t m_windowWidth;
	uint32_t m_windowHeight;

	VkInstance m_vkInstance;
	VkPhysicalDevice m_physicalDevice;
	VkDevice m_logicalDevice;

	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;

	VkSurfaceKHR m_surface;

	VkSwapchainKHR m_swapchain;
	std::vector<VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
	std::vector<VkImageView> m_swapChainImageViews;

	VkPipeline m_graphicsPipeline;
	VkRenderPass m_renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout m_pipelineLayout;

	VkCommandPool m_commandPool;
	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	VkBuffer m_indexBuffer;
	VkDeviceMemory m_indexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	std::vector<VkCommandBuffer> m_commandBuffers;

	std::vector<VkFramebuffer> m_swapChainFramebuffers;

	std::vector<VkSemaphore> m_imageAvailableSemaphores;
	std::vector<VkSemaphore> m_renderFinishedSemaphores;
	std::vector<VkFence> m_inFlightFences;

	const std::vector<const char*> m_validationLayers = {
	"VK_LAYER_KHRONOS_validation" };

	VkDebugUtilsMessengerEXT m_debugMessenger;

	uint32_t m_currentFrame;
	bool m_framebufferResized = false;

	static const int m_maxFramesInFlight = 2;
};