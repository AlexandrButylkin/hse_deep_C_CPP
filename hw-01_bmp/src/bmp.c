#include "bmp.h"
#include <stdlib.h>

bool init_bmp_rect(bmp_t *bmp){
    size_t width = bmp->infoheader.biWidth;
    size_t height = bmp->infoheader.biHeight;

    size_t widthSize = width * sizeof(pixel_t) + 3 & (-4);
    size_t size = widthSize * height;

    bmp->rect.data = (pixel_t*)calloc(size, sizeof(char));
    bmp->rect.pixels = (pixel_t**)calloc(height, sizeof(pixel_t*));
    //if(!bmp->rect.data || !bmp->rect.pixels)
    //    return false;

    for(int x = 0; x < height; ++x){
        char* rowPtr = (char*)bmp->rect.data + widthSize * x;
        bmp->rect.pixels[x] = (pixel_t*)rowPtr;
    }
    return true;
}

void init_info(bmp_t* bmp, int width, int height){
    bmp->infoheader.biWidth = width;
    bmp->infoheader.biHeight = height;

    size_t dstWidth = width * sizeof(pixel_t) + 3 & (-4);
    size_t dstSize = dstWidth * height;

    bmp->fileheader.bfSize = sizeof(bmp_fileheader_t) + sizeof(bmp_infoheader_t) + dstSize;
    bmp->infoheader.biSizeImage = dstSize;
}

void delete_bmp(bmp_t* bmp){
    free(bmp->rect.pixels);
    free(bmp->rect.data);
}

bool load_bmp(FILE* file, bmp_t* dst){
    fseek(file, 0, SEEK_SET);
    if( !fread(&dst->fileheader, sizeof(bmp_fileheader_t), 1, file) ||
        !fread(&dst->infoheader, sizeof(bmp_infoheader_t), 1, file))
        return false;

    if(init_bmp_rect(dst)) {
        size_t height = dst->infoheader.biHeight;
        size_t widthSize = dst->infoheader.biWidth * sizeof(pixel_t) + 3 & (-4);

        for (int y = height - 1; y >= 0; --y) {
            fread(dst->rect.pixels[y], sizeof(char), widthSize, file);
        }
        return true;
    }
    return false;
}

int crop(bmp_t* src, bmp_t* dst, point_t start, int width, int height){
    dst->fileheader = src->fileheader;
    dst->infoheader = src->infoheader;

    init_info(dst, width, height);
    if(init_bmp_rect(dst)) {
        for (int y = height + start.y - 1, yDst = 0; y >= start.y; --y, ++yDst) {
            pixel_t *srcRow = src->rect.pixels[y];
            pixel_t *dstRow = *(dst->rect.pixels + yDst);
            for (int x = start.x; x < start.x + width; ++x) {
                *(dstRow++) = *(srcRow + x);
            }
        }
        return true;
    }
    return false;
}

int rotate(bmp_t* src, bmp_t* dst){
    dst->fileheader = src->fileheader;
    dst->infoheader = src->infoheader;

    init_info(dst, src->infoheader.biHeight, src->infoheader.biWidth);
    if(init_bmp_rect(dst)) {
        for (int x = src->infoheader.biWidth - 1, xDst = 0; x >= 0; --x, ++xDst) {
            pixel_t *dstPtr = dst->rect.pixels[xDst];
            for (int y = 0; y < src->infoheader.biHeight; ++y) {
                dstPtr[y] = src->rect.pixels[y][x];
            }
        }
        return true;
    }
    return false;
}

void save_bmp(FILE* file, bmp_t* src){
    fseek(file, 0, SEEK_SET);
    fwrite(&src->fileheader, sizeof(bmp_fileheader_t), 1, file);
    fwrite(&src->infoheader, sizeof(bmp_infoheader_t), 1, file);
    fwrite(src->rect.data, sizeof(char), src->infoheader.biSizeImage, file);
}