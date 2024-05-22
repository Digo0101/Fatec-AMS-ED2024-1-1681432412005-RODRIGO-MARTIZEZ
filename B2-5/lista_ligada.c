#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insertInLinkedList(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= value) {
        
        
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;

        
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }

        
        newNode->next = current->next;
        current->next = newNode;
    }
}


void printLinkedList(Node* head) {
    printf("Lista ligada: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int value;
    clock_t startTime, endTime;

    
    startTime = clock();

    printf("Digite os valores para a lista ligada (4 espaços, em ordem crescente):\n");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &value);
        insertInLinkedList(&head, value);
    }

   
    int valueToInsert;
    printf("Digite o valor a ser inserido no meio da lista: ");
    scanf("%d", &valueToInsert);

   
    insertInLinkedList(&head, valueToInsert);

    
    printLinkedList(head);

   
    endTime = clock();

   
    printf("Tempo total de execução: %.4f segundos\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

   
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
