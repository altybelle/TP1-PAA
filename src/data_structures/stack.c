#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack *new_cell(item v) {
    stack *cell = (stack*) malloc(sizeof(stack));
    cell->val = v;
    cell->next = NULL;
    return cell;
}

int is_stack_empty(stack* s) {
    return (!s);
}
int check_coord_on_stack(stack* s, int i, int j){
    stack *cell = s;
    while (cell->next != NULL){
        if (cell->val.i == i && cell->val.j == j){
            return 1;
        }
        cell = cell->next;
    } return 0;
}

void push(stack** root, item v) {
    stack *cell = new_cell(v);
    cell->next = *root;
    *root = cell;
}

item *peek(stack* root) {
    if (is_stack_empty(root)) {
        return NULL;
    }
    return &root->val;
}

void pop(stack** root) {
    if (is_stack_empty(*root)) {
        return;
    }

    stack *temp = *root;
    *root = (*root)->next;
    item popped = temp->val;

    printf("POPPED: %d %d\n", popped.i, popped.j);

    free(temp);
}
