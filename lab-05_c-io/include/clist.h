#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node {
    struct intrusive_node* next;
    struct intrusive_node* prev;
};

struct intrusive_list {
    struct intrusive_node* head;
    struct intrusive_node* tail;
};

struct intrusive_list* init_list(struct intrusive_list* list);
void add_node_front(struct intrusive_list* list, struct intrusive_node* node);
void add_node_back(struct intrusive_list* list, struct intrusive_node* node);
struct intrusive_node* remove_node(struct intrusive_list* list, struct intrusive_node* node);
struct intrusive_node* get_last_node(struct intrusive_node* list);

int get_length(struct intrusive_list* list);

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *node, void *data), void *data);
#endif
