include <stdio.h>

int main() {
    int numerointeiros[5];
    
    printf("Por favor, insira 5 números inteiros positivos:\n");
    
    
    for (int i = 0; i < 5; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &numerointeiros[i]);
    }
    
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (numerointeiros[j] > numerointeiros[j + 1]) {
                int temp = numerointeiros[j];
                numerointeiros[j] = numerointeiros[j + 1];
                numerointeiros[j + 1] = temp;
            }
        }
    }
    
    
    printf("\nNúmeros em ordem crescente:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numerointeiros[i]);
    }
    printf("\n");
    
    return 0;
}