#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    cam.render(world);
}

// Notes:
// - Pixels are written out in rows, each row left to right.
// - Rows are written from top to bottom.
// - Each color component (r, g, b) is a real value in [0.0, 1.0], scaled to [0, 255].
// - Red goes from black to bright red left to right.
// - Green goes from black at the top to bright green at the bottom.
// - The bottom right corner will be yellow (red + green).