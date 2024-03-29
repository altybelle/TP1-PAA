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

item* pop(stack** root) {
    if (is_stack_empty(*root)) {
        return NULL;
    }

    stack *temp = *root;
    *root = (*root)->next;
    item *popped = (item*)malloc(sizeof(item));
    popped->i = temp->val.i;
    popped->j = temp->val.j;
    free(temp);

    return popped;
}
