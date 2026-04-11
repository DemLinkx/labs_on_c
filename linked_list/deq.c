#include "deq.h"
#include <stdio.h>


struct node {
    double data;
    struct node *next, *prev;
};

struct deque {
    struct node *front, *back;
};

typedef struct node nd;
typedef struct deque deque;


deque* deq_init (){
    deque* d = malloc(sizeof(*d));
    if (!d) return NULL;
    d->front = NULL;
    d->back = NULL;
    return d;
}


int deque_is_empty(deque* d){
    return d->front == NULL;
}


int deque_push_front (deque* d, double data){
    nd* new_nd = malloc(sizeof(*new_nd));
    if (!new_nd) return 1;

    new_nd->prev = NULL;
    new_nd->next = NULL;

    new_nd->data = data;
    new_nd->next = d->front;

    if (!deque_is_empty(d)) d->front->prev = new_nd;
    else d->back = new_nd;
    d->front = new_nd;

    return 0;
}


int deque_push_back (deque* d, double data){
    nd* new_nd = malloc(sizeof(*new_nd));
    if (!new_nd) return 1;

    new_nd->next = NULL;
    new_nd->prev = NULL;
    new_nd->data = data;

    if (!deque_is_empty(d)){ 
        new_nd->prev = d->back;
        d->back->next = new_nd; 
    }
    else d->front = new_nd;

    d->back = new_nd;
    return 0;
}


int deque_pop_back (deque* d, double* data){
    nd* del_nd = d->back;
    if (!del_nd) return 1;
    if (data != NULL) *data = del_nd->data;  // тонко
    
    if (del_nd->prev == NULL){
        d->back = NULL;
        d->front = NULL;
        free(del_nd);
        return 0;
    }

    d->back = del_nd->prev;
    d->back->next = NULL;
    free(del_nd);
    return 0;
}


int deque_pop_front (deque* d, double* data){
    nd* del_nd = d->front;
    if (!del_nd) return 1;
    *data = del_nd->data; 

    if (del_nd->next == NULL){
        d->front = NULL;
        d->back = NULL;
        free(del_nd);
        return 0;
    }

    d->front = del_nd->next;
    d->front->prev = NULL;
    free(del_nd);
    return 0;
}


void deque_free (deque* d){
    while (!deque_is_empty(d)) deque_pop_back(d, NULL); // тонко
    free(d);
}


deque* deque_copy (deque* d){
    deque* new_deq = deq_init();
    if(new_deq == NULL){
        return NULL;
    }
    if (!deque_is_empty(d)){
        nd* left = d->front;
        while (left != NULL){
            deque_push_back(new_deq, left->data);
            left = left->next;
        }
    }
    return new_deq;
}


void deque_print(deque *d) {
    if (deque_is_empty(d)) {
        printf("[]\n");
        return;
    }

    printf("[");

    nd *left = d->front;
    while (left != NULL) {
        printf("%.2f", left->data);
        if (left->next != NULL) printf(", ");
        left = left->next;
    }
    printf("]\n");
}


int deque_size(deque *d) {
    int count = 0;
    nd *left = d->front;
    while (left != NULL) {
        count++;
        left = left->next;
    }
    return count;
}
