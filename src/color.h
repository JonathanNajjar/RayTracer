// color.h - Utility functions for color output in ray tracing
#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "vec3.h"   // For the color = vec3 alias

// Alias for vec3 to represent RGB color
using color = vec3;

// Write the translated [0,1] RGB color to the output stream in PPM format
// Each color component is scaled to [0,255] and written as an integer
// Example output: "128 200 255\n"
void write_color(std::ostream& out, const color& pixel_color)
{
    // Extract RGB components from the color
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Convert to [0,255] integer values
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write the color to the output stream in PPM format
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif