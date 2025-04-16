#ifndef CANVAS_H
#define CANVAS_H

#include "Vector.h"
#include "Point.h"
#include <fstream>
#include <string>

class Canvas {
private:
  std::ofstream stream;
  std::string name;
  unsigned short width, height;
  Vector **grid;
  Vector bg;

public:
  Canvas();
  Canvas(std::string file_name, unsigned short width, unsigned short height);
  Canvas(std::string file_name, unsigned short width, unsigned short height,
         Vector bg_color);
  ~Canvas();

  unsigned short getWidth() const;
  unsigned short getHeight() const;
  std::string getName() const;
  void setName(std::string new_name);
  void setBackgroundColor(Vector new_bg);

  void close();
  void open();
  void plotGrid(int x, int y, Vector color);
  void plot(Vector color);

  void operator<<(const std::string message);

  friend void print_grid(Canvas &canvas);
  void save_grid();
};

#endif // !CANVAS_H
