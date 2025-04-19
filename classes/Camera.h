#ifndef CAMERA_H
#define CAMERA_H

#include "Canvas.h"
#include "CubeModel.h"
#include "Triangle.h"
#include "Vector.h"
#include "Point.h"

#include <array>
#include <string>
#include <vector>

class Camera {
private:
  Vector origin;
  struct VP {
    double height;
    double width;
    double distance;
  } viewport;

public:
  Camera();
  Camera(Vector origin_pos);
  ~Camera();

  Vector getOrigin();

  void DrawLine(Canvas &canvas, Point point0, Point point1, Vector color);
  void DrawPoint(Canvas &canvas, Point point, Vector color);
  void DrawWireframeTriangle(Canvas &canvas, Point point0, Point point1,
                             Point point2, Vector color);
  void RenderTriangle(Canvas &canvas, Triangle triangle,
                      std::vector<std::vector<double>> projected_arr);
  void RenderModel(Canvas &canvas, CubeModel model);

  inline std::vector<double> ProjectVertex(Canvas &canvas, Vector coord);

  // void DrawFilledTriangle(Canvas &canvas, Point point0, Point point1,
  // Point point2, Vector color);

  /*
   void render_scene(Canvas &canvas,
   unsigned short recursion_limit);
   void rotate(double yaw, double roll, double pitch);
   void move(double displacement_x, double displacement_y,
   double displacement_z);
   Vector CanvasToViewPort(Canvas &canvas, double x, double y);
  */
};

#endif // !CAMERA_H
#define CAMERA_H
