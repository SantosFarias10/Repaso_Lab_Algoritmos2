#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"
#include <stdio.h>

#define MAX_PRIORITY 5  /* sin ; va xd */

struct s_pstack {
    unsigned int size;
    priority_t max_priority;
    struct s_node *array[MAX_PRIORITY];
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;

    new_node = malloc(sizeof(struct s_node));

    new_node->elem = e;
    new_node->next = NULL;

    assert(new_node!=NULL);
    return new_node; 
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pstack s) {
    return (s != NULL);
}

/* inicializamos el pstack */
pstack pstack_empty(priority_t max_priority) {
    pstack s = NULL;
    s = malloc(sizeof(struct s_pstack));

    s->max_priority = max_priority;
    s->size = 0u;
    
    for (unsigned int i = 0u; i <= max_priority; i++){
        s->array[i] = NULL;
    }

    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));

    if(priority > s->max_priority){
        printf("La prioridad del elemento que se quiere agregar es mayor al permitido\n");
        return s;
    } else{
        struct s_node *new_node = create_node(e);
        struct s_node *aux = s->array[priority];
        s->array[priority] = new_node;
        new_node->next = aux;
        s->size++;
    }

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));

    return (s->size == 0u);
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    pstack_elem max = 0u;

    for (unsigned int i = 0; i <= s->max_priority; i++){ 
        if(s->array[i] != NULL){
            if(i > max){
                max = i;
            }
        }
    }
    pstack_elem e = s->array[max]->elem;

    assert(invrep(s));
    return e;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    pstack_elem max = 0u;

    for(unsigned int i = 0u; i <= s->max_priority; i++){
        if (s->array[i] != NULL){
            if(i > max){
                max = i;
            }
        }
    }

    assert(invrep(s));
    return max;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return (s->size);
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    pstack_elem max = 0u;

    for(unsigned int i = 0u; i <= s->max_priority; i++){
        if(s->array[i] != NULL){
            if(i > max){
                max = i;
            }
        }
    }

    struct s_node *aux = s->array[max];
    s->array[max] = s->array[max]->next;
    destroy_node(aux);
    s->size--;

    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));

    for(unsigned int i = 0u; i <= s->max_priority; i++){
        while(s->array[i] != NULL){
            struct s_node *aux = s->array[i];
            s->array[i] = s->array[i]->next;
            destroy_node(aux);
        }
    }

    free(s);
    s = NULL;

    assert(s == NULL);

    return s;
}
