#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct {
    double items[MAX_STACK_SIZE];
    int top;
} Stack;


void initialize(Stack *s) {
    s->top = -1;
}


int isEmpty(Stack *s) {
    return s->top == -1;
}


int isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}


void push(Stack *s, double value) {
    if (isFull(s)) {
        printf("Erro: Pilha cheia!\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}


double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia!\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}


double operate(double operand1, double operand2, char operator) {
    switch(operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                printf("Erro: Divisão por zero!\n");
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        default:
            printf("Erro: Operador inválido!\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    Stack stack;
    initialize(&stack);

    printf("Digite a expressão RPN (Operadores: +, -, *, /): ");
    char token;
    double operand1, operand2;
    while ((token = getchar()) != '\n') {
        if (isdigit(token) || (token == '.')) {
            ungetc(token, stdin);
            scanf("%lf", &operand1);
            push(&stack, operand1);
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            push(&stack, operate(operand1, operand2, token));
        }
    }

    double result = pop(&stack);
    printf("Resultado da operação: %.2lf\n", result);

    return 0;
}
