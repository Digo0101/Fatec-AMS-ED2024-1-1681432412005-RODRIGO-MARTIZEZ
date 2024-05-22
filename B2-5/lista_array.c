#include <stdio.h>
#include <time.h>


void insertInArray(int array[], int size, int value) {
    int i, position;

    
    if (size % 2 == 0)
        position = size / 2;
    else
        position = (size + 1) / 2;

    
    for (i = size - 1; i >= position; i--) {
        array[i + 1] = array[i];
    }

   
    array[position] = value;
}

int main() {
    int arraySize = 4;
    int array[arraySize];
    int valueToInsert;
  
    clock_t startTime = clock();
   
    printf("Digite os elementos do array (tamanho 4): ");
    for (int i = 0; i < arraySize; i++) {
        scanf("%d", &array[i]);
    }

    printf("Digite o valor a ser inserido no meio do array: ");
    scanf("%d", &valueToInsert);

   

    insertInArray(array, arraySize, valueToInsert);

   
  
    printf("Array depois da insercao: ");
    for (int i = 0; i < arraySize + 1; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
   
    clock_t endTime = clock();

   
    printf("Tempo de processamento para insercao no array: %.4f segundos\n",
           (double)(endTime - startTime) / CLOCKS_PER_SEC);

    return 0;
}
