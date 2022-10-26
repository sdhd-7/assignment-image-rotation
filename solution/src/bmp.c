//
// Created by adgjw on 24.10.2022.
//
#include "image_pixel.h"
#include  <stdint.h>
#include  <stdio.h>
#include  <stdlib.h>


#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};
#pragma pack(pop)

/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* коды других ошибок  */
};

enum read_status from_bmp( FILE* in, struct image* img ){
    struct bmp_header tmp;
    size_t count = fread(&tmp, 1, sizeof(struct bmp_header), in);
    if(count != sizeof(struct bmp_header))
        return READ_INVALID_HEADER;
    img->width=tmp.biWidth;
    img->height=tmp.biHeight;
    img->data=malloc(sizeof(struct pixel*) * img->height*img->width);
    size_t pass = 0;
    for(int i = 0; i < img->height;++i){
        count = fread(&img->data[i*img->width], sizeof(struct pixel), img->width, in);
        if(count != img->width)
            return READ_INVALID_BITS;
        pass = (4 - (count*sizeof(struct pixel)) % 4) % 4;
        //printf("*%zu\n", pass);
        fseek(in, (long)pass, 1);
    }
    return READ_OK;
}

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

enum write_status to_bmp( FILE* out, struct image const* img ){
    size_t pass = (4 - (img->width* sizeof(struct pixel))%4)%4;
    struct bmp_header tmp;
    tmp.biHeight=img->height;
    tmp.biWidth=img->width;
    tmp.bfType=19778;
    tmp.bfileSize = sizeof(struct bmp_header) + img->height*(img->width*sizeof(struct pixel) + pass);
    tmp.bfReserved = 0;
    tmp.bOffBits=54;
    tmp.biSize=40;
    tmp.biPlanes=1;
    tmp.biBitCount=24;
    tmp.biCompression=0;
    tmp.biSizeImage=tmp.bfileSize-tmp.bOffBits;
    tmp.biXPelsPerMeter=0;
    tmp.biYPelsPerMeter=0;
    tmp.biClrUsed=0;
    tmp.biClrImportant=0;
    uint8_t z = 0;
    size_t count = fwrite(&tmp, 1, sizeof(struct bmp_header), out);
    if(count != sizeof(struct bmp_header))
        return WRITE_ERROR;
    for(int i = 0; i < img->height;++i){
        count = fwrite(&img->data[i*img->width], 1, img->width*sizeof(struct pixel), out);
        if(count!=img->width*sizeof(struct pixel))
            return WRITE_ERROR;
        for(int j = 0; j < pass; ++j)
            fwrite(&z, sizeof(uint8_t), 1, out);
    }
    return WRITE_OK;
}
