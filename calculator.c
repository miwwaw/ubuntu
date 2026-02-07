#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100


typedef struct {
    double datos[MAX];
    int top;
} Stack;


void init(Stack *s) {
    s->top = -1;
}


int isEmpty(Stack *s) {
    return s->top == -1;
}


void push(Stack *s, double val) {
    if (s->top < MAX - 1) {
        s->datos[++s->top] = val;
    } else {
        printf("Error: pila llena\n");
    }
}


double pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->datos[s->top--];
    } else {
        printf("Error: pila vacía\n");
        return 0;
    }
}

int main() {
    Stack pila;
    init(&pila);

    char entrada[50];

    printf("Calculadora RPN\n");
    printf("Ingrese numeros u operadores (+ - * /)\n");
    printf("Escriba q para salir\n\n");

    while (1) {
        printf("> ");
        scanf("%s", entrada);


        if (strcmp(entrada, "q") == 0) {
            break;
        }


        if (isdigit(entrada[0]) || 
           (entrada[0] == '-' && isdigit(entrada[1]))) {
            push(&pila, atof(entrada));
        }

        else {
            double b = pop(&pila);
            double a = pop(&pila);
            double res;

            switch (entrada[0]) {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = a - b;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        printf("Error: division por cero\n");
                        push(&pila, a);
                        push(&pila, b);
                        continue;
                    }
                    res = a / b;
                    break;
                default:
                    printf("Operador no valido\n");
                    push(&pila, a);
                    push(&pila, b);
                    continue;
            }

            push(&pila, res);
            printf("Resultado: %.2f\n", res);
        }
    }

    printf("Saliendo de la calculadora RPN...\n");
    return 0;
}
