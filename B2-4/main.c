#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_NAME_LEN 100

typedef struct Paciente {
  int idPaciente;
  int idSenha;
  char nomePaciente[MAX_NAME_LEN];
  int idadePaciente;
  char especialidade[MAX_NAME_LEN];
  time_t inicio_atendimento;
  time_t termino_atendimento;
  struct Paciente *proximo;
} Paciente;

typedef struct Fila {
  Paciente *frente;
  Paciente *tras;
} Fila;

typedef struct {
  int idMedico;
  char nomeMedico[MAX_NAME_LEN];
  char especialidade[MAX_NAME_LEN];
} Medico;

typedef struct {
  int idAtendimento;
  int idMedico;
  int numeroConsultorio;
  char dataAtendimento[11]; // Formato "YYYY-MM-DD"
  char horaAtendimento[6];  // Formato "HH:MM"
} Atendimento;

typedef struct {
  int idSenha;
  char textoSenha[MAX_NAME_LEN];
  char tipoAtendimento[MAX_NAME_LEN];
  int posicaoFila;
} Painel;

typedef struct {
  int idHistorico;
  int idSenha;
  char textoSenha[MAX_NAME_LEN];
  int posicaoFila;
  char dataAtendimento[11]; // Formato "YYYY-MM-DD"
  char horaAtendimento[6];  // Formato "HH:MM"
} HistoricoChamada;

// Funções para manipulação das filas
void inicializar_fila(Fila *fila) {
  fila->frente = NULL;
  fila->tras = NULL;
}

int fila_vazia(Fila *fila) { return fila->frente == NULL; }

void adicionar_paciente(Fila *fila, int idPaciente, int idSenha,
                        const char *nome, int idade,
                        const char *especialidade) {
  Paciente *novo_paciente = (Paciente *)malloc(sizeof(Paciente));
  novo_paciente->idPaciente = idPaciente;
  novo_paciente->idSenha = idSenha;
  strncpy(novo_paciente->nomePaciente, nome, MAX_NAME_LEN);
  novo_paciente->idadePaciente = idade;
  strncpy(novo_paciente->especialidade, especialidade, MAX_NAME_LEN);
  novo_paciente->inicio_atendimento = 0;
  novo_paciente->termino_atendimento = 0;
  novo_paciente->proximo = NULL;

  if (fila_vazia(fila)) {
    fila->frente = novo_paciente;
  } else {
    fila->tras->proximo = novo_paciente;
  }
  fila->tras = novo_paciente;
}

Paciente *remover_paciente(Fila *fila) {
  if (fila_vazia(fila)) {
    return NULL;
  }
  Paciente *paciente_removido = fila->frente;
  fila->frente = fila->frente->proximo;
  if (fila->frente == NULL) {
    fila->tras = NULL;
  }
  return paciente_removido;
}

void atender_paciente(Paciente *paciente, Atendimento *atendimento) {
  time(&paciente->inicio_atendimento);
  printf("Atendendo paciente: %s\n", paciente->nomePaciente);
  printf("Motivo: %s\n", paciente->especialidade);
  printf("Início do atendimento: %s", ctime(&paciente->inicio_atendimento));
  // Simulando o término do atendimento após 5 segundos
  sleep(5);
  time(&paciente->termino_atendimento);
  printf("Término do atendimento: %s", ctime(&paciente->termino_atendimento));

  // Registrar dados de atendimento
  strncpy(atendimento->dataAtendimento, "2023-12-31", 11);
  strncpy(atendimento->horaAtendimento, "10:30", 6);
}

void exibir_fila(Fila *fila) {
  Paciente *atual = fila->frente;
  while (atual != NULL) {
    printf("Nome: %s, Idade: %d, Motivo: %s\n", atual->nomePaciente,
           atual->idadePaciente, atual->especialidade);
    atual = atual->proximo;
  }
}

void exibirPainel(Painel *painel) {
  printf("Senha: %s, Tipo de Atendimento: %s, Posição na Fila: %d\n",
         painel->textoSenha, painel->tipoAtendimento, painel->posicaoFila);
}

void registrarHistorico(HistoricoChamada *historico, int idSenha,
                        const char *texto, int posicao, const char *data,
                        const char *hora) {
  historico->idSenha = idSenha;
  strncpy(historico->textoSenha, texto, MAX_NAME_LEN);
  historico->posicaoFila = posicao;
  strncpy(historico->dataAtendimento, data, 11);
  strncpy(historico->horaAtendimento, hora, 6);
}

void gerenciar_atendimentos(Fila *fila_normal, Fila *fila_prioritaria,
                            Fila *fila_urgente, int n,
                            Atendimento *atendimento) {
  int contador_normal = 0;
  while (!fila_vazia(fila_urgente) || !fila_vazia(fila_prioritaria) ||
         !fila_vazia(fila_normal)) {
    if (!fila_vazia(fila_urgente)) {
      Paciente *paciente = remover_paciente(fila_urgente);
      atender_paciente(paciente, atendimento);
      free(paciente);
    } else if (contador_normal < n && !fila_vazia(fila_normal)) {
      Paciente *paciente = remover_paciente(fila_normal);
      atender_paciente(paciente, atendimento);
      free(paciente);
      contador_normal++;
    } else if (!fila_vazia(fila_prioritaria)) {
      Paciente *paciente = remover_paciente(fila_prioritaria);
      atender_paciente(paciente, atendimento);
      free(paciente);
      contador_normal = 0;
    } else {
      contador_normal = 0;
    }
  }
}

int main() {
  Fila fila_normal, fila_prioritaria, fila_urgente;
  inicializar_fila(&fila_normal);
  inicializar_fila(&fila_prioritaria);
  inicializar_fila(&fila_urgente);

  Atendimento atendimento;
  Painel painel;
  HistoricoChamada historico;

  adicionar_paciente(&fila_normal, 1, 101, "Paciente Normal 1", 30,
                     "Consulta de rotina");
  adicionar_paciente(&fila_prioritaria, 2, 102, "Paciente Prioritário 1", 65,
                     "Consulta de rotina");
  adicionar_paciente(&fila_urgente, 3, 103, "Paciente Urgente 1", 50,
                     "Dor intensa");

  printf("Fila Normal:\n");
  exibir_fila(&fila_normal);
  printf("\nFila Prioritária:\n");
  exibir_fila(&fila_prioritaria);
  printf("\nFila Urgente:\n");
  exibir_fila(&fila_urgente);

  printf("\nGerenciando atendimentos:\n");
  gerenciar_atendimentos(&fila_normal, &fila_prioritaria, &fila_urgente, 2,
                         &atendimento);

  return 0;
}
