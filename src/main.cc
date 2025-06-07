#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

//returns lerp blue to white
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

// Entry point of the program
int main()
{
    //Aspect ratio
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // Ensure height is at least 1

    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera
    auto focal_length = 1.0; // Focal length of the camera
    auto viewport_height = 2.0; // Height of the viewport
    auto viewport_width = viewport_height * (double(image_width) / image_height); // Width based on aspect ratio
    auto camera_center = point3(0, 0, 0); // Camera position at the origin

    //calculate vectors across horizontal and vertical directions
    auto viewport_u = vec3(viewport_width, 0, 0); // Horizontal vector across the viewport
    auto viewport_v = vec3(0, -viewport_height, 0); // Vertical vector across the viewport

    //Calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    //Calculate location of upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

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
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
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