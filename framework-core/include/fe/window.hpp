#ifndef FE_WINDOW_HPP
#define FE_WINDOW_HPP

#include "input_handler.hpp"

namespace fe {

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

class Window {
    WindowState state_;
public:
    InputHandler input_handler;

    /**
     * @brief Retrieve window state. 
     */
    const WindowState& GetState() const;
};

}

#endif 