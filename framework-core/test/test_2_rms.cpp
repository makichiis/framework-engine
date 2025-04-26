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

    auto scene = rms.CreateObject<Scene>("Main Scene");

    auto camera = scene->AddChild<Camera>("Main Camera");
    assert(scene->children.size() == 1);

    scene->AddChild<Object>("Some Object");
    assert(scene->children.size() == 2);

    scene->RemoveChild(camera);
    assert(scene->children.size() == 1);

    rms.DestroyObject(scene);
}