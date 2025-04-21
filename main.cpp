#include "classes/Camera.h"
#include "classes/Canvas.h"
#include "classes/Vector.h"
#include <cstdlib>
#include <iostream>

int main() {
  Canvas canvas("first.ppm", 1000, 1000);
  Camera camera;

  Vector red = Vector(255, 0, 0);
  Vector black = Vector(0, 0, 0);
  Vector green = Vector(0, 255, 0);
  // CubeModel cube = CubeModel(0, 0, 4, black);
  // camera.RenderModel(canvas, cube);
  // camera.DrawWireframeTriangle(canvas, {18, 60}, {50, 30}, {85, 70},
  // Vector(0, 0, 0));

  double x_off = -20;
  double y_off = -10;

  for (int i = 0; i < 10; i++) {
    x_off = -20;
    for (int j = 0; j < 20; j++) {
      // std::cout << "x_off: " << x_off << std::endl;

      camera.RenderModel(canvas, CubeModel(x_off, y_off, 30, black));
      x_off += 2.5;
    }
    y_off += 2.5;
  }

  canvas.save_grid();
  return 0;
}
