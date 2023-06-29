#include "calc.h"

//#define malloc(x) NULL

int start(char* inputStr, double* result, double x) {
  Stack infixStack;
  Stack reverseInfixStack;
  Stack operationStack;
  int check = OK;
  init(&infixStack);
  init(&reverseInfixStack);
  init(&operationStack);
  if (checkString(inputStr) == OK && strlen(inputStr) > 0 &&
      strlen(inputStr) < 260) {
    if (parserStrToStack(inputStr, &infixStack)) {
      reverseStack(&infixStack, &reverseInfixStack);
      stackToPolish(&reverseInfixStack, &operationStack, &infixStack);
      reverseStack(&infixStack, &reverseInfixStack);
      *result = calculating(&reverseInfixStack, x);
    } else {
      check = ERROR;
      *result = 0;
    }
  } else {
    check = ERROR;
    *result = 0;
  }
  if (isnan(*result)) {
    *result = 0;
    check = NaN;
  }
  if (isinf(*result)) {
    *result = 0;
    check = InF;
  }
  return check;
}

// Validators

int checkString(char* str) {
  int correctStr = OK;
  if (checkBrackets(str) && checkDots(str) && checkFunctions(str) &&
      checkXBiFunctions(str)) {
    correctStr = OK;
  } else {
    correctStr = ERROR;
  }
  return correctStr;
}

int checkFunctions(char* str) {
  int correctStr = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && correctStr == OK; i++) {
    if (str[i] == '+' || str[i] == '-') {
      if (i == strLength - 1) correctStr = ERROR;
      if (i != 0 && i != strLength - 1) {
        if (i > 0 &&
            (str[i + 1] == ')' || str[i + 1] == '/' || str[i + 1] == '*' ||
             str[i + 1] == '^' || str[i - 1] == '-' || str[i - 1] == '+'))
          correctStr = ERROR;
        if (i > 0 &&
            (str[i - 1] == '/' || str[i - 1] == '*' || str[i - 1] == '^' ||
             str[i - 1] == '-' || str[i - 1] == '+'))
          correctStr = ERROR;
      }
    }
    if (str[i] == '/' || str[i] == '*' || str[i] == '^') {
      if (i == 0 || i == strLength - 1) correctStr = ERROR;
      if (i != 0 && i != strLength - 1) {
        if (i > 0 &&
            (str[i + 1] == ')' || str[i + 1] == '/' || str[i + 1] == '*' ||
             str[i + 1] == '^' || str[i - 1] == '-' || str[i - 1] == '+'))
          correctStr = ERROR;
        if (i > 0 &&
            (str[i - 1] == '(' || str[i - 1] == '/' || str[i - 1] == '*' ||
             str[i - 1] == '^' || str[i - 1] == '-' || str[i - 1] == '+'))
          correctStr = ERROR;
      }
    }
    if (str[i] == 'm') {
      if (i == 0 || i > strLength - 4) correctStr = ERROR;
      if (i != 0 || i < strLength - 4) {
        if (i > 0 && str[i - 1] != ')' && !isdigit(str[i - 1]) &&
            str[i - 1] != 'x')
          correctStr = ERROR;
        if (!isdigit(str[i + 3]) && str[i + 3] != '(' && str[i + 3] != 'x')
          correctStr = ERROR;
      }
      i = i + 2;
    }
  }
  return correctStr;
}

int checkXBiFunctions(char* str) {
  int correctStr = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && correctStr == OK; i++) {
    if (str[i] == 'c' || str[i] == 't' ||
        (str[i] == 's' && str[i + 1] == 'i') ||
        (str[i] == 'l' && str[i + 1] == 'o')) {
      if (i > strLength - 6) correctStr = ERROR;
      if (i != 0 || i < strLength - 6) {
        if (i > 0 &&
            (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'x'))
          correctStr = ERROR;
      }
      i = i + 2;
    }
    if (str[i] == 'a' || (str[i] == 's' && str[i + 1] == 'q')) {
      if (i > strLength - 7) correctStr = ERROR;
      if (i != 0 || i < strLength - 7) {
        if (i > 0 &&
            (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'x'))
          correctStr = ERROR;
      }
      i = i + 3;
    }
    if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i > strLength - 5) correctStr = ERROR;
      if (i != 0 || i < strLength - 5) {
        if (i > 0 &&
            (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'x'))
          correctStr = ERROR;
      }
      i++;
    }
    if (str[i] == 'x') {
      if (i == 0 &&
          (isdigit(str[i + 1]) || str[i + 1] == '(' || str[i + 1] == 'x'))
        correctStr = ERROR;
      if (i == strLength - 1 &&
          (isdigit(str[i - 1]) || str[i - 1] == ')' || str[i - 1] == 'x'))
        correctStr = ERROR;
      if (i > 0 && i < strLength - 1 &&
          (isdigit(str[i + 1]) || str[i + 1] == '(' || str[i + 1] == 'x'))
        correctStr = ERROR;
      if (i > 0 && i < strLength - 1 &&
          (isdigit(str[i - 1]) || str[i - 1] == ')' || str[i - 1] == 'x'))
        correctStr = ERROR;
    }
  }
  return correctStr;
}

int checkDots(char* str) {
  int correctStr = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && correctStr == OK; i++) {
    int dotsCount = 0;
    if ((str[i] >= '0' && str[i] <= '9')) {
      while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
        if (str[i] == '.') dotsCount++;
        i++;  // двигаем цикл while
      }
      i--;  // цикл закончился не на цифре, поэтому двинем на 1 назад чтоб сам
            // цикл for сделал перемещение указателя
    }
    if (dotsCount > 1) correctStr = ERROR;
    if (str[i] == '.') correctStr = ERROR;
  }
  return correctStr;
}

int checkBracketsPosition(char* str) {
  int strLength = strlen(str);
  int correctStr = OK;
  for (int i = 0; str[i] != '\0'; i++) {
    if (i == 0 && str[i] == ')') correctStr = ERROR;
    if (i == strLength - 1 && str[i] == '(') correctStr = ERROR;
    // для открывающейся скобки
    if (str[i] == '(' && i != 0) {
      if (str[i - 1] == ')' || isdigit(str[i - 1])) correctStr = ERROR;
      if (str[i + 1] == ')') correctStr = ERROR;
    }
    if (str[i] == ')' && i != 0) {
      if (str[i + 1] == '(' || isdigit(str[i + 1])) correctStr = ERROR;
      if (str[i - 1] == '(') correctStr = ERROR;
    }
  }
  return correctStr;
}

int checkBrackets(char* str) {
  int open_bracket = 0;
  int close_bracket = 0;
  int correctStr = OK;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') {
      open_bracket++;
      if (str[i + 1] == ')') correctStr = ERROR;
    }
    if (str[i] == ')') {
      close_bracket++;
      if (close_bracket > open_bracket) correctStr = ERROR;
    }
  }
  if (close_bracket != open_bracket) correctStr = ERROR;
  if (correctStr == OK) {
    correctStr = checkBracketsPosition(str);
  }
  return correctStr;
}

// Calculator Functions

double calculating(Stack* polishStack, double x) {
  Stack calculatingStack;
  double result = 0;
  init(&calculatingStack);
  while (polishStack->top != NULL) {
    if (polishStack->top->type == s21_num || polishStack->top->type == s21_x) {
      if (polishStack->top->type == s21_x) {
        push(&calculatingStack, x, s21_num, polishStack->top->priority);
      } else {
        push(&calculatingStack, polishStack->top->data, polishStack->top->type,
             polishStack->top->priority);
      }
      pop(polishStack);
    } else if (polishStack->top->type != s21_num) {
      double value = 0;
      if (polishStack->top->priority == 4) {
        if (polishStack->top->type == s21_cos)
          value = cos(calculatingStack.top->data);
        if (polishStack->top->type == s21_sin)
          value = sin(calculatingStack.top->data);
        if (polishStack->top->type == s21_tan)
          value = tan(calculatingStack.top->data);
        if (polishStack->top->type == s21_acos)
          value = acos(calculatingStack.top->data);
        if (polishStack->top->type == s21_asin)
          value = asin(calculatingStack.top->data);
        if (polishStack->top->type == s21_atan)
          value = atan(calculatingStack.top->data);
        if (polishStack->top->type == s21_sqrt)
          value = sqrt(calculatingStack.top->data);
        if (polishStack->top->type == s21_log)
          value = log10(calculatingStack.top->data);
        if (polishStack->top->type == s21_ln)
          value = log(calculatingStack.top->data);
        pop(&calculatingStack);
        pop(polishStack);
        push(&calculatingStack, value, s21_num, 0);
      } else {
        double first = pop(&calculatingStack);
        double second = pop(&calculatingStack);
        if (polishStack->top->type == s21_plus) value = second + first;
        if (polishStack->top->type == s21_minus) value = second - first;
        if (polishStack->top->type == s21_mult) value = second * first;
        if (polishStack->top->type == s21_div) value = second / first;
        if (polishStack->top->type == s21_mod) value = fmod(second, first);
        if (polishStack->top->type == s21_pow) value = pow(second, first);
        pop(polishStack);
        push(&calculatingStack, value, s21_num, 0);
      }
    }
  }
  result = calculatingStack.top->data;
  pop(&calculatingStack);
  return result;
}

void stackToPolish(Stack* inputStack, Stack* operationStack,
                   Stack* outputStack) {
  while (inputStack->top != NULL) {
    if (inputStack->top->type == s21_num ||
        inputStack->top->type == s21_x) {  // если число кидаем сразу в Аутпут
      push(outputStack, inputStack->top->data, inputStack->top->type,
           inputStack->top->priority);
    } else if (inputStack->top->priority == 4 ||
               inputStack->top->type ==
                   s21_open) {  // если функция или открывающая скобка - сразу
                                // кидаем в Операции
      push(operationStack, inputStack->top->data, inputStack->top->type,
           inputStack->top->priority);
    } else if (inputStack->top->type ==
               s21_close) {  // процесс когда встречается закрывающая
      while (operationStack->top != NULL &&
             operationStack->top->type != s21_open) {
        push(outputStack, operationStack->top->data, operationStack->top->type,
             operationStack->top->priority);
        pop(operationStack);
      }
      if (operationStack->top != NULL) pop(operationStack);
    } else if (operationStack->top == NULL ||
               (inputStack->top->priority >
                operationStack->top->priority)) {  // если приоритет выше или
                                                   // стэк с Операциями пуст
      push(operationStack, inputStack->top->data, inputStack->top->type,
           inputStack->top->priority);
    } else if ((operationStack->top != NULL) &&
               (inputStack->top->priority <= operationStack->top->priority) &&
               inputStack->top->type !=
                   s21_close) {  // если стэк операций не пуст и приоритет
                                 // инпута ниже чем у топа в Операциях то тогда
                                 // начинаем переносить
      if (operationStack->top->priority == 3 &&
          inputStack->top->priority == 3) {  // возведение правоассициативное
        push(operationStack, inputStack->top->data, inputStack->top->type,
             inputStack->top->priority);
      } else {
        while ((operationStack->top != NULL) &&
               (inputStack->top->priority <= operationStack->top->priority)) {
          push(outputStack, operationStack->top->data,
               operationStack->top->type, operationStack->top->priority);
          pop(operationStack);
        }
        push(operationStack, inputStack->top->data, inputStack->top->type,
             inputStack->top
                 ->priority);  // в конце пушим в Операцию нашу лексему
      }
    }
    pop(inputStack);
  }

  if (inputStack->top == NULL && operationStack->top != NULL) {
    while (operationStack->top != NULL) {
      push(outputStack, operationStack->top->data, operationStack->top->type,
           operationStack->top->priority);
      pop(operationStack);
    }
  }
}

void reverseStack(Stack* oldstack, Stack* newstack) {
  while (oldstack->top != NULL) {
    double data = oldstack->top->data;
    int type = oldstack->top->type;
    int priority = oldstack->top->priority;
    push(newstack, data, type, priority);
    pop(oldstack);
  }
}

// Parsers (with perfect-ready math string)

int parserStrToStack(char* inputStr, Stack* stack) {
  char tempBuff[300] = {0};
  int strLength = (int)strlen(inputStr);
  int check_plus = 0;
  int check_minus = 0;
  int error = OK;
  for (int i = 0; i < strLength && error == OK; i++) {
    if (parseNumbers(inputStr, stack, tempBuff, &i, &check_minus,
                     &check_plus) == ERROR) {
      error = ERROR;
    } else {
      parseZeroPriority(inputStr, stack, i);
      parseFirstPriority(inputStr, stack, i, &check_minus, &check_plus);
      parseSecondPriority(inputStr, stack, &i);
      parseThirdPriority(inputStr, stack, i);
      parseFourthPriority(inputStr, stack, &i);
    }
  }
  return error;
}

void parseFourthPriority(char* inputStr, Stack* stack, int* i) {
  if (inputStr[*i] == 'c') {
    push(stack, 0, s21_cos, 4);
    *i = *i + 2;
  } else if (inputStr[*i] == 't') {
    push(stack, 0, s21_tan, 4);
    *i = *i + 2;
  } else if (inputStr[*i] == 's') {
    if (inputStr[*i + 1] == 'i') {
      push(stack, 0, s21_sin, 4);
      *i = *i + 2;
    } else {
      push(stack, 0, s21_sqrt, 4);
      *i = *i + 3;
    }
  } else if (inputStr[*i] == 'l') {
    if (inputStr[*i + 1] == 'o') {
      push(stack, 0, s21_log, 4);
      *i = *i + 2;
    } else {
      push(stack, 0, s21_ln, 4);
      *i = *i + 1;
    }
  } else if (inputStr[*i] == 'a') {
    if (inputStr[*i + 1] == 's') {
      push(stack, 0, s21_asin, 4);
    } else if (inputStr[*i + 1] == 'c') {
      push(stack, 0, s21_acos, 4);
    } else {
      push(stack, 0, s21_atan, 4);
    }
    *i = *i + 3;
  }
}

void parseThirdPriority(char* inputStr, Stack* stack, int i) {
  if (inputStr[i] == '^') {
    push(stack, 0, s21_pow, 3);
  }
}

void parseSecondPriority(char* inputStr, Stack* stack, int* i) {
  if (inputStr[*i] == '*') {
    push(stack, 0, s21_mult, 2);
  } else if (inputStr[*i] == '/') {
    push(stack, 0, s21_div, 2);
  } else if (inputStr[*i] == 'm') {
    push(stack, 0, s21_mod, 2);
    *i = *i + 2;
  }
}

void parseFirstPriority(char* inputStr, Stack* stack, int i, int* check_minus,
                        int* check_plus) {
  if (inputStr[i] == '+') {
    if (i == 0 || (inputStr[i - 1] == '(')) {
      *check_plus = 1;
    } else {
      push(stack, 0, s21_plus, 1);
    }
  } else if (inputStr[i] == '-') {
    if (i == 0 || (inputStr[i - 1] == '(')) {  // может уберу
      push(stack, 0, s21_num, 0);
      push(stack, 0, s21_minus, 1);
      *check_minus = 0;
    } else {
      push(stack, 0, s21_minus, 1);
    }
  }
}
void parseZeroPriority(char* inputStr, Stack* stack, int i) {
  if (inputStr[i] == '(') {
    push(stack, 0, s21_open, 0);
  } else if (inputStr[i] == ')') {
    push(stack, 0, s21_close, 0);
  } else if (inputStr[i] == 'x') {
    push(stack, 0, s21_x, 0);
  }
}

int parseNumbers(char* inputStr, Stack* stack, char* tempBuff, int* i,
                 int* check_minus, int* check_plus) {
  double data = 0;
  int correctNum = OK;
  if (inputStr[*i] >= '0' && inputStr[*i] <= '9') {
    int start = *i;
    int x = 0;
    while ((inputStr[start] >= '0' && inputStr[start] <= '9') ||
           (inputStr[start] == '.')) {
      tempBuff[x] = inputStr[start];
      x++;
      start++;
    }
    *i = start - 1;
    if (strlen(tempBuff) > 1 && tempBuff[0] == '0' && tempBuff[1] != '.') {
      correctNum = ERROR;
    } else {
      data = atof(tempBuff);
      if (*check_minus == 1) {
        data = data * -1;
      }
      push(stack, data, s21_num, 0);
      size_t clean = sizeof(tempBuff);
      memset(tempBuff, '\0', clean);
    }
  }
  *check_minus = 0;
  *check_plus = 0;
  return correctNum;
}

// Stack functions

void init(Stack* stack) { stack->top = NULL; }

void push(Stack* stack, double data, int type, int priority) {
  Node* head = malloc(sizeof(Node));
  if (head == NULL) exit(0);
  head->data = data;
  head->priority = priority;
  head->type = type;
  head->next = stack->top;
  stack->top = head;
}

double pop(Stack* stack) {
  if (stack->top == NULL) {
    return 0;
  }
  double data = stack->top->data;
  Node* tmp = stack->top;
  stack->top = stack->top->next;
  free(tmp);
  return data;
}

void credit(double* total_amount, int term, double percents,
            double* monthly_pay, double* first_pay, double* overpay,
            double* total_pay, int type) {
  double save = *total_amount;
  if (type == 1) {
    percents = percents / 12 / 100;
    double k =
        (percents)*pow(1 + (percents), term) / (pow(1 + percents, term) - 1);
    *monthly_pay = k * (*total_amount);
    *total_pay = *monthly_pay * term;
  } else {
    percents = percents / 100;
    double main_pay = (*total_amount) / term;
    for (int i = 1; i <= term; i++) {
      double full_pay = main_pay + (*total_amount) * percents / 12;
      if (i == 1) *first_pay = full_pay;
      *monthly_pay = full_pay;
      *total_pay = *total_pay + full_pay;
      (*total_amount) = (*total_amount) - main_pay;
    }
  }
  *overpay = *total_pay - save;
}
