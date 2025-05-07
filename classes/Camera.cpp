#include "Camera.h"
#include "HomoCoord.h"
#include "Scene.h"
#include <cmath>
#include <math.h>
#include <vector>

inline void swap(int &x, int &y) {
  int temp = x;
  x = y;
  y = temp;
}

Camera::Camera() : origin(HomoCoord()) {
  viewport.height = 1;
  viewport.width = 1;
  viewport.distance = 1;

  modifiers.rotation = HomoCoord();
  modifiers.translation = HomoCoord();

  double num = 1/std::sqrt(2);

  planes.near = HomoCoord(0, 0, viewport.distance, 0);
  planes.left = HomoCoord(num, 0, num, 0);
  planes.right = HomoCoord(-num, 0, num, 0);
  planes.bottom = HomoCoord(0, num, num, 0);
  planes.up = HomoCoord(0, -num, num, 0);
}

Camera::Camera(HomoCoord origin_vec) : origin(origin_vec) {
  viewport.height = 1;
  viewport.width = 1;
  viewport.distance = 1;

  modifiers.rotation = HomoCoord();
  modifiers.translation = HomoCoord();

  double num = 1/std::sqrt(2);

  planes.near = HomoCoord(0, 0, viewport.distance, 0);
  planes.left = HomoCoord(num, 0, num, 0);
  planes.right = HomoCoord(-num, 0, num, 0);
  planes.bottom = HomoCoord(0, num, num, 0);
  planes.up = HomoCoord(0, -num, num, 0);
}
Camera::~Camera() {}

HomoCoord Camera::getOrigin() { return origin; }

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
                      HomoCoord color) {
  int x0 = point0.x;
  int y0 = point0.y;
  int x1 = point1.x;
  int y1 = point1.y;

  if (abs(x1 - x0) > abs(y1 - y0)) {
    if (x0 > x1) {
      swap(x0, x1);
      swap(y0, y1);
    }

    std::vector<double> ys = Interpolate(x0, y0, x1, y1);
    for (int x = x0; x < x1; x++) {
      canvas.plotGrid(x, static_cast<int>(ys[x - x0]), color);
    }
  }

  else {
    if (y0 > y1) {
      swap(x0, x1);
      swap(y0, y1);
    }

    std::vector<double> xs = Interpolate(y0, x0, y1, x1);

    for (int y = y0; y < y1; y++) {
      canvas.plotGrid(static_cast<int>(xs[y - y0]), y, color);
    }
  }
}

void Camera::DrawPoint(Canvas &canvas, Point point, HomoCoord color) {
  canvas.plotGrid(point.x, point.y, color);
}

void Camera::DrawWireframeTriangle(Canvas &canvas, Point point0, Point point1,
                                   Point point2, HomoCoord color) {
  DrawLine(canvas, point0, point1, color);
  DrawLine(canvas, point1, point2, color);
  DrawLine(canvas, point2, point0, color);
}

inline std::vector<double> Camera::ProjectVertex(Canvas &canvas,
                                                 HomoCoord coord) {
  double x = coord.x * viewport.distance / coord.z;
  double y = coord.y * viewport.distance / coord.z;
  return {(x * canvas.getWidth() / viewport.width),
          (y * canvas.getHeight() / viewport.height)};
}

void Clip(Camera &camera, Canvas &canvas, Scene &scene) {
}

std::vector<double> FullTrans(Camera &camera, Canvas &canvas, CubeModel &model,
                HomoCoord scene_point) {

  scene_point = scene_point * model.getScaleModifier(); // Scale instance.

  // Rotate instance.
  double yaw = model.getRotationModifier().x;
  double roll = model.getRotationModifier().y;
  double pitch = model.getRotationModifier().z;

  yaw = yaw * M_PI / 180.0;
  roll = roll * M_PI / 180.0;
  pitch = pitch * M_PI / 180.0;

  HomoCoord matrix[4] = {
      HomoCoord(cos(roll) * cos(yaw),
                cos(roll) * sin(yaw) * sin(pitch) - sin(roll) * cos(pitch),
                cos(roll) * sin(yaw) * cos(pitch) + sin(roll) * sin(pitch), 0),
      HomoCoord(sin(roll) * cos(yaw),
                sin(roll) * sin(yaw) * sin(pitch) + cos(roll) * cos(pitch),
                sin(roll) * sin(yaw) * cos(pitch) - cos(roll) * sin(pitch), 0),
      HomoCoord(-sin(yaw), cos(yaw) * sin(pitch), cos(yaw) * cos(pitch), 0),
      HomoCoord(0, 0, 0, 1)};

  scene_point =
      HomoCoord(scene_point.dot(matrix[0]), scene_point.dot(matrix[1]),
                scene_point.dot(matrix[2]), scene_point.dot(matrix[3]));

  scene_point =
      scene_point + model.getTranslationModifier(); // Transform instance.

  scene_point =
      scene_point -
      (camera.origin + camera.modifiers.translation); // Transform Camera.

  // Rotate Camera.
  yaw = camera.modifiers.rotation.x;
  roll = camera.modifiers.rotation.y;
  pitch = camera.modifiers.rotation.z;

  yaw = yaw * M_PI / 180.0;
  roll = roll * M_PI / 180.0;
  pitch = pitch * M_PI / 180.0;

  matrix[0] =
      HomoCoord(cos(roll) * cos(yaw),
                cos(roll) * sin(yaw) * sin(pitch) - sin(roll) * cos(pitch),
                cos(roll) * sin(yaw) * cos(pitch) + sin(roll) * sin(pitch), 0);
  matrix[1] =
      HomoCoord(sin(roll) * cos(yaw),
                sin(roll) * sin(yaw) * sin(pitch) + cos(roll) * cos(pitch),
                sin(roll) * sin(yaw) * cos(pitch) - cos(roll) * sin(pitch), 0);

  matrix[2] =
      HomoCoord(-sin(yaw), cos(yaw) * sin(pitch), cos(yaw) * cos(pitch), 0);

  matrix[3] = HomoCoord(0, 0, 0, 1);

  scene_point =
      HomoCoord(scene_point.dot(matrix[0]), scene_point.dot(matrix[1]),
                scene_point.dot(matrix[2]), scene_point.dot(matrix[3]));

  // Project and Map to Canvas
  double x = ((scene_point.x * camera.viewport.distance) / scene_point.z) *
          (canvas.getWidth() / camera.viewport.width);
  double y = ((scene_point.y * camera.viewport.distance) / scene_point.z) *
          (canvas.getHeight() / camera.viewport.height);

  return {x, y};
}

void Camera::RenderModel(Canvas &canvas, CubeModel model) {
  std::vector<std::vector<double>> projected;

  for (int i = 0; i < model.getVertexCount(); i++) {
    std::vector<double> proj = FullTrans(*this, canvas, model, model.getVertex(i));

    std::cout << model.getVertex(i) << std::endl;
    std::cout << "{" << proj[0] << ", " << proj[1]  << "}" << std::endl << std::endl;

    projected.push_back(FullTrans(*this, canvas, model, model.getVertex(i)));
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

  // DrawWireframeTriangle(canvas, point1, point2, point3, triangle.color);
  DrawFilledTriangle(canvas, point1, point2, point3, triangle.color);
}

void Camera::DrawFilledTriangle(Canvas &canvas, Point point1, Point point2,
                                Point point3, HomoCoord color) {
  int x0 = point1.x;
  int y0 = point1.y;
  int x1 = point2.x;
  int y1 = point2.y;
  int x2 = point3.x;
  int y2 = point3.y;
  int temp;

  if (y1 < y0) {
    swap(x0, x1);
    swap(y0, y1);
  }

  if (y2 < y0) {
    swap(x0, x2);
    swap(y0, y2);
  }

  if (y2 < y1) {
    swap(x1, x2);
    swap(y1, y2);
  }

  std::vector<double> x01 = Interpolate(y0, x0, y1, x1);
  std::vector<double> x12 = Interpolate(y1, x1, y2, x2);
  std::vector<double> x02 = Interpolate(y0, x0, y2, x2);

  x01.pop_back();

  std::vector<double> x012 = x01;

  for (int i = 0; i < x12.size(); i++)
    x012.push_back(x12[i]);

  int slope = x012.size() / 2;

  std::vector<double> x_left, x_right;
  if (x02[slope] < x012[slope]) {
    x_left = x02;
    x_right = x012;
  } else {
    x_left = x012;
    x_right = x02;
  }

  for (int y = y0; y < y2; y++) {
    for (int x = x_left[y - y0]; x < x_right[y - y0]; x++) {
      canvas.plotGrid(x, y, color);
    }
  }
}

void Camera::rotate(double yaw, double roll, double pitch) {
  modifiers.rotation = modifiers.rotation + HomoCoord(yaw, roll, pitch, 1);
}

void Camera::transform(double x_val, double y_val, double z_val) {
  modifiers.translation =
      modifiers.translation + HomoCoord(x_val, y_val, z_val, 1);
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
