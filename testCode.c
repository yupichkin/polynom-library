#include "Poly.h"
#include "locale.h"
#pragma warning(disable: 4996)
int main(void) {
  int isEOF = 0;
  int number;
  int result;
  poly_t polynom;
  poly_t polynom1;
  poly_t polynom2;
  FILE* readingStream = stdin;
  FILE* writingStream = stdout;
  setlocale(LC_CTYPE, "Russian");
  printf("Введите полином с переменной x и целочисленными коэффициентами:\n");
  polynom1 = PolyRead(stdin, &isEOF);
  printf("Результат чтения функции Parse и вывода функции Format:\n");
  PolyWrite(stdout, polynom1);
  printf("Результат задания полинома функцией с переменным кол-вом аргументов From:\n");
  polynom2 = PolyFrom(5, 1, 2, 3, 4, 5);
  PolyWrite(stdout, polynom2);
  printf("Результат сложения полиномов функцией Add:\n");
  polynom = PolyAdd(polynom1, polynom2);
  PolyWrite(stdout, polynom);
  printf("Результат вычитания полиномов функцией Sub:\n");
  polynom = PolySub(polynom1, polynom2);
  PolyWrite(stdout, polynom);
  printf("Результат умножения полиномов функцией Mul:\n");
  polynom = PolyMul(polynom1, polynom2);
  PolyWrite(stdout, polynom);
  printf("Введите целочисленное число:\n");
  scanf("%i", &number);
  printf("Значение полинома в этом числе:\n");
  result = Evaluate(polynom1, number);
  printf("%i\n", result);
  printf("Результат умножения полинома на это число:\n");
  polynom = PolyMulInt(polynom1, number);
  PolyWrite(stdout, polynom);
  printf("Введите степень коэффициента:\n");
  scanf("%i", &number);
  result = PolyELEMENT(polynom1, number);
  printf("Значение коэффициента при этой степени:\n");
  printf("%i\n", result);
  _getch();
  return 0;
}
