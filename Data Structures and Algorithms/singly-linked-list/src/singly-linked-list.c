/*
    Author: Sami Munir
    Codebase 2.0
    Data Structures and Algorithms
    singly-linked-list
    - singly-linked-list.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "singly-linked-list.h"

struct Node *head = NULL;

bool is_empty() {
    if (head == NULL) {
        return true;
    } else {
        return false;
    }
}