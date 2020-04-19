#include "Poly.h"

poly_t* PolyCreate(poly_t* polynom, int degree) {
  int i;
  polynom = malloc(sizeof(poly_t));
  polynom->degree = degree;
  polynom->coefficients = (int*)malloc((degree + 1) * sizeof(int));
  if (polynom->coefficients == 0)
    printf("ERR_MEMORY");
  for (i = 0; i <= degree; i++) //"<=" потому что ещё память под нулевую степень
    polynom->coefficients[i] = 0;
  return polynom;
}

void PolyDestroy(poly_t* polynom) {
  free(polynom->coefficients);
  free(polynom);
}

int PolyELEMENT(poly_t polynom, int degree) {
  if (degree > polynom.degree)
    return 0;
  return polynom.coefficients[degree];
}

poly_t PolyFrom(int N, ...) {
  int i;
  int* ptr = &N;
  poly_t* polynom = NULL;
  polynom = PolyCreate(polynom, N - 1);

  for (i = N; i > 0; i--) {
    polynom->coefficients[i - 1] = *(++ptr);
  }
  return *polynom;
}

void Realloc(poly_t* polynom) {
  int* polynom_coefficients = NULL;
  polynom_coefficients = realloc(polynom, polynom->degree * sizeof(int));
  if (polynom_coefficients == NULL)
    printf("ERR_MEMORY");
  polynom->coefficients = polynom_coefficients;
}

int Min(int degree1, int degree2) {
  if (degree1 < degree2)
    return degree1;
  return degree2;
}

int Max(int degree1, int degree2) {
  if (degree1 > degree2)
    return degree1;
  return degree2;
}
poly_t* AnalyseHighestDegree(poly_t* polynom) {
  int i;
  int k;
  poly_t* resevePolynom = NULL;
  if (polynom->coefficients[polynom->degree] == 0) {
    k = polynom->degree;
    while (polynom->coefficients[k] == 0 && k > 0)
      k--;
    resevePolynom = PolyCreate(resevePolynom, k);
    for (i = 0; i <= k; i++)
      resevePolynom->coefficients[i] = polynom->coefficients[i];
    return resevePolynom;
  }
  else
    return polynom;
}

int IsNumber(char symbol) {
  if (symbol >= '0' && symbol <= '9')
    return 1;
  return 0;
}

int GetNumberFromString(char* str, int position, int turn, int* lengthOfRightNumber) {
  int number = 0;
  int k = 0;
  int j = 0;
  if ((position < 0) || isspace(str[position] || str[position] == '+' || str[position] == '-')) { //если берём справа, то сюда никак не залезет т.к '^'
    return 1;
  }
  if (turn == left) {
    while (IsNumber(str[position + j])) {
      number = number + (str[position + j] -'0')* (int)(pow(10, k));
      k++;
      j += turn;
    }
  }
  while (IsNumber(str[position + j])) {
    number = number * 10 + str[position + j] - '0';
    k++;
    j += turn;
  }
  if (turn == right)
    *lengthOfRightNumber = j;
  return number;
}

int GetDegreeOfStringPolynom(char* str) {
  int i = 0;
  int length;
  int degree = 0;
  while (str[i] != '\0') {
    if (str[i] == 'x') {
      if (str[i + 1] == '^') {
        if (degree < GetNumberFromString(str, i + 2, right, &length))
          degree = GetNumberFromString(str, i + 2, right, &length);
      }
      else {
        if (degree < 1)
          degree = 1;
      }

    }
    i++;
  }
  return degree;
}

char* ReallocString(char* str, int size) {
  char* strRealloc = NULL;
  strRealloc = (char*)realloc(str, size);
  if (strRealloc == NULL)
    printf("Error: memory");
  str = strRealloc;
  return str;
}

int GetLengthOfNumber(int number) {
  int i = 0;
  while (number > 0) {
    number = number / 10;
    i++;
  }
  return i;
}

void PrintError(error_t error) {
  switch (error) {
  case ERROR_OK:
    break;
  case ERROR_USER_WRITING: 
    printf("ERROR: illegal polynom");
    break;
  case ERROR_MEMORY:
    printf("ERROR: memory");
    break;
  case ERROR_UNKNOWN:
    printf("ERROR: unknown");
    break;
  }
