// A Hello World Program with doubly linked list practice
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining a node structure 
typedef struct Node {
    char* string;
    struct Node* next;
    struct Node* prev;
} Node;

// Insert a new node in the list, or create a node if there is no list
void insert(Node** list, Node* prev, const char* string) {
    // create a new node
    Node* node = malloc(sizeof(Node));

    // Copy string to the heap
    node->string = malloc(strlen(string) + 1);
    strcpy(node->string, string);

    if (prev == NULL) {
        if (*list != NULL) (*list)->prev = node;
        node->prev = NULL;
        node->next = *list;
        *list = node;
    } else {
        node->next = prev->next;
        if (node->next != NULL) node->next->prev = node;
        prev->next = node;
        node->prev= prev;
    }
}

// Find a string in doubly linked list
Node* find(Node* list, const char* string) {
    while (list != NULL) {
        if (strcmp(string, list->string) == 0) {
            return list;
        }

        list = list->next;
    }

    // Not found
    return NULL;
}

// Delete a node from a list
void delete(Node** list, Node* node) {
    // Unlink node
    if(node->prev != NULL) node->prev->next = node->next;
    if(node->next != NULL) node->next->prev = node->prev;

    // If head is deleted, update new head
    if (*list == node) *list = node->next;

    free(node->string);
    free(node);
}

// Print doubly linked list
void printList(Node* list) {
    while (list != NULL) {
        printf("%p [prev %p next %p] %s\n",
            list, list->prev, list->next, list->string);
        list = list->next;
    }
}

int main(int argc, const char* argv[]) {
    printf("Hello World!\n");

    Node* list = NULL;
    insert(&list, NULL, "four");
    insert(&list, NULL, "one");
    insert(&list, find(list, "one"), "two");
    insert(&list, find(list, "two"), "three");

    printList(list);
    printf("-- Delete three --\n");
    delete(&list, find(list, "three"));
    printList(list);

    return 0;
}