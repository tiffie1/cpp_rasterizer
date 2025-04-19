#include "Canvas.h"
#include <iostream>

Canvas::Canvas() {
  name = "";
  width = 0;
  height = 0;
  grid = nullptr;
}

Canvas::Canvas(std::string file_name, unsigned short canvas_width,
               unsigned short canvas_height) {
  name = file_name;
  width = canvas_width;
  height = canvas_height;
  stream.open(name);

  stream << "P3 \n" << width << " " << height << "\n255\n"; // Header info.

  // Allocate memory for color grid.
  grid = new Vector *[height];
  for (int i = 0; i < height; i++)
    grid[i] = new Vector[width];

  setBackgroundColor(Vector(255, 255, 255));
}

Canvas::~Canvas() {
  if (stream.is_open())
    stream.close();

  for (int i = 0; i < height; i++)
    delete[] grid[i];
  delete[] grid;

}

unsigned short Canvas::getWidth() const { return width; }
unsigned short Canvas::getHeight() const { return height; }
std::string Canvas::getName() const { return name; }

void Canvas::setName(std::string new_name) {
  stream.close();
  name = new_name;
  stream.open(new_name);

  stream << "P3 \n" << width << " " << height << "\n255\n";
}

void Canvas::setBackgroundColor(Vector new_bg) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      grid[i][j] = new_bg; 
    }
  }
}

void Canvas::close() {
  if (stream.is_open())
    stream.close();
}
void Canvas::open() {
  if (!stream.is_open())
    stream.open(name);
}

void Canvas::operator<<(const std::string message) {
  if (!stream.is_open()) {
    stream.open(name);
  }

  stream << message;
}

void print_grid(Canvas &canvas) {
  for (int i = 0; i < canvas.height; i++) {
    for (int j = 0; j < canvas.width; j++) {
      std::cout << canvas.grid[i][j] << std::endl;
    }
    std::cout << std::endl;
  }
}

void Canvas::save_grid() {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      plot(grid[x][y]);
    }
  }
}

void Canvas::plot(Vector color) {
  stream << color.x << " " << color.y << " " << color.z << " \n";
}

void Canvas::plotGrid(int x, int y, Vector color) {
  std::cout << "xy: " << x << " " << y << " " << std::endl;
  // Avoid plotting if coord out of range of matrix.
  if (x >= 0 && y >= 0 && x < width && y < height)
    grid[x][y] = color;

  else
   std::cout << "Not doing." << std::endl;
}
