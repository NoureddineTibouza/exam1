#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 100
typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;
void initStack(Stack* stack) {
    stack->top = -1;
}
int is_empty(const Stack* stack) {
    return stack->top == -1;
}
int is_full(const Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}
void push(Stack* stack, int item) {
    if (is_full(stack)) {
        printf("Stack Overflow! Cannot push %d\n", item);
        return;
    }
    stack->items[++stack->top] = item;
}
int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;
    }
    return stack->items[stack->top--];
}
int peek(const Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return stack->items[stack->top];
}
void clear(Stack* stack) {
    stack->top = -1;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
int apply_operator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}
void infix_to_postfix(const char* infix, char* postfix) {
    Stack operators;
    initStack(&operators);
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isdigit(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(&operators, c);
        } else if (c == ')') {
            while (!is_empty(&operators) && peek(&operators) != '(') {
                postfix[k++] = pop(&operators);
            }
            pop(&operators);
        } else if (is_operator(c)) {
            while (!is_empty(&operators) && precedence(peek(&operators)) >= precedence(c)) {
                postfix[k++] = pop(&operators);
            }
            push(&operators, c);
        }
    }
    while (!is_empty(&operators)) {
        postfix[k++] = pop(&operators);
    }
    postfix[k] = '\0';
}
int evaluate_postfix(const char* postfix) {
    Stack operands;
    initStack(&operands);
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            push(&operands, c - '0');
        } else if (is_operator(c)) {
            int b = pop(&operands);
            int a = pop(&operands);
            int result = apply_operator(a, b, c);
            push(&operands, result);
        }
    }
    return pop(&operands);
}
int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    printf("Enter a valid infix expression: ");
    scanf("%s", infix);
    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);
    return 0;
}
