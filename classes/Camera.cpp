#include "Camera.h"
#include "Vector.h"
#include <iostream>
#include <math.h>

/*
#include "Canvas.h"
#include "Scene.h"
#include <array>
#include <cmath>
#include <vector>
*/

Camera::Camera() : origin(Vector()) {
  viewport.height = 1;
  viewport.width = 1;
  viewport.distance = 1;
}

Camera::Camera(Vector origin_vec) : origin(origin_vec) {
  viewport.height = 1;
  viewport.width = 1;
  viewport.distance = 1;
}
Camera::~Camera() {}

Vector Camera::getOrigin() { return origin; }

std::vector<double> Interpolate(double start0, double end0, double start1,
                                double end1) {
  std::vector<double> calculated_values;

  if (start0 == start1) {
    calculated_values.push_back(end0);
    return calculated_values;
  }

  double slope = (end1 - end0) / (start1 - start0);
  double displacement = end0;

  for (int i = start0; i <= start1; i++) {
    calculated_values.push_back(displacement);
    displacement += slope;
  }

  return calculated_values;
}

void Camera::DrawLine(Canvas &canvas, Point point0, Point point1,
                      Vector color) {
  int x0 = static_cast<int>(point0.x);
  int y0 = static_cast<int>(point0.y);
  int x1 = static_cast<int>(point1.x);
  int y1 = static_cast<int>(point1.y);
  int temp;

  if (abs(x1 - x0) > abs(y1 - y0)) {
    if (x0 > x1) {
      temp = x0;
      x0 = x1;
      x1 = temp;

      temp = y0;
      y0 = y1;
      y1 = temp;
    }

    std::vector<double> ys = Interpolate(x0, y0, x1, y1);
    for (int x = x0; x < x1; x++) {
      canvas.plotGrid(x, static_cast<int>(ys[x - x0]), color);
    }
  }

  else {
    if (y0 > y1) {
      temp = x0;
      x0 = x1;
      x1 = temp;

      temp = y0;
      y0 = y1;
      y1 = temp;
    }

    std::vector<double> xs = Interpolate(y0, x0, y1, x1);

    for (int y = y0; y < y1; y++) {
      canvas.plotGrid(static_cast<int>(xs[y - y0]), y, color);
    }
  }
}

void Camera::DrawPoint(Canvas &canvas, Point point, Vector color) {
  canvas.plotGrid(point.x, point.y, color);
}

void Camera::DrawWireframeTriangle(Canvas &canvas, Point point0, Point point1,
                                   Point point2, Vector color) {
  DrawLine(canvas, point0, point1, color);
  DrawLine(canvas, point1, point2, color);
  DrawLine(canvas, point2, point0, color);
}

inline std::vector<double> Camera::ProjectVertex(Canvas &canvas, Vector coord) {
  double x = coord.x * viewport.distance / coord.z;
  double y = coord.y * viewport.distance / coord.z;
  return {(x * canvas.getWidth() / viewport.width),
          (y * canvas.getHeight() / viewport.height)};
}

void Camera::RenderModel(Canvas &canvas, CubeModel model) {
  std::vector<std::vector<double>> projected;

  for (int i = 0; i < model.getVertexCount(); i++) {
    projected.push_back(ProjectVertex(canvas, model.getVertex(i)));
  }

  for (int i = 0; i < model.getTriangleCount(); i++) {
    RenderTriangle(canvas, model.getTriangle(i), projected);
  }
}

void Camera::RenderTriangle(Canvas &canvas, Triangle triangle,
                            std::vector<std::vector<double>> projected_arr) {
  Point point1 = {static_cast<int>(projected_arr[triangle.id1][0]),
                  static_cast<int>(projected_arr[triangle.id1][1])};
  Point point2 = {static_cast<int>(projected_arr[triangle.id2][0]),
                  static_cast<int>(projected_arr[triangle.id2][1])};
  Point point3 = {static_cast<int>(projected_arr[triangle.id3][0]),
                  static_cast<int>(projected_arr[triangle.id3][1])};

  DrawWireframeTriangle(canvas, point1, point2, point3, triangle.color);
}

/* THINGS TO IMPLEMENT LATER.
void Camera::rotate(double yaw, double roll, double pitch) {
  yaw = yaw * M_PI / 180.0;
  roll = roll * M_PI / 180.0;
  pitch = pitch * M_PI / 180.0;

  std::array<Vector, 3> matrix = {
      {Vector(cos(roll) * cos(yaw),
              cos(roll) * sin(yaw) * sin(pitch) - sin(roll) * cos(pitch),
              cos(roll) * sin(yaw) * cos(pitch) + sin(roll) * sin(pitch)),
       Vector(sin(roll) * cos(yaw),
              sin(roll) * sin(yaw) * sin(pitch) + cos(roll) * cos(pitch),
              sin(roll) * sin(yaw) * cos(pitch) - cos(roll) * sin(pitch)),
       Vector(-sin(yaw), cos(yaw) * sin(pitch), cos(yaw) * cos(pitch))}};
  rotational_matrix = matrix;
}

void Camera::move(double displacement_x, double displacement_y,
                  double displacement_z) {
  origin = origin + Vector(displacement_x, displacement_y, displacement_z);
}

Vector operator*(std::array<Vector, 3> matrix, Vector vector) {
  return Vector(
      matrix[0].x * vector.x + matrix[1].x * vector.y + matrix[2].x * vector.z,
      matrix[0].y * vector.x + matrix[1].y * vector.y + matrix[2].y * vector.z,
      matrix[0].z * vector.x + matrix[1].z * vector.y + matrix[2].z * vector.z);
}

Vector Camera::CanvasToViewPort(Canvas &canvas, double x, double y) {
  return rotational_matrix *
         Vector(x * canvas.getV_Width() / canvas.getWidth(),
                y * canvas.getV_Height() / canvas.getHeight(),
                canvas.getV_Distance());
}

double linear_map(double input, double input_min, double input_max,
                  double output_min, double output_max) {
  return output_min + ((output_max - output_min) / (input_max - input_min)) *
                          (input - input_min);
}

double fractional_function(double x, double strength) {
  return 1 / (pow(x, strength));
}

Vector ClampColor(Vector &color) {
  if (color.x < 0)
    color.x = 0;
  else if (color.x > 255)
    color.x = 255;
  if (color.y < 0)
    color.y = 0;
  else if (color.y > 255)
    color.y = 255;
  if (color.z < 0)
    color.z = 0;
  else if (color.z > 255)
    color.z = 255;

  return Vector(round(color.x), round(color.y), round(color.z));
}
*/
