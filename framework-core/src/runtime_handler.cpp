#include <fe/runtime_handler.hpp>

fe::runtime::FrameworkRuntimeHandler::FrameworkRuntimeHandler() : scene_manager_{ &resource_manager_ } {}

fe::runtime::FrameworkRuntimeHandler& fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler() {
    static FrameworkRuntimeHandler handler;
    return handler;
}

fe::ResourceManager *const fe::runtime::FrameworkRuntimeHandler::GetResourceManager() {
    return &resource_manager_;
}

fe::runtime::RenderHandler *const fe::runtime::FrameworkRuntimeHandler::GetRenderHandler() {
    return &render_handler_;
}

fe::SceneManager *const fe::runtime::FrameworkRuntimeHandler::GetSceneManager() {
    return &scene_manager_;
}

fe::Window *const fe::runtime::FrameworkRuntimeHandler::GetWindow() {
    return &window_;
}

fe::InputHandler *const fe::runtime::FrameworkRuntimeHandler::GetInput() {
    return &(window_.input_handler);
}

void fe::runtime::FrameworkRuntimeHandler::UpdateTime(double (*time_fn)()) {
    static double old_time_since_start_ = 0.0;

    double time_since_start = time_fn();
    delta_time = time_since_start - old_time_since_start_;
    
    old_time_since_start_ = time_since_start;
} 
