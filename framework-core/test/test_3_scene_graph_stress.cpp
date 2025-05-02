#include <iostream>
#include <iomanip>
#include <cassert>
#include <chrono>

#define DEBUG

#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/scene_objects/scene.hpp>
#include <fe/objects/object.hpp>
#include <fe/scene_manager.hpp>
#include <fe/resource_manager.hpp>

using namespace fe;

void add_lots_of_objects(Object* root, int max_level, int level=0) {
    if (level >= max_level) return;

    static constexpr int CHILD_NODE_MULTIPLIER = 5;

    for (int i = 0; i < CHILD_NODE_MULTIPLIER; ++i) {
        auto obj = root->AddChild<Object>();
        add_lots_of_objects(obj, max_level, 1 + level);
    }
}

int main() {
    ResourceManager rms;

    std::cout << "Starting stress test...\n";

    auto start = std::chrono::steady_clock::now();

    auto scene = rms.CreateObject<Scene>("Scene");
    add_lots_of_objects(scene, 9);

    std::cout << "Objects allocated: " << rms.allocated_objects_.size();
    std::cout << " (~" << ((sizeof(Object) * rms.allocated_objects_.size()) + rms.allocated_objects_.size() * 8) / 1000 << " KB) ";

    auto end = std::chrono::steady_clock::now();
    std::cout << "in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    std::cout << "Destroying objects...\n";

    start = std::chrono::steady_clock::now();

    rms.DestroyObject(scene);

    end = std::chrono::steady_clock::now();
    std::cout << "All objects destroyed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    
}