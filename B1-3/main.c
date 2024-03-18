#include <stdio.h>

#define SIZE 5
float encontrarMaiorElemento(float *array){
  float maior = array[1];
  for(int i = 1; i<SIZE; i++)
{if (array[i] > maior){
  maior = array[1];
}
}
  return maior;
}
float calcularSoma(float *array){
  float soma = 0;
  for(int i = 0; i<SIZE; i++){
    soma += array[i];
  }
  return soma;
}
void imprimirArray(float *array){
  printf("Array: [");
  for(int i = 0; i<SIZE; i++){
    printf("%.2f", array[i]);
    if (i <SIZE - 1){
      printf(",");
    }
  }
  printf("]\n");
}
void modificarArray(float *array, float multiplicador){
for (int i = 0;i <SIZE; i++){
  array[i] *= multiplicador;
}
}
int main(){
float notas [SIZE];
  printf("Digite as %d notas:\n",SIZE);
  for(int i = 0; i<SIZE; i++){
    printf("Nota %d: ", i + 1);
    scanf("%f", &notas[i]);
  }
  for (int i = 0; i < SIZE - 1; i++) {
    for (int j = 0; j < SIZE - i - 1; j++) {
        if (notas[j] > notas[j + 1]) {
            float temp = notas[j];
            notas[j] = notas[j + 1];
            notas[j + 1] = temp;
        }
    }
  }
  printf("\nMaior elemento: %.2f\n", encontrarMaiorElemento(notas));
  printf("Soma de todos os elementos: %.2f\n", calcularSoma(notas));
  printf("Array modificado (multiplicado por 2):\n");
  modificarArray(notas, 2);
  imprimirArray(notas);
  return 0;
}
  