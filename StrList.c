
// #pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct _StrList {
    Node* head;
    size_t size;
} StrList;

// Utility function to create a new node
static Node* Node_new(const char* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->data = strdup(data); // Copy the string to ensure independence
        node->next = NULL;
    }
    return node;
}

// Frees a single node
static void Node_free(Node* node) {
    if (node) {
        free(node->data); // Free the string
        free(node);       // Then free the node itself
    }
}

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list) {
        list->head = NULL;
        list->size = 0;
    }
    return list;
}

void StrList_free(StrList* StrList) {
    if (StrList) {
        Node* current = StrList->head;
        while (current) {
            Node* next = current->next;
            Node_free(current);
            current = next;
        }
        free(StrList);
    }
}

size_t StrList_size(const StrList* StrList) {
    return StrList ? StrList->size : 0;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if (!StrList || !data) return;
    Node* node = Node_new(data);
    if (!node) return;

    if (!StrList->head) {
        StrList->head = node;
    } else {
        Node* current = StrList->head;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
    StrList->size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (!StrList || !data || index < 0 || index > StrList->size) return;
    Node* node = Node_new(data);
    if (!node) return;

    if (index == 0) {
        node->next = StrList->head;
        StrList->head = node;
    } else {
        Node* current = StrList->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    StrList->size++;
}

char* StrList_firstData(const StrList* StrList) {
    if (StrList && StrList->head) {
        return StrList->head->data;
    }
    return NULL;
}

void StrList_print(const StrList* StrList) {
    if (!StrList) return;
    Node* current = StrList->head;
    while (current) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void StrList_printAt(const StrList* StrList, int index) {
    if (!StrList || index < 0 || index >= StrList->size) return;
    Node* current = StrList->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    printf("%s\n", current->data);
}

int StrList_printLen(const StrList* Strlist) {
    if (!Strlist) return 0;

    int totalLen = 0;
    Node* current = Strlist->head;
    while (current != NULL) {
        totalLen += strlen(current->data);
        current = current->next;
    }
    return totalLen;
}

int StrList_count(StrList* StrList, const char* data) {
    if (!StrList || !data) return 0;
    int count = 0;
    Node* current = StrList->head;
    while (current) {
        if (strcmp(current->data, data) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void StrList_remove(StrList* StrList, const char* data) {
    if (!StrList || !data) return;
    Node *current = StrList->head, *prev = NULL;
    while (current) {
        if (strcmp(current->data, data) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                StrList->head = current->next;
            }
            Node* temp = current;
            current = current->next;
            Node_free(temp);
            StrList->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || index >= StrList->size) {
        return; // Check for valid list and index
    }

    Node* temp = StrList->head;
    Node* prev = NULL;

    // Special case to remove head
    if (index == 0) {
        StrList->head = temp->next; // Change head
        Node_free(temp); // Free old head
        StrList->size--;
        return;
    }

    // Find previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < index; i++) {
        prev = temp;
        temp = temp->next;
    }

    // If position is more than number of nodes
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    // Free memory
    Node_free(temp);

    StrList->size--;
}

void StrList_reverse(StrList* StrList) {
    if (!StrList || !StrList->head || !StrList->head->next) return; // List is empty or has one element

    Node *prev = NULL;
    Node *current = StrList->head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move pointers one position ahead
        current = next;
    }
    StrList->head = prev; // Reset head to the new first element
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->size < 2) {
        return;
    }

    int swapped;
    do {
        swapped = 0;
        Node* current = StrList->head;
        while (current->next != NULL) {
            if (strcmp(current->data, current->next->data) > 0) {
                char* temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->size < 2) {
        printf("true \n");
        return 1; // Consider an empty list or a list with one element as sorted
    }

    Node* current = StrList->head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            printf("false \n");
            return 0; // Found two adjacent nodes out of order
        }
        current = current->next;
    }
    printf("true \n");
    return 1; // No elements out of order found
}
