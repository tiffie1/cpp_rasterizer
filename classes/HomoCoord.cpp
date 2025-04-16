// FIX LATER

#include "HomoCoord.h"

HomoCoord::HomoCoord() {
  x = 0;
  x = 0;
  x = 0;
  iscoord = false;
}

HomoCoord::HomoCoord(double x_value, double y_value, double z_value, double coord_bool) {
  x = x_value;
  y = y_value;
  z = z_value;
  iscoord = coord_bool;
}

HomoCoord HomoCoord::operator-() const { return HomoCoord(-x, -y, -z, -iscoord); }

HomoCoord HomoCoord::operator+(const HomoCoord &other) {
  return HomoCoord(x + other.x, y + other.y, z + other.z, iscoord + other.iscoord);
}

HomoCoord HomoCoord::operator-(const HomoCoord &other) {
  return *this + -(other);
  //return HomoCoord(x - other.x, y - other.y, z - other.z, iscoord - other.iscoord);
}

HomoCoord HomoCoord::operator/(const HomoCoord &other) {
  return HomoCoord(x / other.x, y / other.y, z / other.z);
}

HomoCoord HomoCoord::operator*(const HomoCoord &other) {
  return HomoCoord(x * other.x, y * other.y, z * other.z);
}

HomoCoord HomoCoord::operator/(const double &scalar) {
  return HomoCoord(x / scalar, y / scalar, z / scalar);
}

HomoCoord HomoCoord::operator*(const double &scalar) {
  return HomoCoord(x * scalar, y * scalar, z * scalar);
}


HomoCoord &HomoCoord::operator=(const HomoCoord &other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
    z = other.z;
  }

  return *this;
}

double HomoCoord::dot(const HomoCoord &other) const {
  return x * other.x + y * other.y + z * other.z;
}

double HomoCoord::norm() { return sqrt(x * x + y * y + z * z); }

std::ostream &operator<<(std::ostream &stream,
                                        const HomoCoord &vector) {
  stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return stream;
}
