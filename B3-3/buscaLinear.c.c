/* -------------------------------------------
Fatec São Caetano do Sul - Estrutura de Dados
Professor: Carlos Veríssimo
Proposta: Implementação de algoritmos de busca
Autor: Rodrigo Martinez
Data: 01/10/2024
------------------------------------------- */
#include <stdio.h>


int buscaLinear(int arr[], int n, int x) {
   
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {  
            return i;  
        }
    }
    return -1;  
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};  
    int n = sizeof(arr) / sizeof(arr[0]);  
    int x = 10; 
   
    int resultado = buscaLinear(arr, n, x);

    
    if (resultado == -1) {
        printf("Elemento não encontrado no array.\n");
    } else {
        printf("Elemento encontrado na posição: %d\n", resultado);
    }

    return 0;
}
