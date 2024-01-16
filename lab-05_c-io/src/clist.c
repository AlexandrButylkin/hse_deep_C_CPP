#include "clist.h"

struct intrusive_list* init_list(struct intrusive_list* list){
    list->head = 0;
    list->tail = 0;
    return list;
}

void add_node_front(struct intrusive_list* list, struct intrusive_node* node){
    if(list->head == 0){
        list->head = node;
        list->head->next = 0;
        list->head->prev = 0;
        list->tail = list->head;
    } else {
        list->head->prev = node;
        node->next = list->head;
        node->prev = 0;
        list->head = node;
    }
}

void add_node_back(struct intrusive_list* list, struct intrusive_node* node){
    if(list->head == 0){
        list->head = node;
        list->head->next = 0;
        list->head->prev = 0;
        list->tail = list->head;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = 0;
        list->tail = node;
    }
}

struct intrusive_node* remove_node(struct intrusive_list* list, struct intrusive_node* node){

    struct intrusive_node* tmp = 0;
    if(list->head == node){
        list->head = list->head->next;
        tmp = list->head;
    } else {
        tmp = node->next;
        node->prev->next = node->next;
        if(node->next)
            node->next->prev = node->prev;
    }
    return tmp;
}

int get_length(struct intrusive_list* list){
    int count = 0;
    struct intrusive_node* tmp = list->head;
    while(tmp){
        ++count;
        tmp = tmp->next;
    }
    return count;
}

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *node, void *data), void *data){
    struct intrusive_node* tmp = list->head;
    while(tmp){
        op(tmp, data);
        tmp = tmp->next;
    }
}
