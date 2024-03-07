/*
    Author: Sami Munir
    Codebase 2.0
    Data Structures and Algorithms
    singly-linked-list
    - singly-linked-list.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void print_linked_list();

void print_linked_list_stats();

bool is_empty();

bool does_contain(int);

void insert_head(int);

void remove_head();

void insert_last(int);

void remove_last();

void remove_node(int);

void remove_node_at(int);

void clear_list();