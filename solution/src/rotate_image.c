//
// Created by adgjw on 25.10.2022.
//
#include "image_pixel.h"
#include <stdlib.h>
struct image rotate( struct image const source ){
    struct image tmp;
    tmp.height=source.width;
    tmp.width=source.height;

    tmp.data=malloc(sizeof(struct pixel)*tmp.height*tmp.width);
    for(int i = 0; i < source.height;++i)
        for(int j = 0; j < source.width;++j) {
            tmp.data[source.height * (source.width - j - 1) + i] = source.data[i * source.width + j];
            //tmp.data[source.width * i + j] = source.data[i * source.width + j];
        }
    free(source.data);
    return tmp;
}
