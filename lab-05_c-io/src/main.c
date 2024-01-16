#include <stdio.h>
#include <string.h>
#include "../include/point.h"

void LoadText(char* filePath, struct intrusive_list* list) {
    FILE* file;
    if(file = fopen(filePath, "r")){
        int x, y;
        while(fscanf(file, "%d%d", &x, &y) != EOF){
            add_point_to_back(list, x, y);
            fgetc(file);
        }
        fclose(file);
    }else {
        printf("ERROR");
    }
}

void LoadBin(char* filePath, struct intrusive_list* list) {
    FILE* file;
    if(file = fopen(filePath, "r")) {
        int x, y;
        while(1) {
            int x_size = fread(&x, sizeof(char), 3, file);
            int y_size = fread(&y, sizeof(char), 3, file);
            if(x_size != 3 || y_size != 3)
                break;
            add_point_to_back(list, x, y);
        }
        fclose(file);
    }else {
        printf("ERROR");
    }
}

void WriteText(char* filePath, const struct intrusive_list* list){
    FILE* file;
    if(file = fopen(filePath, "w")){
        struct intrusive_node* tmp = list->head;
        while(tmp){
            struct point* p = container_of(tmp, struct point, node);
            fprintf(file, "%d %d\n", p->x, p->y);
            tmp = tmp->next;
        }
        fclose(file);
    }else {
        printf("ERROR");
    }
}

void WriteBin(char* filePath, struct intrusive_list* list){
    FILE* file;
    if(file = fopen(filePath, "wb")){
        struct intrusive_node* tmp = list->head;
        while(tmp){
            struct point* p = container_of(tmp, struct point, node);
            fwrite(&p->x, 3, 1, file);
            fwrite(&p->y, 3, 1, file);
            tmp = tmp->next;
        }
        fclose(file);
    } else {
        printf("ERROR");
    }
}

void increment_point_counter(struct intrusive_node* node, int* counter){
    if(node)
        ++*counter;
}

int main(int argc, char** argv) {
    char* inFileView = argv[1];
    char* inFilePath = argv[2];
    char* action = argv[3];

    struct intrusive_list list;
    init_list(&list);

    if(strcmp(inFileView, "loadtext") == 0){
        LoadText(inFilePath, &list);
    }
    else if(strcmp(inFileView, "loadbin") == 0){
        LoadBin(inFilePath, &list);
    }

    if(strcmp(action, "savetext") == 0){
        WriteText(argv[4], &list);
    }
    else if (strcmp(action, "savebin") == 0){
        WriteBin(argv[4], &list);
    }
    else if (strcmp(action, "print") == 0){
        char* format = argv[4];
        apply(&list, print_point, format);
        printf("\n");
    } else if(strcmp(action, "count") == 0){
        int counter = 0;
        apply(&list, increment_point_counter, &counter);
        printf("%d\n", counter);
    }
    remove_all_points(&list);
    return 0;
}
