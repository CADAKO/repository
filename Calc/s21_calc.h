#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int calcbracketinfix(char *infix);
double calc(char *infix);
char *infixToPostfix(char *infix);
int get_priority(char op);
