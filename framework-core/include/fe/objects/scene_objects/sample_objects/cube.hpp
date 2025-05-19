#ifndef FE_SAMPLE_CUBE_HPP
#define FE_SAMPLE_CUBE_HPP

#include "fe/objects/scene_objects/sample_objects/sample_object.hpp"

namespace fe::sample {

/**
 * @brief A simple cube which rotates every update. Used for unit testing. 
 */
class RotatingCube : public SampleObject {

public:
    using SampleObject::SampleObject;

    /**
     * @brief Builds internal cube renderer and mesh.
     */
    void OnInit() override;

    void OnUpdate() override;

    void OnTest() override;
};

}

#endif 