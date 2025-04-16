#include "Scene.h"

Scene::Scene(/*std::string scene_identify,*/ Vector background_color)
    /*: scene_identification(scene_identify)*/ {
  bg_color = background_color;
}

Scene::~Scene() {}

Vector Scene::getBackgroundColor() const { return bg_color; }
