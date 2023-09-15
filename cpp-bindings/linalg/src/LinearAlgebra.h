#pragma once

#include <vector>

class LinearAlgebra {
public:
  static double dotPure(const std::vector<double> &a,
                        const std::vector<double> &b);
  static double dotBlas(const std::vector<double> &a,
                        const std::vector<double> &b);
  static std::vector<std::vector<double>>
  matmulPure(const std::vector<std::vector<double>> &a,
             const std::vector<std::vector<double>> &b);
  static std::vector<std::vector<double>>
  matmulBlas(const std::vector<std::vector<double>> &a,
             const std::vector<std::vector<double>> &b);
};
