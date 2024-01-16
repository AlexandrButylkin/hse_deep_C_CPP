#include "str.h"

char * my_strcpy( char * destPtr, const char * srcPtr ){
    if (destPtr == 0) return 0;

    char *ptr = destPtr;

    while (*srcPtr != 0)
        *destPtr++ = *srcPtr++;
    *destPtr = '\0';
    return ptr;
}

char * my_strcat( char * destPtr, const char * srcPtr ){
    if((destPtr == 0) && (srcPtr == 0)) return 0;

    char *ptr = destPtr;
    while(*ptr != '\0')
        ++ptr;

    while(*srcPtr != '\0')
        *ptr++ = *srcPtr++;

    *ptr = '\0';
    return destPtr;
}

int my_strcmp( const char * str1, const char * str2 ){
    const unsigned char *ptr1 = ( const unsigned char * )str1;
    const unsigned char *ptr2 = ( const unsigned char * )str2;

    while ( *ptr1 && *ptr1 == *ptr2 ) ++ptr1, ++ptr2;

    return ( *ptr1 > *ptr2 ) - ( *ptr2  > *ptr1 );
}

unsigned long long my_strlen( const char * str ){
    unsigned long long count = 0;

    while(*str++ != '\0')
        ++count;

    return count;
}