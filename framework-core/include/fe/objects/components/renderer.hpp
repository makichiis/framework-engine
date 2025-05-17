#ifndef FE_COMPONENT_RENDERER_HPP
#define FE_COMPONENT_RENDERER_HPP

#include "fe/objects/components/component.hpp"
#include "../assets/materials/material.hpp"
#include "fe/util/flag.hpp"

namespace fe {

class Renderer : public Component {
private:
    void handle_visibility_change_(bool visible);

public:
    using VisibilityFlag = Flag<decltype(&Renderer::handle_visibility_change_)>;
    
    Material* material; // Underlying render blueprint for this renderer.
    VisibilityFlag visible { &Renderer::handle_visibility_change_ }; // Whether to render this object.

    using Component::Component;
};

}

#endif 