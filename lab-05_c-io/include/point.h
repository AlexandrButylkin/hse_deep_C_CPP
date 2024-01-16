#ifndef LAB_05_C_IO_POINT_H
#define LAB_05_C_IO_POINT_H
#include "clist.h"

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point_to_back(struct intrusive_list* list, int x, int y);
void add_point_to_front(struct intrusive_list* list, int x, int y);
void remove_point(struct intrusive_list* list, int x, int y);
struct intrusive_node* remove_node(struct intrusive_list* list, struct intrusive_node* node);
void show_all_points(struct intrusive_list* list, char* format);
void print_point(struct intrusive_node* node, char* format);
void remove_all_points(struct intrusive_list* list);

#endif //LAB_05_C_IO_POINT_H
