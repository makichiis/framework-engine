#include <fe/objects/assets/asset.hpp>

void fe::Asset::OnInit() {
    resource_manager->MarkObjectTentative(this);
}
