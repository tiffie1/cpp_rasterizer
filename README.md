# Simple C++ Rasterizer ⬛️⬜️

This is a rasterizer made in C++ that implements the following:  
- Interpolation for rendering of lines
- Rendering of triangles
- Rendering of filled triangles
- Cube model and rendering of model
- Support for homogeneous coordinates
- Transformation and rotation of camera and models, with support for scaling on models
- Clipping

## Compiling
To compile the `main.cpp` file, use the compiler of
your choice (GNU's gcc is recommended).   

Example:
```bash
g++ main.cpp ./classes/*.cpp -o exec && ./exec
```
Note that compiling the header implementations is required. 

Showcase of most recent render:

![Line](first.png)
