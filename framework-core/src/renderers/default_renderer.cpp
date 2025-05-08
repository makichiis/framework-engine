#include <fe/objects/components/renderers/default_renderer.hpp>
#include <fe/objects/assets/materials/default_material.hpp>

fe::DefaultRenderer::DefaultRenderer() : Renderer("Default Renderer") {
    material = resource_manager->CreateObject<DefaultMaterial>();
}
