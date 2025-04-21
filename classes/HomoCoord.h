#ifndef HOMOCOORD_H
#define HOMOCOORD_H

#include <iostream>
#include <random>

class HomoCoord {
private:
  double coord_id;

public:
  double x, y, z;

  HomoCoord();

  // is_coord: 0 false; !0 true.
  HomoCoord(double x_value, double y_value, double z_value, double is_coord);

  inline HomoCoord operator+(const HomoCoord &other);
  inline HomoCoord operator-(const HomoCoord &other);
  inline HomoCoord operator-() const;
  inline HomoCoord operator*(const double scalar);
  inline HomoCoord operator*(const HomoCoord &other);
  inline HomoCoord operator/(const double scalar);
  inline HomoCoord operator/(const HomoCoord &other);
  inline HomoCoord &operator=(const HomoCoord &other);

  double isCoord() const;

  double dot(const HomoCoord &other) const;
  double norm();
  friend std::ostream &operator<<(std::ostream &stream,
                                  const HomoCoord &vector);
};

#endif // !HOMOCOORD_H
