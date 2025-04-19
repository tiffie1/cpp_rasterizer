#include "Triangle.h"
#include "Vector.h"
#include <string>

// TODO: Make parent class.
//
class CubeModel {
private:
  Vector vertices[8];
  Triangle triangles[12];

  const unsigned int v_count = 8;
  const unsigned int t_count = 12;
public:
  CubeModel();
  CubeModel(double x_offset, double y_offset, double z_offset, Vector color);

  Vector getVertex(unsigned int index) const;
  Triangle getTriangle(unsigned int index) const;

  unsigned int getVertexCount() const; // Universal attribute.
  unsigned int getTriangleCount() const; // Universal attribute.
};
