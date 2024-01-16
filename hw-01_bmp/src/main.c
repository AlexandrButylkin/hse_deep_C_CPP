#include "bmp.h"
#include "stego.h"
#include <string.h>
#include <stdlib.h>

#define ARG_ERROR 1;
#define FILE_ERROR 2;
#define LOAD_ERROR 3;
#define CROP_ERROR 4;
#define ROTATE_ERROR 5;

int main(int argc, char** argv) {

    int isError = 0;
    if (argc < 5)
        return ARG_ERROR;

    char* command = argv[1];

    if (strcmp(command, "crop-rotate") == 0) {
        if (argc < 7){
            isError = ARG_ERROR;
            return isError;
        }
        char *pathInput = argv[2];
        char *pathOutput = argv[3];
        point_t point = {atoi(argv[4]), atoi(argv[5])};
        int width = atoi(argv[6]);
        int height = atoi(argv[7]);

        FILE *fileInput = fopen(pathInput, "rb");

        if (fileInput) {
            bmp_t bmp_load;
            if (load_bmp(fileInput, &bmp_load)) {

                if( point.x > bmp_load.infoheader.biWidth ||
                    point.y > bmp_load.infoheader.biHeight ||
                    point.x + width > bmp_load.infoheader.biWidth ||
                    point.y + height > bmp_load.infoheader.biHeight ||
                    width < 1 || height < 1)
                {
                    isError = ARG_ERROR;
                }
                bmp_t bmp_crop;
                if (crop(&bmp_load, &bmp_crop, point, width, height)) {
                    bmp_t bmp_rotate;
                    if (rotate(&bmp_crop, &bmp_rotate)) {
                        FILE *fileOutput = fopen(pathOutput, "wb");
                        save_bmp(fileOutput, &bmp_rotate);
                        fclose(fileOutput);
                    } else isError = ROTATE_ERROR;
                    delete_bmp(&bmp_rotate);
                } else isError = CROP_ERROR;
                delete_bmp(&bmp_crop);
            }
            else isError = LOAD_ERROR;
            delete_bmp(&bmp_load);
        }
        else isError = FILE_ERROR;
        fclose(fileInput);

        return isError;
    }
    else if(strcmp(command, "insert") == 0) {

        if (argc < 6)
            return ARG_ERROR;

        char* pathInput = argv[2];
        char* pathOutput = argv[3];
        char* pathKey = argv[4];
        char* pathMessage = argv[5];

        FILE* inpFile = fopen(pathInput, "rb");
        FILE* outFile = fopen(pathOutput, "wb");
        FILE* keyFile = fopen(pathKey, "r");
        FILE* msgFile = fopen(pathMessage , "r");

        if(inpFile && outFile && keyFile && msgFile){
            bmp_t bmp;
            if(load_bmp(inpFile, & bmp)) {
                code_message(keyFile, &bmp, msgFile);
                save_bmp(outFile, &bmp);
            }
            else isError = LOAD_ERROR;
            delete_bmp(&bmp);
        }
        else isError = FILE_ERROR;
        fclose(inpFile);
        fclose(outFile);
        fclose(keyFile);
        fclose(msgFile);

        return isError;
    }
    else if(strcmp(command, "extract") == 0) {

        char* pathInput = argv[2];
        char* pathKey = argv[3];
        char* pathMessage = argv[4];

        FILE* inpFile = fopen(pathInput, "rb");
        FILE* keyFile = fopen(pathKey, "r");
        FILE* msgFile = fopen(pathMessage , "w");

        if(inpFile && keyFile && msgFile){
            bmp_t bmp;
            if(load_bmp(inpFile, & bmp)){
                decode_message(keyFile, msgFile, &bmp);
            }
            else isError = LOAD_ERROR;
            delete_bmp(&bmp);
        }
        else isError = FILE_ERROR;
        fclose(inpFile);
        fclose(keyFile);
        fclose(msgFile);
    }
    else isError = ARG_ERROR;

    return isError;
}