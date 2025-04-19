#include "CubeModel.h"
#include "Vector.h"

CubeModel::CubeModel() {}

CubeModel::CubeModel(double x_off, double y_off, double z_off,
                     Vector color) {

  Vector offset_vec = Vector(x_off, y_off, z_off);

  Vector temp_vertices[8] = {
      Vector(1, 1, 1),    Vector(-1, 1, 1),  Vector(-1, -1, 1),
      Vector(1, -1, 1),   Vector(1, 1, -1),  Vector(-1, 1, -1),
      Vector(-1, -1, -1), Vector(1, -1, -1),
  };

  for (unsigned short i = 0; i < 8; i++) {
    Vector v = temp_vertices[i] + offset_vec;
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

Vector CubeModel::getVertex(unsigned int i) const { return vertices[i]; }
Triangle CubeModel::getTriangle(unsigned int i) const { return triangles[i]; }

unsigned int CubeModel::getTriangleCount() const { return t_count; }
unsigned int CubeModel::getVertexCount() const { return v_count; }
