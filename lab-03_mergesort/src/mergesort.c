#include "mergesort.h"
#include <stdlib.h>

void CopyBytes(char* dest, char* src, unsigned long long element_size){
    for(unsigned long long i = 0; i < element_size; ++i) {
        *(dest + i) = *(src + i);
    }
}

int Merge(char* arrayStart, char* arrayMid, char* arrayEnd,
           unsigned long long element_size, int (*comparator)(const void *, const void *)){

    unsigned long long size = arrayEnd - arrayStart;
    char* sortedArray = (char*) malloc(size * sizeof(char));
    if(sortedArray) {
        char *temp = sortedArray;

        char *firstPtr = arrayStart;
        char *secondPtr = arrayMid;

        while (firstPtr != arrayMid || secondPtr != arrayEnd) {
            if (firstPtr < arrayMid && secondPtr < arrayEnd) {
                if (comparator((void *) firstPtr, (void *) secondPtr) >= 0) {
                    CopyBytes(temp, firstPtr, element_size);
                    firstPtr += element_size;
                } else {
                    CopyBytes(temp, secondPtr, element_size);
                    secondPtr += element_size;
                }
            } else if (firstPtr < arrayMid) {
                CopyBytes(temp, firstPtr, element_size);
                firstPtr += element_size;
            } else {
                CopyBytes(temp, secondPtr, element_size);
                secondPtr += element_size;
            }
            temp += element_size;
        }

        for (unsigned long long i = 0; i < size; ++i) {
            *(arrayStart + i) = *(sortedArray + i);
        }
        free(sortedArray);
        return 0;
    } else {
        return -1;
    }

}

int MergeSort(char* start, char* end, unsigned long long element_size,  int (*comparator)(const void *, const void *)){
    unsigned long long itemsCount = (end - start) / element_size;
    if(itemsCount < 2){
        return 0;
    }
    char* mid = start + (itemsCount / 2) * element_size;
    if (MergeSort(start, mid, element_size, comparator) == -1){
        return -1;
    }
    if (MergeSort(mid, end, element_size, comparator) == -1) {
        return -1;
    }
    if (Merge(start, mid, end, element_size, comparator)){
        return -1;
    }
}

int mergesort( void *array,
                unsigned long long elements, unsigned long long element_size,
                int (*comparator)(const void *, const void *)){
    char* start = (char*) array;
    char* end = start + element_size * elements;
    return MergeSort(start, end, element_size, comparator);
}