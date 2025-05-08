#ifndef FE_MATERIAL_HPP
#define FE_MATERIAL_HPP

#include "../asset.hpp"
#include "../shaders/shader.hpp"

namespace fe {

struct Color {
    float r;
    float g;
    float b;
    float a;
};

class Material : public Asset {
public:
    Shader* shader; // Shader used by this material.
    Color color; // Color of this material.
    // TODO: Textures 

    using Asset::Asset;
};

}

#endif 