#ifndef FE_WINDOW_HPP
#define FE_WINDOW_HPP

#include "input_handler.hpp"

#include <string>

namespace fe {

namespace runtime { class FrameworkRuntimeHandler; }

struct Size2D {
    int x;
    int y;

    /**
     * @brief Compute `x:y` ratio of this size object.
     */
    double aspect() const;
};

/**
 * @brief Configurations and state information about this window.
 */
struct WindowState {
    Size2D size;
};

class Window { // TODO: refactor as base object
#ifdef DEBUG
public:
#endif 
    WindowState state_;
    void* window_handle_ = nullptr;

    friend InputHandler;
    InputHandler input_handler;

    friend runtime::FrameworkRuntimeHandler;
public:

    static Window* CreateNewWindow(Size2D size, std::string title);

    void DestroyWindow();

    /**
     * @brief Retrieve window state. 
     */
    const WindowState& GetState() const;

    InputHandler *const GetInput();

    bool WindowShouldClose() const;
    
    void PollEvents();

    void SwapBuffers() const;

    void InitializeWindowBindings(void (*window_bind_fn)(void* window_object_param), void* window_handle);

    void OnKeyInput(int key, int scancode, int action, int mods); // TODO: Standardize this call

    void OnResize(int width, int height);

    void OnCursorMove(double x_pos, double y_pos);

    void OnScroll(double x_offset, double y_offset);
};

}

#endif 