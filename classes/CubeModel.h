#include "Triangle.h"
#include "HomoCoord.h"
#include <string>

// TODO: Make parent class.
//
class CubeModel {
private:
  HomoCoord vertices[8];
  Triangle triangles[12];

  const unsigned int v_count = 8;
  const unsigned int t_count = 12;
public:
  CubeModel();
  CubeModel(double x_offset, double y_offset, double z_offset, HomoCoord color);

  HomoCoord getVertex(unsigned int index) const;
  Triangle getTriangle(unsigned int index) const;

  unsigned int getVertexCount() const; // Universal attribute.
  unsigned int getTriangleCount() const; // Universal attribute.
  HomoCoord getVertexArray() const;

  inline CubeModel &operator=(const CubeModel &other);
  
  void scale(double x_val, double y_val, double z_val); // I_s.
  void rotation(double pitch, double yaw, double roll); // I_r.
  void transform(double x_val, double y_val, double z_val); // I_t.
};
