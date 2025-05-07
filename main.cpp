#include "classes/Camera.h"
#include "classes/Canvas.h"
#include "classes/HomoCoord.h"
#include <cstdlib>

int main() {
  Canvas canvas("first.ppm", 1000, 1000);
  Camera camera;

  HomoCoord red = HomoCoord(255, 0, 0, 1);
  HomoCoord green = HomoCoord(0, 255, 0, 1);
  HomoCoord blue = HomoCoord(0, 0, 255, 1);
  HomoCoord black = HomoCoord(0, 0, 0, 1);

  CubeModel model = CubeModel(black);

  model.transform(0, 0, 10);
  model.rotate(35, 0, 0);
  model.scale(1, 1, 1);

  camera.transform(0, 0, 3);
  camera.rotate(0, 35, 0);

  camera.RenderModel(canvas, model);

  /*
  double x_off = -20;
  double y_off = -20;

  for (int i = 0; i < 20; i++) {
    x_off = -20;
    for (int j = 0; j < 20; j++) {
      // std::cout << "x_off: " << x_off << std::endl;

      camera.RenderModel(canvas, CubeModel(x_off, y_off, 40, red));
      x_off += 2.8;
    }
    y_off += 2.8;
  }
  */

  // ------------ //
  canvas.save_grid();
  return 0;
}
