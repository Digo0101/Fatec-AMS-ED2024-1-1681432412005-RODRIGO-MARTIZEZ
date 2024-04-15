/*------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                      Estrutura de Dados  */
                    /*    avaliação N1 */
/*                                                         */
/*             Objetivo: Controlar Estoque de produtos                   */
/* Autores: Rodrigo Martinez , Lucas                                */
/*                                                                        */
/*                                                       Data:14/04/2024  */
/*------------------------------------------------------------------------*/ 
#include <stdio.h>
#include <stdlib.h>
#include "logistica.h"

int main() {
    Pacote* listaPacotes = NULL;

   
    char origem[MAX_CIDADE_LEN];
    char destino[MAX_CIDADE_LEN];
    char conteudo[MAX_CONTEUDO_LEN];

   
    printf("Digite a cidade de origem do pacote: ");
    fgets(origem, MAX_CIDADE_LEN, stdin);
    printf("Digite a cidade de destino do pacote: ");
    fgets(destino, MAX_CIDADE_LEN, stdin);
    printf("Digite o conteúdo do pacote: ");
    fgets(conteudo, MAX_CONTEUDO_LEN, stdin);

   
    origem[strcspn(origem, "\n")] = '\0';
    destino[strcspn(destino, "\n")] = '\0';
    conteudo[strcspn(conteudo, "\n")] = '\0';

   
    incluirPacote(&listaPacotes, origem, destino, conteudo);

    
    mostrarEntregas(listaPacotes);

    
    listarTodosPacotes(listaPacotes);

    
    int idParaAlterar;
    printf("Digite o ID do pacote que deseja alterar o status: ");
    scanf("%d", &idParaAlterar);
    alterarStatus(&listaPacotes, idParaAlterar, 2);

    
    int idParaRastrear;
    printf("Digite o ID do pacote que deseja rastrear: ");
    scanf("%d", &idParaRastrear);
    rastrearPacote(listaPacotes, idParaRastrear);

    return 0;
}
