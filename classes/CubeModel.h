#include <Vector.h>
#include <string>

struct Triangle {
  int id1;
  int id2;
  int id3;
  std::string color;
};

class CubeModel {
private:
  Vector vertices[9];
  Triangle triangles[12];

public:
  CubeModel();
  CubeModel(double x_val, double y_val, double z_val, std::string color_str);
};
