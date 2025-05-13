#ifndef FE_ASSET_HPP
#define FE_ASSET_HPP

#include <fe/objects/object.hpp>

namespace fe {

class Asset : public Object {
public:
    using Object::Object;

    void OnInit();
};

}

#endif 