#ifndef FE_SAMPLE_CUBE_HPP
#define FE_SAMPLE_CUBE_HPP

#include "fe/objects/scene_objects/sample_objects/sample_object.hpp"

namespace fe::sample {

class Cube : public SampleObject {
public:
    using SampleObject::SampleObject;

    Cube();
};

}

#endif 