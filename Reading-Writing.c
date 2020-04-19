#include "Poly.h"

poly_t* PolyParse(poly_t* polynom, char* str, error_t* error) {
  int i = 0;
  int length;
  int degree;
  int signOfNumber = 1;
  int* reallocCoeficients = NULL;
  degree = GetDegreeOfStringPolynom(str);
  polynom = PolyCreate(polynom, degree);

  while (str[i] != '\0') {
    if (str[i] == '+')
      signOfNumber = 1;
    if (str[i] == '-')
      signOfNumber = -1;
    if (IsNumber(str[i])) {
      while (IsNumber(str[i])) {
        i++;
      }
      if (str[i] != 'x')
        polynom->coefficients[0] += signOfNumber * GetNumberFromString(str, i - 1, left, &length);
      i--;
    }
    if (str[i] == 'x') {
      if (str[i + 1] == '^') {
        if (!IsNumber(str[i + 2])) {
          *error = ERROR_USER_WRITING;
          return polynom;
        }
        if (IsNumber(str[i - 1]))
          polynom->coefficients[GetNumberFromString(str, i + 2, right, &length)] += signOfNumber * GetNumberFromString(str, i - 1, left, &length);
        else 
          polynom->coefficients[GetNumberFromString(str, i + 2, right, &length)] += signOfNumber;
        i += length + 1;
      }
      else if (IsNumber(str[i - 1]))
        polynom->coefficients[1] += signOfNumber * GetNumberFromString(str, i - 1, left, &length);
      else
        polynom->coefficients[1] += signOfNumber;
    }
    i++;
  }
  return polynom;
}


char* PolyFormat(poly_t* polynom, char* str) {
  int i = polynom->degree; //счётчик полинома
  int k = 0; //счётчик строки
  int coefficient;
  int lengthOfCoefficient; // длина числа элемента полинома
  int lengthOfDegree; //длина степени элемента полинома
  int degree; //степень элемента полинома
  char* strRealloc = NULL;
  while (i >= 0) {
    lengthOfCoefficient = GetLengthOfNumber(abs(polynom->coefficients[i]));
    lengthOfDegree = GetLengthOfNumber(abs(i));
    degree = i;
    coefficient = polynom->coefficients[i];
    if (coefficient == 0) {
      i--;
      continue;
    }
    if (coefficient > 0) {
      if (k != 0) { //если не первый положительный коэффициент 
        str = ReallocString(str, k + 1);
        str[k] = '+';
        k++;
      }
    }
    if (coefficient < 0) {
      str = ReallocString(str, k + 1);
      str[k] = '-';
      k++;
      coefficient = -coefficient;
    }
    str = ReallocString(str, k + lengthOfCoefficient);
    if (coefficient != 1 || i == 0) { //чтобы написать 2x^2 + (1)
      while (lengthOfCoefficient) {
        str[k] = (coefficient / (int)pow(10, lengthOfCoefficient - 1)) + '0';
        k++;
        coefficient = coefficient % (int)pow(10, lengthOfCoefficient - 1);
        lengthOfCoefficient--;
      }
    }
    if (i >= 1) {
      str = ReallocString(str, k + lengthOfCoefficient + 2 + lengthOfDegree); //выделяю не столько сколько нужно, ну и ПОФИК!!!
      str[k] = 'x';
      k++;
      if (i > 1) {
        str[k] = '^';
        k++;
        while (lengthOfDegree) {

          str[k] = degree / (int)(pow(10, lengthOfDegree - 1)) + '0';
          k++;
          degree = degree % (int)pow(10, lengthOfDegree - 1);
          lengthOfDegree--;
        }
      }
    }
    i--;
  }
  str[k] = '\0';
  return str;
}
void PolyWrite(FILE* stream, poly_t polynom) {
  int i = 0;
  char* str = NULL;
  char linebreak = '\n';
  str = PolyFormat(&polynom, str);
  fprintf(stream, str);
  fprintf(stream, "%c", linebreak);
}

poly_t PolyRead(FILE* stream, int* eof) {
  int i = 0;
  int degree;
  char add_char = (char)fgetc(stream);
  char* str = NULL;
  char* str_realloc = NULL;
  error_t error = ERROR_OK;
  poly_t* polynom = NULL;
  if (*eof) {
    polynom = PolyCreate(polynom, 0);
    return *polynom;
  }
  while (add_char != '\n') {
    if ((add_char == EOF) || (ferror(stream) != 0) || (add_char == 26)) {
      *eof = 1;
      break;
    }
    str_realloc = (char*)realloc(str, (i + 1) * sizeof(char));
    if (str_realloc == NULL) {
      printf("ERROR: memory");
      exit(1);
    }
    str = str_realloc;
    str[i] = add_char;
    i++;
    add_char = (char)fgetc(stream);
  }
  str_realloc = (char*)realloc(str, (i + 1) * sizeof(char));
  if (str_realloc == NULL) {
    printf("ERROR: memory");
    exit(1);
  }
  str = str_realloc;
  str[i] = '\0';
  degree = GetDegreeOfStringPolynom(str);
  polynom = PolyCreate(polynom, degree);
  polynom = PolyParse(polynom, str, &error);
  if (error != ERROR_OK)
    PrintError(error);
  return *polynom;
}
