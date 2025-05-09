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

  //camera.rotate(0, 0, -90);
  camera.transform(0, 0, 5);

  camera.RenderModel(canvas, model);

  // ------------ //
  canvas.save_grid();
  return 0;
}
