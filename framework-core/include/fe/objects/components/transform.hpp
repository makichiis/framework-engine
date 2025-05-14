#ifndef FE_TRANSFORM_HPP
#define FE_TRANSFORM_HPP

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <fe/objects/components/component.hpp>

namespace fe {

struct Rotation {
    glm::vec3 axis = {};
    float angle_degrees = 0.0f;
};

class Transform : public Component {
public:
    glm::vec3 position = {};
    Rotation rotation = {}; // TODO: Abstraction functions

    using Component::Component;
};

}

#endif 