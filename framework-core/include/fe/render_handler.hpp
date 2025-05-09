#ifndef FE_RENDER_HANDLER_HPP
#define FE_RENDER_HANDLER_HPP

#include <queue>
#include <unordered_map>

namespace fe {

class Object;


namespace internal {

// !! tech debt imminent !! 

using GLint = int; // TODO: (CRITICAL) Replace with unified GL header include 

struct gl_render_handle_ {
    GLint shader_program_id;
    GLint textures[32]; // TODO: (CRITICAL) Determine from comptime header rather than hardcoding 

    GLint vao;
    GLint vbo; // NOTE: Multiple-vbo count may change in the future.
    GLint ebo; // NOTE: Multiple-ebo count may change in the future;

    GLint draw_count;
};

}

namespace runtime {



class RenderHandler {
private:
    std::unordered_map<Object*, internal::gl_render_handle_> uploaded_render_objects_; // Hash table for fast object query/removal 
    std::unordered_map<Object*, internal::gl_render_handle_> skipped_objects_; // Objects set to skip drawing next frame 
    // TODO: Mat/mesh Batches
public:
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
     */
    void DrawObjects();
};

}
}


#endif 