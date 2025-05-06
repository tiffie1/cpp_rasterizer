#include "CubeModel.h"
#include "HomoCoord.h"


CubeModel::CubeModel(double x_off, double y_off, double z_off,
                     HomoCoord color) {

  HomoCoord offset_vec = HomoCoord(x_off, y_off, z_off, 1);

  HomoCoord temp_vertices[8] = {
      HomoCoord(1, 1, 1, 1),    HomoCoord(-1, 1, 1, 1),  HomoCoord(-1, -1, 1, 1),
      HomoCoord(1, -1, 1, 1),   HomoCoord(1, 1, -1, 1),  HomoCoord(-1, 1, -1, 1),
      HomoCoord(-1, -1, -1, 1), HomoCoord(1, -1, -1, 1),
  };

  for (unsigned short i = 0; i < 8; i++) {
    HomoCoord v = temp_vertices[i] + offset_vec;
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

CubeModel::CubeModel() {
  *this = CubeModel(0, 0, 0, HomoCoord(0, 0, 0, 1));
}

HomoCoord CubeModel::getVertex(unsigned int i) const { return vertices[i]; }
Triangle CubeModel::getTriangle(unsigned int i) const { return triangles[i]; }

unsigned int CubeModel::getTriangleCount() const { return t_count; }
unsigned int CubeModel::getVertexCount() const { return v_count; }

inline CubeModel &CubeModel::operator=(const CubeModel &other) {
  if (this != &other) {
    for (int i = 0; i < other.getTriangleCount(); i++) {
      triangles[i] = other.getTriangle(i);
    }

    for (int i = 0; i < other.getVertexCount(); i++) {
      vertices[i] = other.getVertex(i);
    }
  }

  return *this;
}

void CubeModel::transform(double x_val, double y_val, double z_val) {
  for (int i = 0; i < v_count; i++) {
    
  }
}
