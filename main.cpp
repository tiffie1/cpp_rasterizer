#include "classes/Canvas.h"
#include "classes/Scene.h"
#include <classes/Vector.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Point {
  int x;
  int y;
};

void print_grid(Vector **grid, unsigned short height, unsigned short width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << grid[i][j] << std::endl;
    }
    std::cout << std::endl;
  }
}

void print_vector(std::vector<double> vector) {
  std::cout << "(";
  for (int i = 0; i < vector.size(); i++) {
    std::cout << vector[i] << ", ";
  }
  std::cout << ")\n";
}

void save_grid(Canvas &canvas, Vector **grid, unsigned short height,
               unsigned short width) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      canvas.plot(grid[x][y]);
    }
  }
}

std::vector<double> Interpolate(double start0, double end0, double start1,
                                double end1) {
  std::vector<double> calculated_values;

  if (start0 == start1) {
    calculated_values.push_back(end0);
    return calculated_values;
  }

  double slope = (end1 - end0) / (start1 - start0);
  double displacement = end0;

  for (int i = start0; i <= start1; i++) {
    calculated_values.push_back(displacement);
    displacement += slope;
  }

  return calculated_values;
}

void DrawLine(Canvas &canvas, Vector **grid, Point point0, Point point1,
              Vector color) {
  int x0 = static_cast<int>(point0.x);
  int y0 = static_cast<int>(point0.y);
  int x1 = static_cast<int>(point1.x);
  int y1 = static_cast<int>(point1.y);
  int temp;

  if (abs(x1 - x0) > abs(y1 - y0)) {
    if (x0 > x1) {
      temp = x0;
      x0 = x1;
      x1 = temp;

      temp = y0;
      y0 = y1;
      y1 = temp;
    }

    std::vector<double> ys = Interpolate(x0, y0, x1, y1);
    for (int x = x0; x < x1; x++) {
      grid[x][static_cast<int>(ys[x - x0])] = color;
    }
  }

  else {
    if (y0 > y1) {
      temp = x0;
      x0 = x1;
      x1 = temp;

      temp = y0;
      y0 = y1;
      y1 = temp;
    }

    std::vector<double> xs = Interpolate(y0, x0, y1, x1);

    for (int y = y0; y < y1; y++) {
      grid[static_cast<int>(xs[y - y0])][y] = color;
    }
  }
}

void DrawPoint(Canvas &canvas, Vector **grid, Point point, Vector color) {
  grid[point.x][point.y] = color;
}

std::vector<int> ViewportToCanvas(Canvas &canvas, int x, int y) {
  std::vector<int> result = {(x * canvas.getWidth() / canvas.getV_Width()),
                             (y * canvas.getHeight() / canvas.getV_Height())};
  return result;
}

std::vector<int> ProjectVertex(Canvas &canvas, Point point) {
  return ViewportToCanvas(canvas, point.x, point.y);
}

void DrawWireframeTriangle(Canvas &canvas, Vector **grid, Point point0,
                           Point point1, Point point2, Vector color) {
  DrawLine(canvas, grid, point0, point1, color);
  DrawLine(canvas, grid, point1, point2, color);
  DrawLine(canvas, grid, point2, point0, color);
}

void DrawFilledTriangle(Canvas &canvas, Vector **grid, Point point0,
                        Point point1, Point point2, Vector color) {
  int x0 = static_cast<int>(point0.x);
  int y0 = static_cast<int>(point0.y);
  int x1 = static_cast<int>(point1.x);
  int y1 = static_cast<int>(point1.y);
  int x2 = static_cast<int>(point2.x);
  int y2 = static_cast<int>(point2.y);
  int temp;

  if (y1 < y0) {
    temp = x0;
    x0 = x1;
    x1 = temp;

    temp = y0;
    y0 = y1;
    y1 = temp;
  }
  if (y2 < y0) {
    temp = x0;
    x0 = x2;
    x2 = temp;

    temp = y0;
    y0 = y2;
    y2 = temp;
  }
  if (y2 < y1) {
    temp = x1;
    x1 = x2;
    x2 = temp;

    temp = y1;
    y1 = y2;
    y2 = temp;
  }

  std::cout << x0 << " " << y0 << std::endl;
  std::cout << x1 << " " << y1 << std::endl;
  std::cout << x2 << " " << y2 << std::endl;

  std::vector<double> x01 = Interpolate(y0, x0, y1, x1);
  std::vector<double> x12 = Interpolate(y1, x1, y2, x2);
  std::vector<double> x02 = Interpolate(y0, x0, y2, x2);

  x01.pop_back();

  print_vector(x01);
  print_vector(x12);
  print_vector(x02);

  std::vector<double> x012 = x01;

  for (int i = 0; i < x12.size(); i++) {
    double element = x12.front();
    x12.pop_back();
    x012.push_back(element);
  }

  int slope = x012.size() / 2;

  std::vector<double> x_left, x_right;
  if (x02[slope] < x012[slope]) {
    x_left = x02;
    x_right = x012;
  } else {
    x_left = x012;
    x_right = x02;
  }

  for (int y = y0; y < y2; y++) {
    for (int x = x_left[y - y0]; x < x_right[y - y0]; x++) {
      std::cout << x << " " << y << "   ";

      grid[x][y] = color;
    }
  }
}

int main() {
  Scene scene(Vector(255, 255, 255));
  Canvas canvas("first.ppm", 100, 100, 1, 1, 1);

  unsigned short height = canvas.getHeight();
  unsigned short width = canvas.getWidth();

  Vector **color_grid = new Vector *[height];
  for (int i = 0; i < height; i++)
    color_grid[i] = new Vector[width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      color_grid[i][j] = scene.getBackgroundColor();
    }
  }

  Point point0 = {1, 1};
  Point point1 = {50, 70};

  // DrawLine(canvas, color_grid, point0, point1, Vector(0, 0, 0));
  //  print_grid(color_grid, height, width);

  Vector red = Vector(255, 0, 0);

  DrawWireframeTriangle(canvas, color_grid, {1, 1}, {50, 70}, {50, 1},
                     Vector(0, 0, 0));
  DrawPoint(canvas, color_grid, {1, 1}, red);
  DrawPoint(canvas, color_grid, {50, 70}, red);
  DrawPoint(canvas, color_grid, {50, 1}, red);

  save_grid(canvas, color_grid, height, width);

  // Dont forget to delete grid!
  for (int i = 0; i < height; i++)
    delete[] color_grid[i];
  delete[] color_grid;

  return 0;
}
