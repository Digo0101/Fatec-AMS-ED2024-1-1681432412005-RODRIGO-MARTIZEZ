/* -------------------------------------------
Fatec São Caetano do Sul - Estrutura de Dados
Professor: Carlos Veríssimo
Proposta: Implementação de algoritmos de busca
Autor: Rodrigo Martinez
Data: 01/10/2024
------------------------------------------- */

#include <stdio.h>


int buscaBinaria(int arr[], int n, int x) {
    int esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;


        if (arr[meio] == x) {
            return meio;
        }

        
        if (arr[meio] < x) {
            esquerda = meio + 1;
        }
      
        else {
            direita = meio - 1;
        }
    }
    return -1;  
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};  
    int n = sizeof(arr) / sizeof(arr[0]);  
    int x = 10;  

   
    int resultado = buscaBinaria(arr, n, x);

    
    if (resultado == -1) {
        printf("Elemento não encontrado no array.\n");
    } else {
        printf("Elemento encontrado na posição: %d\n", resultado);
    }

    return 0;
}
