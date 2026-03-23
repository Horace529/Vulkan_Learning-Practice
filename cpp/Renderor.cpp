#include "Renderor.h"
#include <stdexcept>
#include "log.h"
#include <chrono>

void Renderor::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Renderor::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Renderor::initVulkan() {
    createInstance();
}

void Renderor::mainLoop() {
    using clock = std::chrono::steady_clock;
    auto lastLog = clock::now();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 渲染 / 更新逻辑
        // drawFrame(); // 如果你有帧渲染函数，放在这里

        // 示例：按需单次调用日志接口（不要把 spdlog 直接写进渲染器）
         Log::Debug("Running main loop. WIDTH={} HEIGHT={}", WIDTH, HEIGHT);

        // 如果需要周期性日志，请在外部模块安排调用，而不是在此处硬编码。
    }
}

void Renderor::cleanup() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderor::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}