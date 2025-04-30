#ifndef FE_COMPONENT_HPP
#define FE_COMPONENT_HPP

#include "fe/objects/scene_objects/scene_object.hpp"

namespace fe {

class Component : public SceneObject {
public:
    using SceneObject::SceneObject; // Inherit constructors from SceneObject
};

} // namespace fe

#endif // FE_COMPONENT_HPP
