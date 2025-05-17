#include <fe/objects/assets/materials/default_material.hpp>
#include <fe/objects/assets/shaders/basic_color_shader.hpp>

void fe::DefaultMaterial::OnInit() {
    shader = resource_manager->CreateObject<BasicColorShader>();
    color = { 1.0f, 0.5f, 0.2f, 1.0f };

    // shader->SetVec4("color", { color.r, color.g, color.b, color.a });
}
