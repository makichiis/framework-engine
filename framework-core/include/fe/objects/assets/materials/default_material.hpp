#ifndef FE_DEFAULT_MATERIAL_HPP
#define FE_DEFAULT_MATERIAL_HPP

#include "material.hpp"

namespace fe {

class DefaultMaterial : public Material {
public:
    using Material::Material;

    DefaultMaterial();
};

}

#endif 