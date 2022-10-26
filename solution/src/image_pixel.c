//
// Created by adgjw on 25.10.2022.
//
#include <stdint.h>
struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};
