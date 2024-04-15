#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logistica.h"


Pacote* criarPacote(int id, char origem[], char destino[], char conteudo[], int status) {
    Pacote* novoPacote = (Pacote*)malloc(sizeof(Pacote));
    if (novoPacote == NULL) {
        printf("Erro ao alocar memória para o novo pacote.\n");
        exit(1);
    }
    novoPacote->id = id;
    strcpy(novoPacote->origem, origem);
    strcpy(novoPacote->destino, destino);
    strcpy(novoPacote->conteudo, conteudo);
    novoPacote->status = status;
    novoPacote->proximo = NULL;
    return novoPacote;
}


void incluirPacote(Pacote** listaPacotes, char origem[], char destino[], char conteudo[]) {
    static int proximoID = 1;
    Pacote* novoPacote = criarPacote(proximoID, origem, destino, conteudo, 1);
    if (*listaPacotes == NULL) {
        *listaPacotes = novoPacote;
    } else {
        Pacote* temp = *listaPacotes;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoPacote;
    }
    proximoID += 2;
}


void alterarStatus(Pacote** listaPacotes, int id, int novoStatus) {
    Pacote* temp = *listaPacotes;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->status = novoStatus;
            return;
        }
        temp = temp->proximo;
    }
    printf("Pacote com ID %d não encontrado.\n", id);
}


void rastrearPacote(Pacote* listaPacotes, int id) {
    Pacote* temp = listaPacotes;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Conteúdo do pacote: %s\n", temp->conteudo);
            printf("Status do pacote: %d\n", temp->status);
            return;
        }
        temp = temp->proximo;
    }
    printf("Pacote com ID %d não encontrado.\n", id);
}


void mostrarEntregas(Pacote* listaPacotes) {
    printf("Situação atual das entregas:\n");
    Pacote* temp = listaPacotes;
    while (temp != NULL) {
        printf("ID: %d, Origem: %s, Destino: %s, Status: %d\n", temp->id, temp->origem, temp->destino, temp->status);
        temp = temp->proximo;
    }
}

void listarTodosPacotes(Pacote* listaPacotes) {
    printf("Lista de todos os pacotes:\n");
    Pacote* temp = listaPacotes;
    while (temp != NULL) {
        printf("ID: %d, Origem: %s, Destino: %s, Conteúdo: %s, Status: %d\n", temp->id, temp->origem, temp->destino, temp->conteudo, temp->status);
        temp = temp->proximo;
    }
}
