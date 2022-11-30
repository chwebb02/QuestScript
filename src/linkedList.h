#ifndef __linked_list__
#define __linked_list__

typedef struct nodestruct {
    void *obj;
    struct nodestruct *next;
} node;

typedef struct {
    node *head;
    int size;
} list;

list makeList();
int appendList(list *, void *);
int popList(list *, unsigned int);
void *fromList(list, unsigned int);
void freeList(list *);

#endif