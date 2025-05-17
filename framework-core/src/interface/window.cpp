#include <fe/window.hpp>
#include <fe/input_handler.hpp>
#include <unordered_map>

#include <glad/gl.h> // preemptive, redundant include necessary to prevent definition overlap
#include <GLFW/glfw3.h>

#include <iostream>

#include <cassert>
#include <cmath>

// TODO: Rest of events. Current implementation is to meet deliverable.
// https://www.glfw.org/docs/3.3/window_guide.html#window_properties

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void glfw_cursor_callback(GLFWwindow* window, double x_pos, double y_pos);
void glfw_key_callback(GLFWwindow* window, int key, int scnacode, int action, int mods);
void glfw_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);


// Goal is to make this unit as branchless as possible. Thousands of object events could invoke
// most of these components. 

fe::CursorPosition fe::CursorPosition::delta(const CursorPosition& other) { 
    x -= other.x;
    y -= other.y;

    x = fabs(x);
    y = fabs(y);

    return *this;
}

double fe::Size2D::aspect() const {
    return static_cast<double>(x) / static_cast<double>(y);
}

const fe::WindowState& fe::Window::GetState() const {
    return state_;
}

fe::InputHandler *const fe::Window::GetInput() {
    return &input_handler;
}

fe::Window* fe::Window::CreateNewWindow(Size2D size, std::string title) {

    // TODO: Abstract GLFW init to singleton constructor, since it is global
    if (!glfwInit()) {
        std::cerr << "[ERROR]: Failed to initialize GLFW.\n";
        std::abort();
    }

    // TODO: Move window parameters to configuration struct 

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "[ERROR] Initialization of GLFW window unsuccessful.\n";
        std::abort();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::cerr << "[ERROR]: Could not load GLAD.\n";
        std::abort();
    }

    Window* result = new Window;
    result->input_handler.window_ = result;
    result->state_.size = size;
    result->window_handle_ = window;

    glfwSetWindowUserPointer(window, result);

    for (auto key = GLFW_KEY_0; key <= GLFW_KEY_9; ++key) 
        result->input_handler.key_mappings_[key - GLFW_KEY_0] = key;

    for (auto key = GLFW_KEY_A; key <= GLFW_KEY_Z; ++key)
        result->input_handler.key_mappings_[key - GLFW_KEY_A + 10] = key;

    result->input_handler.key_mappings_[static_cast<uint16_t>(Key::LEFT_SHIFT)] = GLFW_KEY_LEFT_SHIFT;
    result->input_handler.key_mappings_[static_cast<uint16_t>(Key::RIGHT_SHIFT)] = GLFW_KEY_RIGHT_SHIFT;

    result->input_handler.key_mappings_[static_cast<uint16_t>(Key::LEFT_CTRL)] = GLFW_KEY_LEFT_CONTROL;
    result->input_handler.key_mappings_[static_cast<uint16_t>(Key::RIGHT_CTRL)] = GLFW_KEY_RIGHT_CONTROL;

    // TODO: Rest of key set.

    for (auto i = 0ULL; i < BITSIZEOF(key_mask_t); ++i) 
        result->input_handler.reverse_key_mappings_.insert_or_assign(result->input_handler.key_mappings_[i], static_cast<Key>(i));

    glfwSetWindowSizeCallback(static_cast<GLFWwindow*>(result->window_handle_), glfw_window_size_callback);
    glfwSetCursorPosCallback(static_cast<GLFWwindow*>(result->window_handle_), glfw_cursor_callback);
    glfwSetKeyCallback(static_cast<GLFWwindow*>(result->window_handle_), glfw_key_callback);
    glfwSetScrollCallback(static_cast<GLFWwindow*>(result->window_handle_), glfw_scroll_callback);

    std::cout << "Window bindings set\n";

    return result;
}

void fe::Window::DestroyWindow() {
    assert(!"not implemented");
}

// deprecated
void fe::Window::InitializeWindowBindings(void (*window_bind_fn)(void* window_object_param), void* window_handle) {}
void fe::Window::PollEvents() {
    glfwPollEvents();
}

bool fe::Window::WindowShouldClose() const {
    return glfwWindowShouldClose(static_cast<GLFWwindow*>(window_handle_));
}

void fe::Window::SwapBuffers() const {
    glfwSwapBuffers(static_cast<GLFWwindow*>(window_handle_));
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

void fe::Window::OnResize(int width, int height) {
    state_.size = { width, height };
    glViewport(0, 0, state_.size.x, state_.size.y); // TODO: THIS IS A PIPELINE PART! Refactor into render handler
}

void fe::Window::OnCursorMove(double x_pos, double y_pos) {
    input_handler.delta_ = input_handler.last_position_.delta({ x_pos, y_pos });
    input_handler.last_position_ = { x_pos, y_pos };
}

void fe::Window::OnScroll(double x_offset, double y_offset) { 
    input_handler.scroll_delta_ = { x_offset, y_offset };
}

fe::key_mask_t fe::get_key_mask(Key key) {
    return 1ULL << static_cast<uint16_t>(key);
}

bool fe::InputHandler::GetKeyPressed(Key key) {
    assert(window_->window_handle_); 
    return glfwGetKey(static_cast<GLFWwindow*>(window_->window_handle_), key_mappings_[static_cast<uint16_t>(key)]) == GLFW_PRESS;
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    fe::Window* window_ = static_cast<fe::Window*>(glfwGetWindowUserPointer(window));
    assert(window_);

    window_->OnKeyInput(key, scancode, action, mods);
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
    fe::Window* window_ = static_cast<fe::Window*>(glfwGetWindowUserPointer(window));
    assert(window_);

    window_->OnResize(width, height);
}

void glfw_cursor_callback(GLFWwindow* window, double x_pos, double y_pos) {
    fe::Window* window_ = static_cast<fe::Window*>(glfwGetWindowUserPointer(window));
    assert(window_);

    window_->OnCursorMove(x_pos, y_pos);
}

void glfw_scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    fe::Window* window_ = static_cast<fe::Window*>(glfwGetWindowUserPointer(window));
    assert(window_);

    window_->OnScroll(x_offset, y_offset);
}
