#include <fe/objects/object.hpp>

fe::Object::Object() = default;

fe::Object::Object(std::string p_name) : name{ p_name } {}

fe::Object::~Object() {}

void fe::Object::UnbindFromParent() {
    resource_manager->TakeOwnership(this);
}

bool fe::Object::remove_child_and_shift_(Object* obj) {
    if (children.empty()) return false;

    for (decltype(children.size()) i = 0; i < children.size() - 1; ++i) {
        if (children.at(i) == obj) std::swap(children.at(i), children.at(i+1));
    }

    if (children.back() != obj) return false;

    children.pop_back();
    return true;
}
