#ifndef FE_RENDER_HANDLER_HPP
#define FE_RENDER_HANDLER_HPP

#include <queue>
#include <unordered_map>

#include <glad/gl.h>

namespace fe {

class Object;


namespace internal {

struct gl_render_handle_ {
    GLuint shader_program_id;
    GLuint textures[32]; // TODO: (CRITICAL) Determine from comptime header rather than hardcoding 

    GLuint vao;
    GLuint vbo; // NOTE: Multiple-vbo count may change in the future.
    GLuint ebo; // NOTE: Multiple-ebo count may change in the future;

    GLuint draw_count;
    GLuint texture_count;

    void DestroyAttachedBuffers();
};

}

namespace runtime {

class RenderHandler;

struct ConfigState {
    GLbitfield clear_mask = 0x00;
};

struct RenderConfig {
    bool depth = true;
    bool anti_aliasing = false;
    struct clear_color_t { float r; float g; float b; float a; } clear_color = { 0.0f, 0.5f, 0.5f, 1.0f };

private:
    ConfigState config_state;

    friend RenderHandler;
};

class RenderHandler {
private:
#ifdef DEBUG
public:
#endif 
    std::unordered_map<Object*, fe::internal::gl_render_handle_> uploaded_render_objects_; // Hash table for fast object query/removal 
    std::unordered_map<Object*, fe::internal::gl_render_handle_> skipped_objects_; // Objects set to skip drawing next frame 
    // TODO: Mat/mesh Batches
public:
    RenderConfig config;

    ~RenderHandler();

    /**
     * @brief Uploads an object's render data -- provided it contains a componenent derived from `Renderer`.
     * TODO: Word this better :sob: 
     */
    void UploadObject(Object* obj);

    /**
     * @brief Destroys the render handle mapped by `obj` and removes it from this render handler. 
     */
    void DestroyObjectRenderBuffers(Object* obj);

    /**
     * @brief Draw all objects loaded in this render handler. Should never be called by game code. 
     * TODO: Figure out how to privatize. 
     */
    void DrawObjects();

    /**
     * @brief Updates the OpenGL context with the current configurations. 
     */
    void ConfigureGLParameters();

};

}
}


#endif 