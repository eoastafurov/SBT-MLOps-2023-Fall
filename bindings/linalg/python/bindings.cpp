#include "LinearAlgebra.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(linalg_core, m) {
  m.doc() = R"doc(
    Python bindings for LinearAlgebra library
  )doc";

  py::class_<LinearAlgebra>(m, "LinearAlgebra")
      .def_static("dotPure", &LinearAlgebra::dotPure, R"doc(
          Compute dot product using pure C++.

          Parameters:
            a : list of float
                The first vector.
            b : list of float
                The second vector.

          Returns:
            float
                The dot product of the two vectors.
      )doc")
      .def_static("dotBlas", &LinearAlgebra::dotBlas, R"doc(
          Compute dot product using BLAS.

          Parameters:
            a : list of float
                The first vector.
            b : list of float
                The second vector.

          Returns:
            float
                The dot product of the two vectors.
      )doc")
      .def_static("matmulPure", &LinearAlgebra::matmulPure, R"doc(
          Matrix multiplication using pure C++.

          Parameters:
            a : list of list of float
                The first matrix.
            b : list of list of float
                The second matrix.

          Returns:
            list of list of float
                The result of matrix multiplication.
      )doc")
      .def_static("matmulBlas", &LinearAlgebra::matmulBlas, R"doc(
          Matrix multiplication using BLAS.

          Parameters:
            a : list of list of float
                The first matrix.
            b : list of list of float
                The second matrix.

          Returns:
            list of list of float
                The result of matrix multiplication.
      )doc");
}
