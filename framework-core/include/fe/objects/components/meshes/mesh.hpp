#ifndef FE_MESH_HPP
#define FE_MESH_HPP

#include <vector>

#include "../component.hpp"

namespace fe {

struct Vertex {
    float x, y, z;
    float u, v;
    float nx, ny, nz;
};

class Mesh : public Component {
public:
    std::vector<Vertex> vertices;

    using Component::Component;
};

}

#endif 