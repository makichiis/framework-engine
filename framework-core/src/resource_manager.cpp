#include <fe/resource_manager.hpp>
#include <fe/objects/object.hpp>

fe::ResourceManager::ResourceManager() = default;

fe::ResourceManager::ResourceManager(Allocator alloc) : alloc_{ alloc } {}

fe::ResourceManager::~ResourceManager() {
    while (!allocated_objects_.empty()) {
        auto* obj = *allocated_objects_.begin();

        DestroyObject(obj);
    }
}


bool fe::ResourceManager::object_is_in_alloc_heap_(Object* obj) { return allocated_objects_.find(obj) != allocated_objects_.end(); }
bool fe::ResourceManager::object_is_tentative_(Object* obj) { return tentative_objects_.find(obj) != tentative_objects_.end(); }
