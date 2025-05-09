#include <iostream>
#include <iomanip>

#include <fe/objects/components/renderer.hpp>
#include <fe/runtime_handler.hpp>

void fe::Renderer::handle_visibility_change_(bool visible) {
    std::cout << "Visibiltiy set to " << std::boolalpha << visible << '\n';
}
