#include <fe/objects/components/renderers/default_renderer.hpp>
#include <fe/objects/assets/materials/default_material.hpp>

void fe::DefaultRenderer::OnInit() {
    material = resource_manager->CreateObject<DefaultMaterial>();
}
