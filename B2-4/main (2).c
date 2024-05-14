#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Paciente {
    char nome[50];
    int idade;
    char motivoConsulta[100];
    int prioridade;
    time_t inicioAtendimento;
    time_t fimAtendimento;
    int numeroConsultorio;
    struct Paciente *proximo;
} Paciente;

typedef struct Fila {
    Paciente *inicio;
    Paciente *fim;
} Fila;

typedef struct HistoricoAtendimentos {
    Paciente *inicio;
    Paciente *fim;
} HistoricoAtendimentos;

Fila *criarFila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

HistoricoAtendimentos *criarHistorico() {
    HistoricoAtendimentos *historico = (HistoricoAtendimentos *)malloc(sizeof(HistoricoAtendimentos));
    historico->inicio = NULL;
    historico->fim = NULL;
    return historico;
}

Paciente *criarPaciente(char *nome, int idade, char *motivoConsulta, int prioridade) {
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    strcpy(p->nome, nome);
    p->idade = idade;
    strcpy(p->motivoConsulta, motivoConsulta);
    p->prioridade = prioridade;
    p->proximo = NULL;
    return p;
}

void adicionarPaciente(Fila *f, Paciente *p) {
    if (f->inicio == NULL) {
        f->inicio = p;
        f->fim = p;
    } else {
        f->fim->proximo = p;
        f->fim = p;
    }
}

Paciente *atenderPaciente(Fila *filaUrgente, Fila *filaPrioritaria, Fila *filaNormal, int numeroConsultorio) {
    Paciente *p = NULL;
    if (filaUrgente->inicio != NULL) {
        p = filaUrgente->inicio;
        filaUrgente->inicio = filaUrgente->inicio->proximo;
    } else if (filaPrioritaria->inicio != NULL) {
        p = filaPrioritaria->inicio;
        filaPrioritaria->inicio = filaPrioritaria->inicio->proximo;
    } else if (filaNormal->inicio != NULL) {
        p = filaNormal->inicio;
        filaNormal->inicio = filaNormal->inicio->proximo;
    }

    if (p != NULL) {
        p->inicioAtendimento = time(NULL);
        p->fimAtendimento = 0;
        p->numeroConsultorio = numeroConsultorio;
    }

    return p;
}

void finalizarAtendimento(Paciente *p) {
    p->fimAtendimento = time(NULL);
}

void removerPaciente(Paciente *p) {
    free(p);
}

void visualizarFila(Fila *f) {
    Paciente *p = f->inicio;
    while (p != NULL) {
        printf("Nome: %s, Idade: %d, Motivo da Consulta: %s, Prioridade: %d\n",
               p->nome, p->idade, p->motivoConsulta, p->prioridade);
        p = p->proximo;
    }
}

void adicionarHistorico(HistoricoAtendimentos *historico, Paciente *p) {
    if (historico->inicio == NULL) {
        historico->inicio = p;
        historico->fim = p;
    } else {
        historico->fim->proximo = p;
        historico->fim = p;
    }
}

void visualizarHistorico(HistoricoAtendimentos *historico) {
    Paciente *p = historico->inicio;
    printf("Histórico de Atendimentos:\n");
    while (p != NULL) {
        printf("Nome: %s, Idade: %d, Motivo da Consulta: %s, Prioridade: %d, Consultório: %d\n",
               p->nome, p->idade, p->motivoConsulta, p->prioridade, p->numeroConsultorio);
        p = p->proximo;
    }
}

int main() {
    Fila *filaNormal = criarFila();
    Fila *filaPrioritaria = criarFila();
    Fila *filaUrgente = criarFila();
    HistoricoAtendimentos *historico = criarHistorico();

    char nome[50];
    int idade;
    char motivoConsulta[100];
    int prioridade;
    int opcao;
    int numeroConsultorio = 1;

    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Adicionar paciente\n");
        printf("2. Visualizar filas\n");
        printf("3. Atender paciente\n");
        printf("4. Visualizar histórico de atendimentos\n");
        printf("5. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do paciente: ");
                scanf("%s", nome);
                printf("Digite a idade do paciente: ");
                scanf("%d", &idade);
                printf("Digite o motivo da consulta: ");
                scanf("%s", motivoConsulta);
                printf("Digite a prioridade do paciente (1 para normal, 2 para prioritária, 3 para urgente): ");
                scanf("%d", &prioridade);

                if (prioridade == 1) {
                    adicionarPaciente(filaNormal, criarPaciente(nome, idade, motivoConsulta, prioridade));
                } else if (prioridade == 2) {
                    adicionarPaciente(filaPrioritaria, criarPaciente(nome, idade, motivoConsulta, prioridade));
                } else if (prioridade == 3) {
                    adicionarPaciente(filaUrgente, criarPaciente(nome, idade, motivoConsulta, prioridade));
                } else {
                    printf("Prioridade inválida.\n");
                }
                break;
            case 2:
                printf("\nFila Normal:\n");
                visualizarFila(filaNormal);
                printf("\nFila Prioritária:\n");
                visualizarFila(filaPrioritaria);
                printf("\nFila Urgente:\n");
                visualizarFila(filaUrgente);
                break;
            case 3:
                if (filaUrgente->inicio != NULL || filaPrioritaria->inicio != NULL || filaNormal->inicio != NULL) {
                    Paciente *p = atenderPaciente(filaUrgente, filaPrioritaria, filaNormal, numeroConsultorio);
                    printf("\nPaciente %s, dirija-se ao consultório %d.\n", p->nome, p->numeroConsultorio);
                    finalizarAtendimento(p);
                    adicionarHistorico(historico, p);
                    removerPaciente(p);
                    numeroConsultorio++;
                } else {
                    printf("\nNenhum paciente na fila.\n");
                }
                break;
            case 4:
                visualizarHistorico(historico);
                break;
            case 5:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpção inválida.\n");
        }
    } while (opcao != 5);

    return 0;
}
