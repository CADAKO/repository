#include "s21_calc.h"
int get_priority(char op) {
  int prioritet = 0;
  if (op == '+' || op == '-') prioritet = 1;
  if (op == '*' || op == '/' || op == '%') prioritet = 2;
  if (op == '#' || (op >= 'C' && op <= '~')) prioritet = 4;
  if (op == '^') prioritet = 3;
  return prioritet;
}

int calcbracketinfix(char *infix) {
  int bracketsbalance = 0;
  int err = 0;
  for (size_t i = 0; i < strlen(infix) && err == 0; i++) {
    if (infix[i] == '(') bracketsbalance++;
    if (infix[i] == ')') {
      bracketsbalance--;
      if (infix[i - 1] == '(') err = 1;
    }
    if (bracketsbalance < 0) err = 1;
  }
  if (bracketsbalance != 0) err = 1;
  return err;
}

char *infixToPostfix(char *infix) {
  char stack[MAX_SIZE];
  char *postfix = malloc(MAX_SIZE * 2 * sizeof(char));
  if (postfix != NULL) {
    int top = -1;
    int pos = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
      if (isdigit(infix[i])) {
        double num = atof(&infix[i]);
        while (isdigit(infix[i]) || infix[i] == '.') {
          i++;
        }
        i--;  // Вернемся на один шаг назад после считывания числа
        pos += sprintf(&postfix[pos], "%f ", num);
      } else if (infix[i] == '(') {
        stack[++top] = infix[i];
      } else if (infix[i] == ')') {
        while (top >= 0 && stack[top] != '(') {
          postfix[pos++] = stack[top--];
          postfix[pos++] = ' ';
        }
        top--;  // Убираем открывающую скобку из стека
      } else if (!isspace(infix[i])) {
        while (top >= 0 && get_priority(stack[top]) >= get_priority(infix[i])) {
          postfix[pos++] = stack[top--];
          postfix[pos++] = ' ';
        }
        stack[++top] = infix[i];
      } else if (i == 0 && infix[i] == '-') {
        postfix[pos++] = '~';
      } else if (i == 0 && infix[i] == '+') {
        postfix[pos++] = '#';
      } else if (infix[i - 1] == '(' && infix[i] == '-') {
        postfix[pos++] = '~';
      } else if (infix[i - 1] == '(' && infix[i] == '+')
        postfix[pos++] = '#';
    }

    while (top >= 0) {
      postfix[pos++] = stack[top--];
      postfix[pos++] = ' ';
    }

    postfix[pos] = '\0';  // Завершаем строку
  } else {
    fprintf(stderr, "Не удалось выделить память для постфиксной строки.\n");
  }
  return postfix;
}

double calc(char *infix) {
  double res = NAN;
  char *postfix = infixToPostfix(infix);
  if (postfix != NULL) {
    double stack[MAX_SIZE];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
      if (isdigit(postfix[i])) {
        double num = atof(&postfix[i]);
        while (isdigit(postfix[i]) || postfix[i] == '.') {
          i++;
        }
        i--;  // Вернемся на один шаг назад после считывания числа
        stack[++top] = num;
      } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' ||
                 postfix[i] == '/' || postfix[i] == '%' || postfix[i] == '^') {
        double operand2 = stack[top--];
        double operand1 = stack[top--];

        switch (postfix[i]) {
          case '+':
            stack[++top] = operand1 + operand2;
            break;
          case '-':
            stack[++top] = operand1 - operand2;
            break;
          case '*':
            stack[++top] = operand1 * operand2;
            break;
          case '/':
            stack[++top] = operand1 / operand2;
            break;
          case '%':
            stack[++top] = fmod(operand1, operand2);
            break;
          case '^':
            stack[++top] = pow(operand1, operand2);
            break;
        }
      } else if (postfix[i] == '~' || postfix[i] == '#' ||
                 (postfix[i] >= 'A' && postfix[i] <= 'z')) {
        double operand1 = stack[top--];
        switch (postfix[i]) {
          case '~':
            stack[++top] = -operand1;
            break;
          case '#':
            stack[++top] = +operand1;
            break;
          case 's':
            stack[++top] = sin(operand1);
            break;
          case 'c':
            stack[++top] = cos(operand1);
            break;
          case 't':
            stack[++top] = tan(operand1);
            break;
          case 'S':
            stack[++top] = asin(operand1);
            break;
          case 'C':
            stack[++top] = acos(operand1);
            break;
          case 'T':
            stack[++top] = atan(operand1);
            break;
          case 'l':
            stack[++top] = log(operand1);
            break;
          case 'L':
            stack[++top] = log10(operand1);
            break;
          case 'Q':
            stack[++top] = sqrt(operand1);
            break;
        }
      }
    }
    res = stack[top];
    free(postfix);
  }
  return res;
}

// int main()
// {
//    char *infixExpression = "s(~0.01)";

//    printf("Инфиксное выражение: %s\n", infixExpression);
//    //    printf("Постфиксное выражение: %s\n", postfixExpression);

//    double result = calc(infixExpression);
//    printf("Значение постфиксного выражения: %f\n", result);

//     char* infixExpressionb = "";
//     int resultb = calcbracketinfix(infixExpressionb);
//        printf("скобки = %d\n", resultb);
//    //    free(postfixExpression);

//    return 0;
// }
