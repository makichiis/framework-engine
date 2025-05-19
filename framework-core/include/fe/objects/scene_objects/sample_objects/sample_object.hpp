#ifndef FE_SAMPLE_OBJECT_HPP
#define FE_SAMPLE_OBJECT_HPP

#include "fe/objects/scene_objects/scene_object.hpp"

namespace fe::sample {

/**
 * @brief Sample objects are not meant to be defined by the end-user, though
 * they wont necessarily break anything if they are. Used to notate objects 
 * belonging to samples and unit tests.
 */
class SampleObject : public SceneObject {
public:
    using SceneObject::SceneObject;
};

}

#endif 