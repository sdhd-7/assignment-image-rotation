//
// Created by sdhd on 26.10.22.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION2_BMP_H
#define ASSIGNMENT_IMAGE_ROTATION2_BMP_H
#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
#include "image_pixel.h"
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* коды других ошибок  */
};
enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image const* img );
#endif //ASSIGNMENT_IMAGE_ROTATION2_BMP_H
