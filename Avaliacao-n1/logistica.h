#ifndef LOGISTICA_H
#define LOGISTICA_H

#define MAX_CIDADE_LEN 50
#define MAX_CONTEUDO_LEN 100


typedef struct Pacote {
    int id;
    char origem[MAX_CIDADE_LEN];
    char destino[MAX_CIDADE_LEN];
    char conteudo[MAX_CONTEUDO_LEN];
    int status;
    struct Pacote* proximo;
} Pacote;


void incluirPacote(Pacote** listaPacotes, char origem[], char destino[], char conteudo[]);
void alterarStatus(Pacote** listaPacotes, int id, int novoStatus);
void rastrearPacote(Pacote* listaPacotes, int id);
void mostrarEntregas(Pacote* listaPacotes);
void listarTodosPacotes(Pacote* listaPacotes);

#endif
