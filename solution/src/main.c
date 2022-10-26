#include "bmp.h"
#include "rotate_image.h"
#include <stdio.h>
int main( int argc, char** argv ) {
    (void) argc; (void) argv; // suppress 'unused parameters' warning
    struct image img;
    FILE* in = fopen(argv[1], "rb");
    enum read_status rd = from_bmp(in, &img);
    fclose(in);
    printf("%u", rd);
    for(int i = 0; i < 3;++i)
        img = rotate(img);
    FILE * out = fopen(argv[2], "wb");
    enum write_status wr = to_bmp(out, &img);
    printf("%u", wr);
    fclose(out);
    return 0;
}
