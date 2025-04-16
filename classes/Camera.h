#ifndef CAMERA_H
#define CAMERA_H

#include "Canvas.h"
#include "Vector.h"

#include <array>
#include <string>

class Camera {
private:
  Vector origin;

public:
  Camera();
  Camera(Vector origin_pos);

  Vector getOrigin();


  void render_scene(Canvas &canvas,
                    unsigned short recursion_limit);

  // void rotate(double yaw, double roll, double pitch);
  // void move(double displacement_x, double displacement_y,
  // double displacement_z);
  //Vector CanvasToViewPort(Canvas &canvas, double x, double y);
};

#endif // !CAMERA_H
#define CAMERA_H
