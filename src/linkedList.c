#ifndef _linked_list_
#define _linked_list_

#include "linkedList.h"

#include <stdlib.h>

list makeList() {
    list output;
    output.size = 0;

    output.head = malloc (sizeof(node));
    if (output.head == NULL)
        return (list){NULL, 0};
    
    output.head->obj = NULL;
    output.head->next = NULL;

    return output;
}

int appendList(list *li, void *insertion) {
    node *p = li->head;

    if (li->head == NULL)
        return 1;
    
    for (int i = 0; i < li->size; i++)
        p = p->next;
    
    p->next = malloc (sizeof(node));
    if (p->next == NULL)
        return 1;

    p->next->obj = insertion;
    p->next->next = NULL;

    li->size += 1;
    return 0;
}

int popList(list *li, unsigned int index) {
    if (li->head == NULL)
        return 1;
    if (li->head->next == NULL)
        return 2;
    if (index < 1 || index > li->size)
        return 3;

    node *p = li->head;

    // Seek the element before the deletion element
    for (int i = 1; i < index; i++)
        p = p->next;
    
    // Save the element to be freed and point the element before it to
    // the element after it
    node *deletion = p->next;
    p->next = p->next->next;

    free(deletion);
    return 0;
}

void *fromList(list li, unsigned int index) {
    if (li.head == NULL || li.head->next == NULL || li.size < 1 || index > li.size || index < 1)
        return NULL;
    
    node *p = li.head->next;
    for (int i = 1; i < index; i++)
        p = p->next;

    return p->obj;
}

void freeList(list *li) {
    node *p1 = li->head;
    node *p2 = li->head->next;
    
    for (int i = 0; i < li->size; i++) {
        free(p1);
        p1 = p2;
        p2 = p2->next;
    }

    li->size = 0;
}

#endif