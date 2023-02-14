#ifndef PICTURE_IO_H_
#define PICTURE_IO_H_

int write_jpg(char const *filename, int x, int y, int comp, const void *data, int quality);

unsigned char* read_jpg(char const *filename, int* width, int* height, int* n);

#endif