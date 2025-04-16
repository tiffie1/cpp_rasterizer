#include "classes/Camera.h"
#include "classes/Canvas.h"
#include <classes/Vector.h>
#include <cstdlib>

int main() {
  Canvas canvas("first.ppm", 100, 100);
  Camera camera;

  Vector red = Vector(255, 0, 0);
  Vector black = Vector(0, 0, 0);

  camera.DrawWireframeTriangle(canvas, {18, 60}, {50, 30}, {85, 70},
                               Vector(0, 0, 0));

  canvas.save_grid();
  return 0;
}
