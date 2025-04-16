#ifndef SCENE_H
#define SCENE_H

#include "Vector.h"
#include <string>

class Scene {
private:
  //std::string id;
  Vector bg_color;

public:
  Scene(/*std::string scene_identify,*/ Vector background_color);
  ~Scene();

  Vector getBackgroundColor() const;
};

#endif // !SCENE_H
