//
// Created by adgjw on 25.10.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_PIXEL_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_PIXEL_H
#include <stdint.h>
struct pixel { uint8_t b, g, r; };
struct image {
    uint64_t width, height;
    struct pixel* data;
};

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_PIXEL_H
