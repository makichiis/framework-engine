#ifndef FE_DEFAULT_RENDERER_HPP
#define FE_DEFAULT_RENDERER_HPP

#include "../renderer.hpp"

namespace fe {

class DefaultRenderer : public Renderer {
public:
    using Renderer::Renderer;

    void OnInit() override;
};

}

#endif 