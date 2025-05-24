#include "color.h"
#include "vec3.h"
#include <iostream>

// Entry point of the program
int main()
{

    // Image dimensions
    int image_width = 256;
    int image_height = 256;

    // Render

    // Output the PPM header (P3 format)
    // P3 means colors are in ASCII, next two numbers are width and height,
    // and the last number is the maximum color value (255)
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    // Loop over each row (from top to bottom)
    for (int j = 0; j < image_height; j++)
    {
        // Print the number of scanlines remaining for progress indication
        std::clog << "\rScanlines remaining: " << image_height - j - 1 << ' ' << std::flush;

        // Loop over each column in the current row (left to right)
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
            write_color(std::cout, pixel_color); // Write the pixel color to the output stream
        }
    }

    std::clog << "\nDone.\n"; // Indicate completion of rendering
}

// Notes:
// - Pixels are written out in rows, each row left to right.
// - Rows are written from top to bottom.
// - Each color component (r, g, b) is a real value in [0.0, 1.0], scaled to [0, 255].
// - Red goes from black to bright red left to right.
// - Green goes from black at the top to bright green at the bottom.
// - The bottom right corner will be yellow (red + green).