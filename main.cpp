#include "classes/Camera.h"
#include "classes/Canvas.h"
#include "classes/Vector.h"
#include <cstdlib>

int main() {
  Canvas canvas("first.ppm", 300, 300);
  Camera camera;

  Vector red = Vector(255, 0, 0);
  Vector black = Vector(0, 0, 0);
  CubeModel cube = CubeModel(0, 0, 4, black);

  camera.RenderModel(canvas, cube);
  //camera.DrawWireframeTriangle(canvas, {18, 60}, {50, 30}, {85, 70},
                               //Vector(0, 0, 0));

  canvas.save_grid();
  return 0;
}
