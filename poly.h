#if !defined POLY_H_INCLUDED
#define POLY_H
#pragma once
/**
 * @mainpage Introduction

Polylib представляет собой простейшую библиотеку для проведения
лабораторных работ в рамках консольных приложений для Windows. Она позволяет
на делать несложные операции с полиномами.

Минимальная программа с использованием библиотеки выглядит следующим образом:

@code{.c}
#include "Poly.h"

int main(void) {
  int isEOF = 0;
  poly_t polynom;
  poly_t polynom1;
  poly_t polynom2;
  FILE* stream = stdin;
  polynom1 = PolyRead(stdin, &isEOF);
  PolyWrite(stdout, polynom1);

  polynom2 = PolyFrom(5, 1, 2, 3, 4, 5);
  PolyWrite(stdout, polynom2);

  polynom = PolyAdd(polynom1, polynom2);
  PolyWrite(stdout, polynom);

  return 0;
}

@endcode

Эта программа инициализирует библиотеку и, в случае успеха, ждёт ввода пользователем
тривиального полинома (к примеру: 2x^2 - x + 1). После программа выводит в текстовом формате
полином пользователя и полином: "x^4+2x^3+3x^2+4x+5". Затем программа выводит результат 
сложения пользовательского полинома и полинома: "x^4+2x^3+3x^2+4x+5".

Обратите внимание на переменную isEOF. В случае чтения после достижения конца потока при чтении из файла,
функция PolyRead вернёт полином 0-ой степени с коэффициентом 0.

Результат выполнения программы в стандартном вводе-выводе(stdin-stdout):

@image html example.png

  \version 1.1
  \date 23.04.2019

*/
#define right 1
#define left -1

#include <stdio.h>
#include <crtdbg.h>
#include <stdlib.h> 
#include <malloc.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>

typedef enum {
  ERROR_OK,
  ERROR_USER_WRITING,
  ERROR_MEMORY,
  ERROR_UNKNOWN
} error_t;

/*!
  \brief Структура полинома типа poly_t
  \param degree степень полинома
  \param coefficients указатель на массив коэффициентов полинома

  Структура полинома содержит в себе степень полинома и указатель на массив коэффициентов полинома, типов int
  */
typedef struct {
	int degree;
	int* coefficients;
} poly_t;

/*!
  \brief Перечисление типа ошибок error_t

  Перечисление содержит в себе список возможных ошибок


*/
typedef enum {
	ERR_OK = 0,
	ERR_MEMORY,
  ERR_INPUT,
  ERR_USE,
} error_t;

/**
  \defgroup Initialization
  \brief Функции инициализации и удаления полиномов
  
  \{

*/

/*!
  \brief Функция создающая полином степени degree
  Фунция выделяет память под массив coefficients для полинома и инициализирует степень полинома
  \param[out] polynom указатель на структуру в которой выделяется память
  \param[in] degree степень полинома которая используется в выделении необходимого количества памяти для массива coefficients
  \return полином степени degree и коэффициентами 0
*/
poly_t* PolyCreate(poly_t* polynom, int degree);

/*!
  \brief Освобождает память полинома
  \param[in] polynom указатель на структуру в которой освобождается память
  */
void PolyDestroy(poly_t* polynom);

/*!
  \brief Функция с переменным числом аргументов
  Создаёт полином по переменному числу аргументов, где следующий аргумент за N будет являться коэффициентом высшей степени N полинома
  \param[in] N степень полинома и кол-во последующих аргументов
  \return полином степени N и коэффициентами последующих аргументов
*/
poly_t PolyFrom(int N, ...);
/**\}*/

/**
  \defgroup functions Math operations
  \brief Простейшие математические операции с полиномами

  \{

*/
/*!
  \brief Операция сложения двух полиномов
   Функция складывает два полинома: polynom1 + polynom2
  \param[in] polynom1 первый операнд-полином
  \param[in] polynom2 второй операнд-полином
  \return результат сложения двух полиномов
*/
poly_t PolyAdd(poly_t const polynom1, poly_t const polynom2);

/*!
  \brief Операция вычитания двух полиномов
   Функция вычитает два полинома: polynom1 - polynom2
  \param[in] polynom1 первый операнд-полином
  \param[in] polynom2 второй операнд-полином
  \return результат вычитания двух полиномов
*/
poly_t PolySub(poly_t const polynom1, poly_t const polynom2);

/*!
  \brief Операция умножения двух полиномов
   Функция умножает два полинома: polynom1 * polynom2
  \param[in] polynom1 первый операнд-полином
  \param[in] polynom2 второй операнд-полином
  \return результат умножения двух полиномов
*/
poly_t PolyMul(poly_t const polynom1, poly_t const polynom2);

/*!
  \brief Операция умножения полинома на число типа int
   Функция умножает полином на число: polynom1 * number
  \param[in] polynom1 первый операнд-полином
  \param[in] number второй операнд-число
  \return результат умножения полинома на число
*/
poly_t PolyMulInt(poly_t const polynom1, int number);

/*!
  \brief Операция вычисления значения полинома в точке
   Функция вычисляет значение полинома в точке типа int 
   Если полином это f(x), то функция вычисляет f(number)
  \param[in] polynom1 полином в котором вычисляют значение
  \param[in] number точка
  \return результат умножения полинома на число
*/
int Evaluate(poly_t const polynom, int number);
/**\}*/

/**
  \defgroup group Reading-Writing functions
  \brief Функции считывания и записи полинома 

  \{

*/

/*!
  \brief Функция считывания полинома из строки

   Функция считывает полином записанный в текстовом виде в полином

  \param[out] polynom полином в который считывается текст
  \param[in] str строка типа char
  \return считанный из строки, полином
*/
poly_t* PolyParse(poly_t* polynom, char* str, error_t error);

/*!
  \brief Функция записи полинома в строку

   Функция записывает полином сохранённый в типе poly_t в строку str типа char

  \param[in] polynom полином с которого записывается строка
  \param[out] str строка в которую сохраняется полином в текстовом виде
  \return строка в которой записан полином
*/
char* PolyFormat(poly_t* polynom, char* str);
/*!
  \brief Функция считывания полинома из потока
   Функция считывает полином из потока stream
   Полином считывается до перевода строки: '\n'
  \param[in] stream поток с которого считывается полином записанный в текстовом виде
  \param[out] eof переменная хранящая информацию о конце потока. Если конец потока достигнут то в eof запишется 1 и при последующем считывании будет автоматически возвращаться нулевой многочлен
  \return считанный из потока, полином
*/
poly_t PolyRead(FILE* stream, int* eof);

/*!
  \brief Функция записи полинома в поток
   Функция записывает полином в поток stream
   Полином записывается в текстовом формате, и затем в конце строки прописывается перевод строки: '\n'
  \param[out] stream поток в который записывается полином polynom сохранённый в типе poly_t
  \param[in] polynom полином который записывается в поток stream
*/
void PolyWrite(FILE* stream, poly_t polynom);

/*!
  \brief Макрокоманда доступа к элементу полинома
   Функция возвращает коэффициент полинома в определённой степени
  \param[in] polynom полином с которого берётся информация о коэффициенте
  \param[in] degree степень необходимого элемента полинома
  \return коэффициент полинома в элементе степени degree 
*/
int PolyELEMENT(poly_t polynom, int degree);
/**\}*/

/**
  \defgroup Supporting  Supporting functions
  \brief Вспомогательные функции

  \{

*/
/*!
  \brief Функция проверки на цифру
   Функция проверяет символ типа char на то, является ли этот символ цифрой от 0 до 9
  \param[in] symbol проверяемый символ
  \return 1 если является цифрой, иначе 0
*/
int IsNumber(char symbol);

/*!
  \brief Функция вычисления степени полинома
  Функция вычисляет степень полинома, который записан в строке в текстовом формате
  \param[in] str полином записанный в строке
  \return степень полинома
*/
int GetDegreeOfStringPolynom(char* str);

/*!
  \brief Функция максимального числа
  Функция возвращает максимальное из 2 чисел поданных типа int
  \param[in] degree1 первое число
  \param[in] degree2 второе число
  \return максимальное из двух чисел
*/
int Max(int degree1, int degree2);

/*!
  \brief Функция минимального числа
  Функция возвращает минимальное из 2 чисел поданных типа int
  \param[in] degree1 первое число
  \param[in] degree2 второе число
  \return минимальное из двух чисел
*/
int Min(int degree1, int degree2);

/*!
  \brief Функция длины числа
  Функция возвращает длину числа или число позиции в числе типа int
  \param[in] number число у которого нужно вычислить длину
  \return длину числа
*/
int GetLengthOfNumber(int number);

/*!
  \brief Функция вычисления числа в строке
  Функция возвращает число из строки в типе int
  Число начинается в позиции position строки str
  \param[in] str строка из которой берётся число
  \param[in] position позиция в строке str где начинается число
  \param[in] turn в каком направлении берётся число (если направо то right = 1) (если налево то left = -1)
  \param[out] lengthOfRightNumber записывается длина числа, если направление взято направо
  \return число типа int из строки
*/
int GetNumberFromString(char* str, int position, int turn, int* lengthOfRightNumber);

/*!
  \brief Функция расширения строки
  Функция расширяет или сжимает массив типа char до размера size
  Число начинается в позиции position строки str
  \param[out] str указатель на начало массива
  \param[in] size размер обновлённого массива
  \return указатель на массив типа char
*/
char* ReallocString(char* str, int size);

/*!
  \brief Функция проверки высшей степени
  После математической операции возможно, что в коэффициент высшей степени полинома 
  равен нулю. В этом случае нет необходимости хранить память для коэффициента для высшей степени полинома.
  Функция проверяет полином на этот случай и перераспределяет память если используется ненужная ячейка памяти
  \param[out] polynom проверяемый полином
  \return полином с перераспределённой памятью
*/
poly_t* AnalyseHighestDegree(poly_t* polynom);
/**\}*/
#endif
