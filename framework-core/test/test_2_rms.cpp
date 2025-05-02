#include <iostream>
#include <cassert>

#include <fe/objects/scene_objects/camera.hpp>
#include <fe/objects/scene_objects/scene.hpp>
#include <fe/objects/object.hpp>
#include <fe/scene_manager.hpp>
#include <fe/resource_manager.hpp>

using namespace fe;

int main() {
    ResourceManager rms;

    auto obj = rms.CreateObject<Object>("Some Object");
    obj->AddChild<Object>();
    obj->AddChild<Object>();

    rms.DestroyObject(obj);

    auto scene = rms.CreateObject<Scene>("Main Scene");

    auto camera = scene->AddChild<Camera>("Main Camera");
    assert(scene->children.size() == 1);

    scene->AddChild<Object>("Some Object");
    assert(scene->children.size() == 2);

    scene->RemoveChild(camera);
    assert(scene->children.size() == 1);

    rms.DestroyObject(scene);

    // Test issue #1 (http://github.com/makichiis/framework-engine/issues/1). Should be freed by ResourceManager destructor.
    auto dummy = rms.CreateObject<Object>("Dummy Object"); 
    auto dummy_child = dummy->AddChild<Object>("Dummy Child");
    (void)dummy_child;
}