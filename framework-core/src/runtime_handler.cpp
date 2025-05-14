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

void fe::runtime::FrameworkRuntimeHandler::UpdateTime(double (*time_fn)()) {
    static double old_time_since_start_ = 0.0;

    double time_since_start = time_fn();
    delta_time = time_since_start - old_time_since_start_;
    
    old_time_since_start_ = time_since_start;
} 
