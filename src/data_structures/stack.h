#ifndef STACK
#define STACK

typedef struct item {
    int i;
    int j;
} item;

typedef struct stack_cell {
    item val;
    struct stack_cell *next;
} stack;

stack *new_cell(item);
int is_stack_empty(stack*);
int check_coord_on_stack(stack* s, int i, int j);
void push(stack**, item);
item *peek(stack*);
void pop(stack**);

#endif // STACK