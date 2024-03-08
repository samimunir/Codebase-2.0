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
unsigned int number_of_nodes = 0;

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

void print_linked_list() {
    if (is_empty()) {
        printf("\tHEAD -> NULL\n");
    } else {
        struct Node *current_node = head;
        printf("\tHEAD -> ");
        while (current_node != NULL) {
            printf("%d -> ", current_node -> data);
            current_node = current_node -> next;
        }
        printf("NULL\n");
    }
}

void print_linked_list_stats() {
    print_linked_list();
    printf("\t\tnumber_of_nodes: %d\n", number_of_nodes);
}