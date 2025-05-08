#include <fe/runtime_handler.hpp>

fe::runtime::FrameworkRuntimeHandler::FrameworkRuntimeHandler() : scene_manager{ &resource_manager } {}

fe::runtime::FrameworkRuntimeHandler& fe::runtime::FrameworkRuntimeHandler::GetRuntimeHandler() {
    static FrameworkRuntimeHandler handler;
    return handler;
}