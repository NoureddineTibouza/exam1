#include "list.h"
#include <stdio.h>


void insertAtPosition(Node** head, int k, int value) {
    Node* newNode = createNode(value);


    if (k == 0) {
        setNext(newNode, *head);
        *head = newNode;
        return;
    }

    Node* current = *head;
    int index = 0;

    while (current != NULL && index < k - 1) {
        current = getNext(current);
        index++;
    }


    if (current == NULL && index != k - 1) {
        printf("Error: Position %d is out of bounds.\n", k);
        deleteNode(newNode);
        return;
    }


    setNext(newNode, getNext(current));
    setNext(current, newNode);
}
int main() {
    Node* list = initializeList();
    printList(list);

    printf("Inserting 99 at position 0:\n");
    insertAtPosition(&list, 0, 99);
    printList(list);

    printf("Inserting 42 at position 3:\n");
    insertAtPosition(&list, 3, 42);
    printList(list);

    printf("Inserting 77 at the end:\n");
    insertAtPosition(&list, 7, 77);
    printList(list);

    printf("Trying to insert at position 10 (out of bounds):\n");
    insertAtPosition(&list, 10, 88);
    printList(list);

    return 0;
}