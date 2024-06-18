#include <stdio.h>
#include <stdlib.h>

// Define a structure for list nodes
typedef struct ListNode {
    struct ListNode *next;
    int data;
    int count;
} ListNode;

// Macro to create a new node
#define NEW_NODE(node, value) do { \
    node = (ListNode*)malloc(sizeof(ListNode)); \
    node->data = value; \
    node->next = NULL; \
    node->count = 1; \
} while(0)

// Macro to increment reference count
#define ADD_REF(node) do { \
    if (node != NULL) node->count++; \
} while(0)

// Macro to decrement reference count and free memory if count reaches zero
#define DEL_REF(node) do { \
    if (node != NULL) { \
        node->count--; \
        if (node->count == 0) { \
            free(node); \
            node = NULL; \
        } \
    } \
} while(0)

// Function to append a new node to the linked list
void appendNode(ListNode **head, int value) {
    ListNode *newNode;
    NEW_NODE(newNode, value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ListNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to search for a value in the list
ListNode* searchNode(ListNode *head, int value) {
    ListNode *current = head;
    while (current != NULL) {
        if (current->data == value) {
            ADD_REF(current); // Increment ref count if node is found
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to print the list
void printList(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        printf("%d (Ref count: %d) -> ", current->data, current->count);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    ListNode *head = NULL;
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    // Append 3 nodes to the list

    printf("Initial list: ");
    printList(head);

    ListNode *found = searchNode(head, 20);
    if (found) {
        printf("\nFound: %d with ref count %d\n", found->data, found->count);
    }

    // Cleanup: manually manage memory
    ListNode *current = head;
    ListNode *next;
    while (current != NULL) {
        next = current->next;
        DEL_REF(current);
        current = next;
    }

    return 0;
}
