#include <fe/window.hpp>
#include <fe/input_handler.hpp>
#include <unordered_map>

#include <glad/gl.h> // preemptive, redundant include necessary to prevent definition overlap
#include <GLFW/glfw3.h>

void glfw_key_callback(GLFWwindow* window, int key, int scnacode, int action, int mods);
void glfw_char_callback(GLFWwindow* window, unsigned int codepoint); // TODO

const fe::WindowState& fe::Window::GetState() const {
    return state_;
}

fe::InputHandler *const fe::Window::GetInput() {
    return &input_handler;
}

void fe::Window::InitializeWindowBindings(void (*window_bind_fn)(void* window_object_param), void* window_handle) {
    if (window_handle_) return; // prevent user-side double-call

    window_handle_ = window_handle;
    window_bind_fn_ = window_bind_fn;

    input_handler.window_handle_ = window_handle_;
    input_handler.window_bind_fn_ = window_bind_fn_;

    for (auto key = GLFW_KEY_0; key <= GLFW_KEY_9; ++key) 
        input_handler.key_mappings_[key - GLFW_KEY_0] = key;

    for (auto key = GLFW_KEY_A; key <= GLFW_KEY_Z; ++key)
        input_handler.key_mappings_[key - GLFW_KEY_A + 10] = key;

    input_handler.key_mappings_[static_cast<uint16_t>(Key::LEFT_SHIFT)] = GLFW_KEY_LEFT_SHIFT;
    input_handler.key_mappings_[static_cast<uint16_t>(Key::RIGHT_SHIFT)] = GLFW_KEY_RIGHT_SHIFT;

    input_handler.key_mappings_[static_cast<uint16_t>(Key::LEFT_CTRL)] = GLFW_KEY_LEFT_CONTROL;
    input_handler.key_mappings_[static_cast<uint16_t>(Key::RIGHT_CTRL)] = GLFW_KEY_RIGHT_CONTROL;

    // TODO: Rest of key set.

    for (auto i = 0ULL; i < BITSIZEOF(key_mask_t); ++i) 
        input_handler.reverse_key_mappings_.insert_or_assign(input_handler.key_mappings_[i], static_cast<Key>(i));

    glfwSetWindowUserPointer(static_cast<GLFWwindow*>(window_handle_), this);
}

void fe::Window::OnKeyInput(int key, int scancode, int action, int mods) {
    if (!input_handler.reverse_key_mappings_.contains(key))
        return;

    auto key_mapping = input_handler.reverse_key_mappings_.at(key);

    auto key_event_list_result = input_handler.key_event_subscribers_.find(key_mapping);
    if (key_event_list_result != input_handler.key_event_subscribers_.end()) 
        for (auto&& event_handlers : key_event_list_result->second) 
            event_handlers(key, scancode, action, mods);
}

fe::key_mask_t fe::get_key_mask(Key key) {
    return 1ULL << static_cast<uint16_t>(key);
}

bool fe::InputHandler::GetKeyPressed(Key key) {
    window_bind_fn_(window_handle_);

    return glfwGetKey(static_cast<GLFWwindow*>(window_handle_), key_mappings_[static_cast<uint16_t>(key)]);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    fe::Window* window_ = static_cast<fe::Window*>(glfwGetWindowUserPointer(window));
    window_->OnKeyInput(key, scancode, action, mods);
}


