#include <fe/runtime_handler.hpp>

fe::runtime::FrameworkRuntimeHandler::FrameworkRuntimeHandler() : scene_manager{ &resource_manager } {}

fe::runtime::FrameworkRuntimeHandler& fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler() {
    static FrameworkRuntimeHandler handler;
    return handler;
}

fe::ResourceManager *const fe::runtime::FrameworkRuntimeHandler::GetResourceManager() {
    return &resource_manager;
}

fe::runtime::RenderHandler *const fe::runtime::FrameworkRuntimeHandler::GetRenderHandler() {
    return &render_handler;
}

fe::SceneManager *const fe::runtime::FrameworkRuntimeHandler::GetSceneManager() {
    return &scene_manager;
}
