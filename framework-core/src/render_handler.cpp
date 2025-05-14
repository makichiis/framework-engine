#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <fe/render_handler.hpp>
#include <fe/objects/components/renderer.hpp>
#include <fe/objects/components/meshes/mesh.hpp>
#include <fe/objects/assets/materials/material.hpp>
#include <fe/objects/scene_objects/sample_objects/cube.hpp>
#include <fe/objects/components/transform.hpp>

#include <fe/objects/components/renderers/default_renderer.hpp>

#include <glad/gl.h>

fe::Renderer* get_renderer(fe::Object* obj) {
    for (auto&& [_, component] : obj->components_by_type) {
        auto renderer = dynamic_cast<fe::Renderer*>(component);
        if (renderer) return renderer;
    }

    return nullptr;
}

void fe::runtime::RenderHandler::UploadObject(fe::Object* obj) {
    if (!obj->resource_manager->ObjectIsRenderable(obj)) {
        std::cerr << "Object " << obj << " is not renderable.\n";
        std::abort();
    }

    auto renderer = get_renderer(obj);
    assert(renderer);

    fe::internal::gl_render_handle_ handle;
    handle.shader_program_id = renderer->material->shader->GetShaderID();

    glUseProgram(handle.shader_program_id);

    auto mesh = obj->GetComponent<Mesh>();
    if (mesh) {
        // TODO: Upload mesh. Mesh information provided by Mesh component.

        GLsizei vertex_sz = static_cast<GLsizei>(mesh->vertices.size() * sizeof(Vertex));
        std::cout << "Mesh byte size: " << vertex_sz << '\n';
        // TODO: Move VAO/VBO to helper fns

        GLuint vao, vbo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // TODO: Draw type specified by Mesh 
        glBufferData(GL_ARRAY_BUFFER, vertex_sz, reinterpret_cast<float*>(mesh->vertices.data()), GL_STATIC_DRAW);

        // init vao
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), reinterpret_cast<void*>(0));
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), reinterpret_cast<void*>(offsetof(Vertex, x)));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), reinterpret_cast<void*>(offsetof(Vertex, u)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), reinterpret_cast<void*>(offsetof(Vertex, nx)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        handle.vao = vao;
        handle.vbo = vbo;
        handle.ebo = 0;
        handle.draw_count = mesh->vertices.size();

        // TODO: Cache CPU-side verts for memory efficiency 
    }

    // TODO: Upload textures (eventually)

    uploaded_render_objects_.insert_or_assign(obj, handle);
}

void fe::runtime::RenderHandler::DestroyObjectRenderBuffers(Object* obj) {
    // TODO
}

#define color4_to_params(color) color.r, color.g, color.b, color.a

void fe::runtime::RenderHandler::DrawObjects() {
    ConfigureGLParameters();
    
    glClearColor(color4_to_params(config.clear_color));
    glClear(config.config_state.clear_mask);

    for (auto&& [obj, handle] : this->uploaded_render_objects_) {
        // TODO: get object transform components
        // TODO: draw override events

        glUseProgram(handle.shader_program_id);

        if (obj->HasComponent<fe::Transform>()) {
            auto trans = obj->GetComponent<fe::Transform>();

            // TODO: Filter objects by shader type to prevent useless uniform setting
            
            // TODO: Note, this needs to be refactored once renderer fetching is generalized. Temporary hotfix to meet deadline.
            if (obj->HasComponent<fe::DefaultRenderer>()) {
                glm::mat4 model = glm::identity<glm::mat4>();
                model = glm::translate(model, trans->position);
                model = glm::rotate(model, glm::radians(trans->rotation.angle_degrees), trans->rotation.axis);

                obj->GetComponent<fe::DefaultRenderer>()->material->shader->SetMatrix4s("model", 1, GL_FALSE, glm::value_ptr(model));
            }
        }

        glBindVertexArray(handle.vao);
        glBindBuffer(GL_ARRAY_BUFFER, handle.vbo);

        if (handle.ebo) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle.ebo);
            glDrawElements(GL_TRIANGLES, handle.draw_count, GL_UNSIGNED_INT, 0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            glUseProgram(0);
            
            continue;
        }

        glDrawArrays(GL_TRIANGLES, 0, handle.draw_count);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    }
}

void fe::runtime::RenderHandler::ConfigureGLParameters() {
    config.config_state = {};
    config.config_state.clear_mask |= GL_COLOR_BUFFER_BIT;

    if (config.depth) {
        glEnable(GL_DEPTH_TEST);
        config.config_state.clear_mask |= GL_DEPTH_BUFFER_BIT;
    }

    if (config.anti_aliasing) {
        // TODO
        std::cerr << "[Warning]: Anti-aliasing is not yet implemented.\n";
    }
}
