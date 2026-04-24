#include "stack.h"
#include <stdlib.h>

struct Node {
    Item item;
    struct Node* next;
};

struct Stack {
    struct Node* head;
};

StackPtr StackInit() {
    StackPtr s = (StackPtr)malloc(sizeof(struct Stack));
    s->head = NULL;
    return s;
}

int StackEmpty(StackPtr s) {
    return s->head == NULL;
}

void push(StackPtr s, Item item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->item = item;
    newNode->next = s->head;
    s->head = newNode;
}

Item pop(StackPtr s) {
    if (StackEmpty(s)) return NULL;
    struct Node* temp = s->head;
    Item item = temp->item;
    s->head = temp->next;
    free(temp);
    return item;
}

void StackDestroy(StackPtr s) {
    while (!StackEmpty(s)) {
        pop(s);
    }
    free(s);
}