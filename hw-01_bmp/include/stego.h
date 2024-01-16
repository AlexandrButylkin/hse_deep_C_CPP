#ifndef STEGO_H
#define STEGO_H

#include "bmp.h"

char get_code_by_symbol(char symbol);
char get_symbol_by_code(char symbol);

void code_pixel(bmp_t* bmp, int x, int y, char chanel, bool bit);
bool decode_pixel(bmp_t* bmp, int x, int y, char chanel);

void code_message (FILE* key, bmp_t* bmp, FILE* msg);
void decode_message(FILE* key, FILE* out, bmp_t* bmp);

#endif //STEGO_H