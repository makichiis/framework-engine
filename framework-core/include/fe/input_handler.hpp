#ifndef FE_INPUT_HANDLER_HPP
#define FE_INPUT_HANDLER_HPP

#include <unordered_map>
#include <vector>
#include <cstdint>

namespace fe {

/**
 * @brief All (currently) supported key mappings.
 */
enum class Key : uint16_t {
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, 

    A, B, C, D, E, F, G, H, I, J, K, L, M, 
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    LEFT_SHIFT, RIGHT_SHIFT, LEFT_CTRL, RIGHT_CTRL, ALT, 
    MINUS, PLUS, ENTER, SPACE,
    LEFT, RIGHT, UP, DOWN,
};

enum class KeyState {
    UP, DOWN, HELD, QUIET
};

struct CursorPosition {
    double x;
    double y;

    /**
     * @brief Retrieves the cursor delta of this cursor position and `other`. 
     * Absolute value of differences.
     */
    CursorPosition delta(const CursorPosition& other);
};

struct ScrollDelta {
    double x;
    double y;
};

using key_mask_t = uint64_t;

#define BITSIZEOF(t_) (8 * sizeof (t_))

/**
 * @brief Retrieve the key mask for `key`. 
 * @warning This is only meaningful when the `Key` list is less than
 * 64 elements in length. If it ever grows beyond that, this should 
 * be deprecated and the mapping should be done with a hash. 
 */
key_mask_t get_key_mask(Key key); // 1ULL << static_cast<uint16_t>(key)

namespace runtime {
    class FrameworkRuntimeHandler;
}

class Window;

class InputHandler {
private:
    int key_mappings_[BITSIZEOF(key_mask_t)] = {}; // Mapping of keys in `fe::Key` to platform-specific keys
    std::unordered_map<int, fe::Key> reverse_key_mappings_; // Mapping of platform-specific keys to Framework keys

    std::unordered_map<fe::Key, std::vector<void (*)(int key, int scancode, int action, int mods)>> key_event_subscribers_;

    friend Window;
    Window* window_;

    CursorPosition last_position_ = {};
    CursorPosition delta_ = {};
    ScrollDelta scroll_delta_ = {};
public:
    /**
     * @brief Retrieves the last position of the input handler. 
     */
    CursorPosition GetLastCursorPosition() const;

    /**
     * @brief Retrieve the distance moved by the cursor since the last update.
     */
    CursorPosition GetCursorDelta() const;

    /**
     * @brief Retrieve the scroll delta since last update.
     */
    ScrollDelta GetScrollDelta() const;

    /**
     * @brief Retrieves whether the current key is being pressed. 
     */
    bool GetKeyPressed(Key key);

    /**
     * @brief Retrieve the 2D position of the cursor. 
     */
    CursorPosition GetCursorPosition();


    /**
     * @brief Set cursor visibility to `cursor_hidden`. 
     * @note Hidden cursors still respond to cursor move events. 
     */
    void SetCursorHidden(bool cursor_hidden);

    /**
     * @returns `true` if the cursor is not visible, `false` otherwise. 
     */
    bool CursorIsHidden();

    /**
     * @brief Subscribe `event_handler` to `key`. 
     * @note TODO: Refactor using class-bindable function wrapper (`std::function<T>`)
     * @deprecated Just use `fe::Object::OnUpdate`. Once the event system is reworked, this function will have no performance benefits.
     */    
    void RegisterKeyEvent(Key key, void (*event_handler)(int key, int scancode, int action, int mods));
};

}

#endif 