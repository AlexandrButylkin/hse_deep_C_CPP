#include <stdlib.h>
#include <stdio.h>
#include "../include/clist.h"

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point_to_back(struct intrusive_list* list, int x, int y){
    struct point* p = (struct point*)malloc(sizeof (struct point));
    p->x = x;
    p->y = y;
    add_node_back(list, &p->node);
}

void add_point_to_front(struct intrusive_list* list, int x, int y){
    struct point* p = (struct point*)malloc(sizeof (struct point));
    p->x = x;
    p->y = y;
    add_node_front(list, &p->node);
}

void remove_point(struct intrusive_list* list, int x, int y) {
    struct intrusive_node* tmp = list->head;
    while(tmp != 0){
        struct point* p = container_of(tmp, struct point, node);
        if(p->x == x && p->y == y){
            tmp = remove_node(list, &p->node);
            free(p);
        } else {
            tmp = tmp->next;
        }
    }
}

void show_all_points(struct intrusive_list* list, char* format) {
    struct intrusive_node* tmp = list->head;
    while(tmp != 0){
        struct point* p = container_of(tmp, struct point, node);
        printf(format, p->x, p->y);
        tmp = tmp->next;
    }
    printf("\n");
}

void print_point(struct intrusive_node* node, char* format){
    struct point* p = container_of(node, struct point, node);;
    printf(format, p->x, p->y);
}

void remove_all_points(struct intrusive_list* list) {
    struct intrusive_node* tmp = list->head;
    while(tmp != 0){
        struct point* p = container_of(tmp, struct point, node);
        tmp = remove_node(list, &p->node);
        free(p);
    }
}

