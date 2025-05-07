#include "CubeModel.h"
#include "HomoCoord.h"

CubeModel::CubeModel(HomoCoord color) {
  modifiers.rotation = HomoCoord();
  modifiers.scale = HomoCoord(1, 1, 1, 1);
  modifiers.translation = HomoCoord();

  HomoCoord temp_vertices[8] = {
      HomoCoord(1, 1, 1, 1),    HomoCoord(-1, 1, 1, 1),
      HomoCoord(-1, -1, 1, 1),  HomoCoord(1, -1, 1, 1),
      HomoCoord(1, 1, -1, 1),   HomoCoord(-1, 1, -1, 1),
      HomoCoord(-1, -1, -1, 1), HomoCoord(1, -1, -1, 1),
  };

  for (unsigned short i = 0; i < 8; i++) {
    vertices[i] = temp_vertices[i];
  }

  Triangle temp_triangles[12] = {
      {0, 1, 2, color}, {0, 2, 3, color}, {4, 0, 3, color}, {4, 3, 7, color},
      {5, 4, 7, color}, {5, 7, 6, color}, {1, 5, 6, color}, {1, 6, 2, color},
      {4, 5, 1, color}, {4, 1, 0, color}, {2, 6, 7, color}, {2, 7, 3, color}};

  for (unsigned short i = 0; i < 12; i++) {
    triangles[i] = temp_triangles[i];
  }
}

CubeModel::CubeModel() { *this = CubeModel(HomoCoord(0, 0, 0, 1)); }

HomoCoord CubeModel::getVertex(unsigned int i) const { return vertices[i]; }
Triangle CubeModel::getTriangle(unsigned int i) const { return triangles[i]; }

unsigned int CubeModel::getTriangleCount() const { return t_count; }
unsigned int CubeModel::getVertexCount() const { return v_count; }

HomoCoord CubeModel::getScaleModifier() const { return modifiers.scale; }
HomoCoord CubeModel::getRotationModifier() const { return modifiers.rotation; }
HomoCoord CubeModel::getTranslationModifier() const {
  return modifiers.translation;
}

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

void CubeModel::scale(double x_val, double y_val, double z_val) {
  if (x_val == 1) x_val = 0;
  if (y_val == 1) y_val = 0;
  if (z_val == 1) z_val = 0;

  modifiers.scale = modifiers.scale + HomoCoord(x_val, y_val, z_val, 1);
}

void CubeModel::rotate(double yaw, double roll, double pitch) {
  modifiers.rotation = modifiers.rotation + HomoCoord(yaw, roll, pitch, 1);
}

void CubeModel::transform(double x_val, double y_val, double z_val) {
  modifiers.translation =
      modifiers.translation + HomoCoord(x_val, y_val, z_val, 1);
}
