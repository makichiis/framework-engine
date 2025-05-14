#ifndef FE_INPUT_HANDLER_HPP
#define FE_INPUT_HANDLER_HPP

#include <cstdint>

namespace fe {

/**
 * @brief All (currently) supported key mappings.
 */
enum class Key : uint16_t {
    Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,

    A, B, C, D, E, F, G, H, I, J, K, L, M, 
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    LEFT_SHIFT, RIGHT_SHIFT, LEFT_CTRL, RIGHT_CTRL,
    MINUS, PLUS, ENTER, SPACE
};

enum class KeyState {
    UP, DOWN, HELD 
};

struct CursorPosition {
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
    class RuntimeHandler;
}

class Window;

class InputHandler {
private:
    key_mask_t key_down_mask_ = 0ULL; // Denotes keys which are pressed this update
    key_mask_t key_held_mask_ = 0ULL; // Denotes keys which are held for a period of time.
    key_mask_t key_free_mask_ = 0ULL; // Denotes keys which are not pressed this update. Bitwise inversion of `key_down_mask_`.
    
    int key_mappings_[BITSIZEOF(key_mask_t)] = {}; // Mapping of platform-specific keys to keys in `fe::Key`

    void* window_handle_ = nullptr;
    void (*window_bind_fn_)(void* abstract_window_object_) = nullptr; // Function wrapper for window binding.

    friend Window;
public:
    /**
     * @brief Updates all internal key mappings to input info sent by window manager.
     */
    void UpdateMappings();

    /**
     * @brief Retrieves the state of `key`. 
     * 
     * @return `UP` - Key is not pressed
     * @return `DOWN` - Key is pressed
     * @return `HELD` - Key has been pressed for a while.
     */
    KeyState GetKey(Key key);

    CursorPosition GetCursorPosition();

    void SetCursorHidden(bool cursor_hidden);

    bool CursorIsHidden();
};

}

#endif 