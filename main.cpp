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

void save_grid(Canvas &canvas, Vector **grid, unsigned short height,
               unsigned short width) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      canvas.plot(grid[x][y]);
    }
  }
}

std::vector<double> Interpolate(double start0, double end0, double start1, double end1) {
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

  DrawLine(canvas, color_grid, point0, point1, Vector(0, 0, 0));

  // print_grid(color_grid, height, width);
  save_grid(canvas, color_grid, height, width);

  // Dont forget to delete grid!
  for (int i = 0; i < height; i++)
    delete[] color_grid[i];
  delete[] color_grid;

  return 0;
}
