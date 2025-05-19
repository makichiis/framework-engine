#ifndef FE_SCENE_OBJECT_HPP
#define FE_SCENE_OBJECT_HPP

#include "../object.hpp"

namespace fe {

/**
 * @brief A scene object is an object which is expected to exist within a scene.
 * @note This subtype is currently purely notational, but may have performance-related
 * traits in the future. 
 */
class SceneObject : public Object {
public:
    using Object::Object;
};

}

#endif 