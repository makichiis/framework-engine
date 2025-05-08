#ifndef FE_ASSET_HPP
#define FE_ASSET_HPP

#include <fe/objects/object.hpp>

namespace fe {

class Asset : public Object {
public:
    using Object::Object;

    Asset();
    Asset(std::string p_name);
};

}

#endif 