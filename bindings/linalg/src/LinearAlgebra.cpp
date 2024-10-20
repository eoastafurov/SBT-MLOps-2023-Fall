#include "LinearAlgebra.h"
#include <cblas.h>
#include <iostream>
#include <vector>

double LinearAlgebra::dotPure(const std::vector<double> &a,
                              const std::vector<double> &b) {
  if (a.size() != b.size()) {
    throw std::runtime_error("Vectors must be of the same size");
  }

  double result = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    result += a[i] * b[i];
  }
  return result;
}

double LinearAlgebra::dotBlas(const std::vector<double> &a,
                              const std::vector<double> &b) {
  if (a.size() != b.size()) {
    throw std::runtime_error("Vectors must be of the same size");
  }
  return cblas_ddot(a.size(), &a[0], 1, &b[0], 1);
}

std::vector<std::vector<double>>
LinearAlgebra::matmulPure(const std::vector<std::vector<double>> &a,
                          const std::vector<std::vector<double>> &b) {
  size_t aRows = a.size();
  size_t aCols = a[0].size();
  size_t bRows = b.size();
  size_t bCols = b[0].size();

  if (aCols != bRows) {
    throw std::runtime_error("The number of columns of the 1st matrix must "
                             "equal the number of rows of the 2nd matrix");
  }

  std::vector<std::vector<double>> result(aRows, std::vector<double>(bCols, 0));

  for (size_t i = 0; i < aRows; ++i) {
    for (size_t j = 0; j < bCols; ++j) {
      for (size_t k = 0; k < aCols; ++k) {
        result[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return result;
}

std::vector<std::vector<double>>
LinearAlgebra::matmulBlas(const std::vector<std::vector<double>> &a,
                          const std::vector<std::vector<double>> &b) {
  size_t aRows = a.size();
  size_t aCols = a[0].size();
  size_t bRows = b.size();
  size_t bCols = b[0].size();

  if (aCols != bRows) {
    throw std::runtime_error("The number of columns of the 1st matrix must "
                             "equal the number of rows of the 2nd matrix");
  }

  // Convert 2D vectors to 1D vector for BLAS compatibility
  std::vector<double> a_flat(aRows * aCols);
  std::vector<double> b_flat(bRows * bCols);
  std::vector<double> result_flat(aRows * bCols);

  for (size_t i = 0; i < aRows; i++)
    for (size_t j = 0; j < aCols; j++)
      a_flat[i * aCols + j] = a[i][j];

  for (size_t i = 0; i < bRows; i++)
    for (size_t j = 0; j < bCols; j++)
      b_flat[i * bCols + j] = b[i][j];

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, aRows, bCols, aCols,
              1.0, &a_flat[0], aCols, &b_flat[0], bCols, 0.0, &result_flat[0],
              bCols);

  // Convert the result back to a 2D vector
  std::vector<std::vector<double>> result(aRows, std::vector<double>(bCols));
  for (size_t i = 0; i < aRows; i++)
    for (size_t j = 0; j < bCols; j++)
      result[i][j] = result_flat[i * bCols + j];

  return result;
}
