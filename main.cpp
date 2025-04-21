#include "classes/Camera.h"
#include "classes/Canvas.h"
#include "classes/Vector.h"
#include <cstdlib>
#include <iostream>

int main() {
  Canvas canvas("first.ppm", 1000, 1000);
  Camera camera;

  Vector red = Vector(255, 0, 0);
  Vector green = Vector(0, 255, 0);
  Vector blue = Vector(0, 0, 255);
  Vector black = Vector(0, 0, 0);


  //camera.DrawFilledTriangle(canvas, {-10, -25}, {-18, 40}, {30, 40}, black);
  //camera.DrawWireframeTriangle(canvas, {-10, -25}, {-18, 40}, {30, 40}, red);

  double x_off = -20;
  double y_off = -20;

  for (int i = 0; i < 20; i++) {
    x_off = -20;
    for (int j = 0; j < 20; j++) {
      // std::cout << "x_off: " << x_off << std::endl;

      camera.RenderModel(canvas, CubeModel(x_off, y_off, 40, black));
      x_off += 2.8;
    }
    y_off += 2.8;
  }

  canvas.save_grid();
  return 0;
}
