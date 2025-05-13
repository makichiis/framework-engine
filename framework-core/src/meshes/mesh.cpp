#include <fe/objects/components/meshes/mesh.hpp>

std::ostream& operator<<(std::ostream& os, const fe::Vertex& vertex) {
    os << "{ " << vertex.x << ", " << vertex.y << ", " << vertex.z << " }";
    
    return os;
}
