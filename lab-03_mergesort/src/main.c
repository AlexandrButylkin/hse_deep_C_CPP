#include "mergesort.h"
#include "string.h"
#include <stdio.h>
#include "stdlib.h"

int int_gt_comparator(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int char_gt_comparator(const void *a, const void *b) {
    return *(char*)b - *(char*)a;
}

int str_gt_comparator(const void *a, const void *b) {
    char* str1 = *(char**) a;
    char* str2 = *(char** ) b;
    unsigned long long size1 = strlen(str1);
    unsigned long long size2 = strlen(str2);
    unsigned long long size = size1 <= size2 ? size1 : size2;
    for(unsigned long long i = 0; i < size ; ++i){
        if(str1[i] != str2[i])
            return str2[i] - str1[i];
    }
    return size2 - size1;
}

void PrintData(void* data, char* type, unsigned long long size){
    if(strcmp(type, "int") == 0){
        int* dataInt = (int*) data;
        for(unsigned long long i = 0; i < size; ++i){
            if(i != 0)
                printf(" ");
            printf("%d", *(dataInt + i));
        }
    } else if (strcmp(type, "char") == 0){
        char* dataChar = (char*) data;
        for(unsigned long long i = 0; i < size; ++i){
            if(i != 0)
                printf(" ");
            printf("%c", *(dataChar + i));
        }
    } else {
        char** dataStr = (char**) data;
        for(unsigned long long i = 0; i < size; ++i){
            if(i != 0)
                printf(" ");
            printf("%s", *(dataStr + i));
        }
    }
    printf("\n");
}

void* GetData(int argc, char** argv){
    char* type = argv[1];

    if(strcmp(type, "int") == 0){
        int* data = (int*) malloc(sizeof(int) * (argc - 2));
        for(int i = 2, j = 0; i < argc, j < argc - 2; ++i, ++j) {
            *(data + j) = atoi(argv[i]);
        }
        return (void*) data;
    } else if (strcmp(type, "char") == 0){
        char* data = (char*) malloc(sizeof(char) * (argc - 2));
        for(int i = 2, j = 0; i < argc, j < argc - 2; ++i, ++j)
            *(data + j) = *argv[i];
        return (void*) data;
    } else {
        char** data = (char**) malloc(sizeof(char*) * (argc - 2));
        for(int i = 2, j = 0; i < argc, j < argc - 2; ++i, ++j)
            *(data + j) = argv[i];
        return (void*) data;
    }

}

int main(int argc, char** argv)
{
    if(argc < 2) return 0;

    char* type = argv[1];
    void* data = GetData(argc, argv);

    int error = 0;

    if(strcmp(type, "int") == 0){
        error = mergesort((void *)data, argc - 2, sizeof(int), int_gt_comparator);
    } else if (strcmp(type, "char") == 0){
        error = mergesort(data, argc - 2, sizeof(char), char_gt_comparator);
    } else {
        error = mergesort(data, argc - 2, sizeof(char*), str_gt_comparator);
    }

    if(error){
        free(data);
        return -1;
    }

    PrintData(data, type, argc - 2);
    free(data);
    return 0;
}

