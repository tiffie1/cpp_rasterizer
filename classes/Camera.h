#ifndef CAMERA_H
#define CAMERA_H

#include "Canvas.h"
#include "CubeModel.h"
#include "Point.h"
#include "Triangle.h"
#include "HomoCoord.h"

#include <array>
#include <string>
#include <vector>

class Camera {
private:
  HomoCoord origin;
  struct VP {
    double height;
    double width;
    double distance;
  } viewport;

public:
  Camera();
  Camera(HomoCoord origin_pos);
  ~Camera();

  HomoCoord getOrigin();

  void DrawLine(Canvas &canvas, Point point0, Point point1, HomoCoord color);
  void DrawPoint(Canvas &canvas, Point point, HomoCoord color);
  void DrawWireframeTriangle(Canvas &canvas, Point point0, Point point1,
                             Point point2, HomoCoord color);
  void RenderTriangle(Canvas &canvas, Triangle triangle,
                      std::vector<std::vector<double>> projected_arr);
  void RenderModel(Canvas &canvas, CubeModel model);

  inline std::vector<double> ProjectVertex(Canvas &canvas, HomoCoord coord);

  void DrawFilledTriangle(Canvas &canvas, Point point0, Point point1,
                          Point point2, HomoCoord color);
};

#endif // !CAMERA_H
#define CAMERA_H
