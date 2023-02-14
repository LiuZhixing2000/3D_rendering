#include "picture_io.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

int write_jpg(char const *filename, int x, int y, int comp, const void *data, int quality){
    return stbi_write_jpg(filename, x, y, comp, data, quality);
}

unsigned char* read_jpg(char const *filename, int* width, int* height, int* n){
    unsigned char* data = stbi_load(filename, width, height, n, 0);
    return data;
}