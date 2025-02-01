#include "list.h"
#include <stdio.h>
void reverseDoublyLinkedList(Node** head) {
    Node* current = *head;
    Node* temp = NULL;
    while (current != NULL) {
        temp = getNext(current);
        setNext(current, getPrev(current));
        setPrev(current, temp);
        current = getPrev(current);
    }
    if (temp != NULL) {
        *head = getPrev(temp);
    }
}
int main() {
    Node* list = initializeList();
    printf("Original list:\n");
    printList(list);

    printf("Reversed list:\n");
    reverseDoublyLinkedList(&list);
    printList(list);
    return 0;
}