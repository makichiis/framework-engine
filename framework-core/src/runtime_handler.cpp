#include <fe/runtime_handler.hpp>

#ifdef DEBUG
#include <cassert>
#endif 

fe::runtime::FrameworkRuntimeHandler::FrameworkRuntimeHandler() {
    #ifdef DEBUG
    static int calls = 0;
    ++calls;
    assert(calls == 1);
    #endif 

    resource_manager_ = new ResourceManager;
    render_handler_ = new RenderHandler;
    scene_manager_ = new SceneManager(resource_manager_);

    #ifdef DEBUG
    std::cout << "Runtime initialized.\n";
    #endif 
}

fe::runtime::FrameworkRuntimeHandler::~FrameworkRuntimeHandler() {
    delete scene_manager_;
    delete render_handler_;
    delete resource_manager_;
}

fe::runtime::FrameworkRuntimeHandler& fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler() {
    static FrameworkRuntimeHandler handler;
    return handler;
}

fe::ResourceManager *const fe::runtime::FrameworkRuntimeHandler::GetResourceManager() {
    return resource_manager_;
}

fe::runtime::RenderHandler *const fe::runtime::FrameworkRuntimeHandler::GetRenderHandler() {
    return render_handler_;
}

fe::SceneManager *const fe::runtime::FrameworkRuntimeHandler::GetSceneManager() {
    return scene_manager_;
}

fe::Window *const fe::runtime::FrameworkRuntimeHandler::GetWindow() {
    return window_;
}

void fe::runtime::FrameworkRuntimeHandler::SetWindow(Window* window) {
    assert(window);

    window_ = window;
}

fe::InputHandler *const fe::runtime::FrameworkRuntimeHandler::GetInput() {
    return window_->GetInput();
}

void fe::runtime::FrameworkRuntimeHandler::UpdateTime(double (*time_fn)()) {
    static double old_time_since_start_ = 0.0;

    double time_since_start = time_fn();
    delta_time = time_since_start - old_time_since_start_;
    
    old_time_since_start_ = time_since_start;

    time_since_start_ = time_fn();
} 

double fe::runtime::FrameworkRuntimeHandler::GetTime() {
    return time_since_start_;
}
