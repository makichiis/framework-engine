#include <fe/objects/object.hpp>
#include <fe/runtime_handler.hpp>

#include <iostream>

fe::Object::Object() = default;

fe::Object::Object(std::string p_name) : name{ p_name } {}

fe::Object::~Object() {}

void fe::Object::OnInit() {}

void fe::Object::OnUpdate() {}

void fe::Object::OnTest() {
    std::cout << "Object::OnTest()\n";
}

void fe::Object::OnPreDraw() {
    
}

void fe::Object::UnbindFromParent() {
    resource_manager->MarkObjectTentative(this);
}

bool fe::Object::remove_child_(Object* obj) {
    auto obj_it = children.find(obj);
    if (obj_it == children.end()) return false;

    children.erase(obj_it);
    return true;
}

fe::runtime::FrameworkRuntimeHandler& fe::Object::GetFramework() {
    return runtime::FrameworkRuntimeHandler::GetRuntimeHandler();
}
