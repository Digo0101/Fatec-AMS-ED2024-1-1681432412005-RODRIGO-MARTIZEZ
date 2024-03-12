#include <stdio.h>

void aplicar_desconto(float *preco, float desconto) {
    if (desconto >= 0 && desconto <= 100) {
        *preco = *preco * (1 - desconto / 100);
    } else {
        printf("Desconto inválido!\n");
    }
}

int main() {
  float preco_produto, desconto;
  printf("insira o valor do produto:");
  scanf("%f", & desconto);
  aplicar_desconto(& preco_produto, desconto);
  printf("preco original: R$%.2f/n", preco_produto/ (1- desconto/100));
  printf("Desconto aplicado: %.2f%%\n", desconto);
   printf("Preco final: R$ %.2f\n", preco_produto);
  return 0;

}