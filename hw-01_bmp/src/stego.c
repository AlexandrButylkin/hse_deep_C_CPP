#include "stego.h"
#include <stdbool.h>

char get_code_by_symbol(char symbol){
    if(symbol == 'A') return 0;
    if(symbol == 'B') return 1;
    if(symbol == 'C') return 2;
    if(symbol == 'D') return 3;
    if(symbol == 'E') return 4;
    if(symbol == 'F') return 5;
    if(symbol == 'G') return 6;
    if(symbol == 'H') return 7;
    if(symbol == 'I') return 8;
    if(symbol == 'J') return 9;
    if(symbol == 'K') return 10;
    if(symbol == 'L') return 11;
    if(symbol == 'M') return 12;
    if(symbol == 'N') return 13;
    if(symbol == 'O') return 14;
    if(symbol == 'P') return 15;
    if(symbol == 'Q') return 16;
    if(symbol == 'R') return 17;
    if(symbol == 'S') return 18;
    if(symbol == 'T') return 19;
    if(symbol == 'U') return 20;
    if(symbol == 'V') return 21;
    if(symbol == 'W') return 22;
    if(symbol == 'X') return 23;
    if(symbol == 'Y') return 24;
    if(symbol == 'Z') return 25;
    if(symbol == ' ') return 26;
    if(symbol == '.') return 27;
    if(symbol == ',') return 28;
    return -1;
}

char get_symbol_by_code(char symbol){
    if(symbol == 0) return 'A';
    if(symbol == 1) return 'B';
    if(symbol == 2) return 'C';
    if(symbol == 3) return 'D';
    if(symbol == 4) return 'E';
    if(symbol == 5) return 'F';
    if(symbol == 6) return 'G';
    if(symbol == 7) return 'H';
    if(symbol == 8) return 'I';
    if(symbol == 9) return 'J';
    if(symbol == 10) return 'K';
    if(symbol == 11) return 'L';
    if(symbol == 12) return 'M';
    if(symbol == 13) return 'N';
    if(symbol == 14) return 'O';
    if(symbol == 15) return 'P';
    if(symbol == 16) return 'Q';
    if(symbol == 17) return 'R';
    if(symbol == 18) return 'S';
    if(symbol == 19) return 'T';
    if(symbol == 20) return 'U';
    if(symbol == 21) return 'V';
    if(symbol == 22) return 'W';
    if(symbol == 23) return 'X';
    if(symbol == 24) return 'Y';
    if(symbol == 25) return 'Z';
    if(symbol == 26) return ' ';
    if(symbol == 27) return '.';
    if(symbol == 28) return ',';
    return -1;
}

void code_pixel(bmp_t* bmp, int x, int y, char chanel, bool bit){
    pixel_t* pixel = bmp->rect.pixels[y] + x;
    if(chanel == 'R') {
        pixel->r = bit ? pixel->r | (1 << 0) : pixel->r & ~(1 << 0);
    } else if (chanel == 'G') {
        pixel->g = bit ? pixel->g | (1 << 0) : pixel->g & ~(1 << 0);
    } else if (chanel == 'B'){
        pixel->b = bit ? pixel->b | (1 << 0) : pixel->b & ~(1 << 0);
    }
}

bool decode_pixel(bmp_t* bmp, int x, int y, char chanel){
    pixel_t* pixel = bmp->rect.pixels[y] + x;
    if(chanel == 'R') {
        return pixel->r & 1;
    } else if (chanel == 'G') {
        return pixel->g & 1;
    } else if (chanel == 'B'){
        return pixel->b & 1;
    }
}

void code_message (FILE* key, bmp_t* bmp, FILE* msg) {
    int symbol = fgetc(msg);
    while(feof(msg) == 0){
        char code = get_code_by_symbol((char)symbol);
        if(code != -1) {
            for (int j = 0; j < 5; ++j) {
                int x, y;
                char chanel;
                fscanf(key, "%d%d %c", &x, &y, &chanel);
                code_pixel(bmp, x, y, chanel, (bool) ((1 << j) & code));
            }
        }
        symbol = fgetc(msg);
    }
};

void decode_message(FILE* key, FILE* out, bmp_t* bmp) {
    int x, y;
    char chanel;
    int i = 0;
    char code = 0;
    while(fscanf(key, "%d%d %c", &x, &y, &chanel) != -1)
    {
        y = bmp->infoheader.biHeight - y - 1;
        code = code | (decode_pixel(bmp, x, y, chanel) << i);
        ++i;
        if(i == 5){
            fprintf(out, "%c", get_symbol_by_code(code));
            code = 0;
            i = 0;
        }
    }
    fprintf(out, "\n");
}