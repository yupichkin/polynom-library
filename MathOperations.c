#include "Poly.h"

poly_t PolyAdd(poly_t const polynom1, poly_t const polynom2) {
  int i;
  int minDegree = Min(polynom1.degree, polynom2.degree);
  int maxDegree = Max(polynom1.degree, polynom2.degree);
  int k = 0;
  poly_t* sparePolynom = NULL; //если в высшей степени сложившегося полинома получили 0 то перепаспределяем полином через запасной
  poly_t* addedPolynom = NULL;
  addedPolynom = PolyCreate(addedPolynom, maxDegree);

  for (i = 0; i <= minDegree; i++) {
    addedPolynom->coefficients[i] = polynom1.coefficients[i] + polynom2.coefficients[i];
  }
  if (maxDegree == polynom1.degree && maxDegree != polynom2.degree) {
    for (i = minDegree + 1; i <= maxDegree; i++) {
      addedPolynom->coefficients[i] = polynom1.coefficients[i];
    }
  }
  if (maxDegree == polynom2.degree && maxDegree != polynom1.degree) {
    for (i = minDegree + 1; i <= maxDegree; i++) {
      addedPolynom->coefficients[i] = polynom2.coefficients[i];
    }
  }
  addedPolynom = AnalyseHighestDegree(addedPolynom);
  return *addedPolynom;
}

poly_t PolySub(poly_t const polynom1, poly_t const polynom2) {
  int i;
  poly_t subbedPolynom;
  poly_t* stockPolynom = NULL;
  stockPolynom = PolyCreate(stockPolynom, polynom2.degree);
  for (i = 0; i <= polynom2.degree; i++)
    stockPolynom->coefficients[i] = -polynom2.coefficients[i];
  subbedPolynom = PolyAdd(polynom1, *stockPolynom);
  return subbedPolynom;
}

poly_t PolyMul(poly_t const polynom1, poly_t const polynom2) {
  int i;
  int j;
  int k = 0;
  poly_t* mulledPolynom = NULL;
  mulledPolynom = PolyCreate(mulledPolynom, polynom1.degree + polynom2.degree);
  for (i = 0; i <= polynom1.degree; i++)
    for (j = 0; j <= polynom2.degree; j++)
      mulledPolynom->coefficients[i + j] += polynom1.coefficients[i] * polynom2.coefficients[j];
  return *mulledPolynom;
}

poly_t PolyMulInt(poly_t const polynom1, int number) {
  int i;
  int k = 0;
  poly_t* mulledPolynom = NULL;
  mulledPolynom = PolyCreate(mulledPolynom, polynom1.degree);
  for (i = 0; i <= polynom1.degree; i++)
    mulledPolynom->coefficients[i] = number * polynom1.coefficients[i];
  return *mulledPolynom;
}

int Evaluate(poly_t const polynom, int number) {
  int result = 0;
  int i = polynom.degree;
  while (i > -1) {
    result += polynom.coefficients[i] * (int)pow(number, i);
    i--;
  }
  return result;
}
