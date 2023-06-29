//
// Created by Oznak Banshee on 4/7/23.
//

#ifndef SMART_CALC_MAIN_H
#define SMART_CALC_MAIN_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define OK 1
#define NaN 2
#define InF 3

// Определение структуры узла списка
typedef struct Node {
  double data;
  int type;
  struct Node* next;
  int priority;
} Node;

// Определение структуры стека
typedef struct Stack {
  Node* top;
} Stack;

typedef enum operation {
  s21_num,
  s21_x,
  s21_open,
  s21_close,
  s21_plus,
  s21_minus,
  s21_mult,
  s21_div,
  s21_pow,
  s21_mod,
  s21_cos,
  s21_sin,
  s21_tan,
  s21_acos,
  s21_asin,
  s21_atan,
  s21_sqrt,
  s21_log,
  s21_ln,
  s21_un_plus,
  s21_un_minus
} operations;

void credit(double* total_amount, int term, double percents,
            double* monthly_pay, double* first_pay, double* overpay,
            double* total_pay, int type);

void push(Stack* stack, double data, int type, int priority);
void init(Stack* stack);
double pop(Stack* stack);

int start(char* inputStr, double* result, double x);

int parserStrToStack(char* inputStr, Stack* stack);
int parseNumbers(char* inputStr, Stack* stack, char* tempBuff, int* i,
                 int* check_minus, int* check_plus);
void parseZeroPriority(char* inputStr, Stack* stack, int i);
void parseFirstPriority(char* inputStr, Stack* stack, int i, int* check_minus,
                        int* check_plus);
void parseSecondPriority(char* inputStr, Stack* stack, int* i);
void parseThirdPriority(char* inputStr, Stack* stack, int i);
void parseFourthPriority(char* inputStr, Stack* stack, int* i);
void reverseStack(Stack* oldstack, Stack* newstack);
void stackToPolish(Stack* inputStack, Stack* operationStack,
                   Stack* outputStack);

double calculating(Stack* polishStack, double x);

int checkString(char* str);
int checkBrackets(char* str);
int checkBracketsPosition(char* str);
int checkDots(char* str);
int checkFunctions(char* str);
int checkXBiFunctions(char* str);

#endif  // SMART_CALC_MAIN_H
