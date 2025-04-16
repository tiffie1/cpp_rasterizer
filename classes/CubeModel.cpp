#include "CubeModel.h"
#include "Vector.h"
#include <string>

CubeModel::CubeModel() {}

CubeModel::CubeModel(double x_off, double y_off, double z_off, std::string color) {

  Vector position = Vector(x_off, y_off, z_off);

  Vector temp_vertices[9] = {
      Vector(1, 1, 1),    Vector(-1, 1, 1),  Vector(-1, -1, 1),
      Vector(1, -1, 1),   Vector(1, 1, -1),  Vector(-1, 1, -1),
      Vector(-1, -1, -1), Vector(1, -1, -1),
  };

  for (unsigned short i = 0; i < 9; i++) {
    Vector v = vertices[i] + position;
    vertices[i] = v;
  }

  Triangle temp_triangles[12] = {
      {0, 1, 2, color}, {0, 2, 3, color}, {4, 0, 3, color}, {4, 3, 7, color},
      {5, 4, 7, color}, {5, 7, 6, color}, {1, 5, 6, color}, {1, 6, 2, color},
      {4, 5, 1, color}, {4, 1, 0, color}, {2, 6, 7, color}, {2, 7, 3, color}};

  for (unsigned short i = 0; i < 12; i++) {
    triangles[i] = temp_triangles[i];
  }
}
