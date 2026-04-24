#ifndef ITEM_H
#define ITEM_H

typedef struct {
    int x;
    int y;
} Point;

typedef Point* Item;

int compare_items(Item a, Item b);

#endif