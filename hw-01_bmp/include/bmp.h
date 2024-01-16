#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} bmp_fileheader_t;

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_infoheader_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;
#pragma pack(pop)

typedef struct {
    pixel_t *data;
    pixel_t **pixels;
} rectangle_t;

typedef struct {
    bmp_fileheader_t fileheader;
    bmp_infoheader_t infoheader;
    rectangle_t rect;
} bmp_t;

typedef struct {
    int x;
    int y;
} point_t;

bool init_bmp_rect(bmp_t *bmp);
void init_info(bmp_t* bmp, int width, int height);
void delete_bmp(bmp_t* bmp);

bool load_bmp(FILE* file, bmp_t* dst);
int crop(bmp_t* src, bmp_t* dst, point_t start, int width, int height);
int rotate(bmp_t* src, bmp_t* dst);
void save_bmp(FILE* file, bmp_t* src);



#endif //BMP_H