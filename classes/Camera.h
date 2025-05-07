#ifndef CAMERA_H
#define CAMERA_H

#include "Canvas.h"
#include "CubeModel.h"
#include "HomoCoord.h"
#include "Point.h"
#include "Triangle.h"

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

  struct {
    HomoCoord rotation;
    HomoCoord translation;
  } modifiers;

  struct {
    HomoCoord near;
    HomoCoord left;
    HomoCoord right;
    HomoCoord bottom;
    HomoCoord up;
  } planes;

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

  void rotate(double yaw, double roll, double pitch);
  void transform(double x_val, double y_val, double z_val);

  friend std::vector<double> FullTrans(Camera &camera, Canvas &canvas,
                                       CubeModel &model, HomoCoord scene_point);
};

#endif // !CAMERA_H
#define CAMERA_H
