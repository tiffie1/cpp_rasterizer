#include "HomoCoord.h"
#include "Triangle.h"
#include <string>
#include <vector>

// TODO: Make parent class.
//
class CubeModel {
private:
  std::vector<HomoCoord> vertices;
  std::vector<Triangle> triangles;

  struct {
    HomoCoord scale;
    HomoCoord rotation;
    HomoCoord translation;
  } modifiers;

  const unsigned int v_count = 8;
  const unsigned int t_count = 12;

public:
  CubeModel();
  CubeModel(HomoCoord color);

  HomoCoord getVertex(unsigned int index) const;
  Triangle getTriangle(unsigned int index) const;

  unsigned int getVertexCount() const;   // Universal attribute.
  unsigned int getTriangleCount() const; // Universal attribute.
  HomoCoord getVertexArray() const;
  HomoCoord getScaleModifier() const;
  HomoCoord getRotationModifier() const;
  HomoCoord getTranslationModifier() const;
  int addVertex(HomoCoord vertex);
  void addTriangle(Triangle triangle);

  CubeModel &operator=(const CubeModel &other);

  void scale(double x_val, double y_val, double z_val);     // I_s.
  void rotate(double yaw, double roll, double pitch);     // I_r.
  void transform(double x_val, double y_val, double z_val); // I_t.
};
