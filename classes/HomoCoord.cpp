#include "HomoCoord.h"

bool xnor(bool statement1, bool statement2) {
  return !((statement1 && (!statement2)) || ((!statement1) && statement2));
}

HomoCoord::HomoCoord() {
  x = 0;
  y = 0;
  z = 0;
  coord_id = 1;
}

HomoCoord::HomoCoord(double x_value, double y_value, double z_value,
                     double coord_bool) {
  x = x_value;
  y = y_value;
  z = z_value;
  coord_id = coord_bool;
}

HomoCoord HomoCoord::operator-() const {
  return HomoCoord(-x, -y, -z, -coord_id);
}

HomoCoord HomoCoord::operator+(const HomoCoord &other) {
  // If both HomoCoord are the same type, add id.
  // Else, operation is a vector transpose.
  if (xnor(coord_id != 0, other.coord_id != 0))
    return HomoCoord(x + other.x, y + other.y, z + other.z,
                     coord_id + other.coord_id);
  else
    return HomoCoord(x + other.x, y + other.y, z + other.z, 0);
}

HomoCoord HomoCoord::operator-(const HomoCoord &other) {
  // If both coordinates, turn into vector.
  // Else, standard addition.
  if (coord_id != 0 && other.coord_id != 0)
    return HomoCoord(x - other.x, y - other.y, z - other.z, 0);
  else
    return *this + -other;
}

HomoCoord HomoCoord::operator*(const double scalar) {
  return HomoCoord(x * scalar, y * scalar, z * scalar, coord_id * scalar);
}

HomoCoord HomoCoord::operator/(const double scalar) {
  return HomoCoord(x / scalar, y / scalar, z / scalar, coord_id / scalar);
}

HomoCoord HomoCoord::operator*(const HomoCoord &other) {
  return HomoCoord(x * other.x, y * other.y, z * other.z,
                   coord_id * other.coord_id);
}

HomoCoord HomoCoord::operator/(const HomoCoord &other) {
  if (coord_id == 0 || other.coord_id == 0)
    return HomoCoord(x / other.x, y / other.y, z / other.z, 0);
  else
    return HomoCoord(x / other.x, y / other.y, z / other.z,
                     coord_id / other.coord_id);
}

HomoCoord &HomoCoord::operator=(const HomoCoord &other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    coord_id = other.coord_id;
  }

  return *this;
}

double HomoCoord::dot(const HomoCoord &other) const {
  return x * other.x + y * other.y + z * other.z + coord_id * other.coord_id;
}

double HomoCoord::norm() { return sqrt(x * x + y * y + z * z); }

bool HomoCoord::isCoord() const {
  if (coord_id == 0)
    return false;
  else
    return true;
}

std::ostream &operator<<(std::ostream &stream, const HomoCoord &value) {
  if (value.coord_id == 0)
    stream << "{" << value.x << ", " << value.y << ", " << value.z << "}";
  else
    stream << "(" << value.x << ", " << value.y << ", " << value.z << ")";

  return stream;
}

