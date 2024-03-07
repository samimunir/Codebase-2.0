/*
    Author: Sami Munir
    Codebase 2.0
    Data Structures and Algorithms
    singly-linked-list
    - singly-linked-list.h
*/
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void print_linked_list();

void print_linked_list_stats();

bool isEmpty();

void insert_head(int);

void remove_head();

void insert_last(int);

void remove_last();