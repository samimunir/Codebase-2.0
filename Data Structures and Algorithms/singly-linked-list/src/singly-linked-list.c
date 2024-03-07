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

bool does_contain(int target_data) {
    if (is_empty()) {
        return false;
    } else {
        struct Node *current_node = head;
        while (current_node != NULL) {
            if (current_node -> data == target_data) {
                return true;
            }
            current_node = current_node -> next;
        }
        free(current_node);
        return false;
    }
}