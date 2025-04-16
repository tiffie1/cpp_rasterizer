#ifndef HOMOCOORD_H
#define HOMOCOORD_H

#include <iostream>
#include <random>

class HomoCoord {
private:
  double iscoord;

public:
  double x, y, z;

  HomoCoord();
  HomoCoord(double x_value, double y_value, double z_value, double coord_bool);

  HomoCoord operator+(const HomoCoord &other);
  HomoCoord operator-(const HomoCoord &other);
  HomoCoord operator-() const;
  HomoCoord operator*(const double scalar);
  HomoCoord operator*(const HomoCoord &other);
  HomoCoord operator/(const double scalar);
  HomoCoord operator/(const HomoCoord &other);
  HomoCoord &operator=(const HomoCoord &other);

  double isCoord() const;

  double dot(const HomoCoord &other) const;
  double norm();
  friend std::ostream &operator<<(std::ostream &stream,
                                  const HomoCoord &vector);
};

#endif // !HOMOCOORD_H
