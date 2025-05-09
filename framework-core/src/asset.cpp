#include <fe/objects/assets/asset.hpp>

fe::Asset::Asset() : Object() {
    resource_manager->MarkObjectTentative(this);
}

fe::Asset::Asset(std::string p_name) : Object(p_name) {
    resource_manager->MarkObjectTentative(this);
}
