#include <iostream>

#include <fe/render_handler.hpp>
#include <fe/objects/components/renderer.hpp>
#include <fe/objects/components/meshes/mesh.hpp>
#include <fe/objects/assets/materials/material.hpp>

#include <glad/gl.h>

fe::Renderer* get_renderer(fe::Object* obj) {
    for (auto&& [_, component] : obj->components_by_type) {
        auto renderer = dynamic_cast<fe::Renderer*>(component);
        if (renderer) return renderer;
    }

    return nullptr;
}

void fe::runtime::RenderHandler::UploadObject(Object* obj) {
    if (!obj->resource_manager->ObjectIsRenderable(obj)) {
        std::cerr << "Object " << obj << " is not renderable.\n";
        std::abort();
    }

    auto renderer = get_renderer(obj);
    assert(renderer);

    internal::gl_render_handle_ handle;
    handle.shader_program_id = renderer->material->shader->GetShaderID();

    glUseProgram(handle.shader_program_id);

    auto mesh = obj->GetComponent<Mesh>();
    if (mesh) {
        // TODO: Upload mesh
    }

    uploaded_render_objects_.insert_or_assign(obj, handle);
}

void fe::runtime::RenderHandler::DestroyObjectRenderBuffers(Object* obj) {

}

void fe::runtime::RenderHandler::DrawObjects() {

}