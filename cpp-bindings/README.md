# Linear Algebra with Python Bindings

This project provides linear algebra utilities implemented in C++ and exposes them to Python using pybind11 bindings. It offers both pure C++ implementations and ones that utilize BLAS.

## Dependencies

### Core Dependencies:

- **C++ Compiler**: g++ is used
- **Python 3**: It is required for the bindings and the build process.
- **pybind11**: Lib used to create the Python bindings.
- **OpenBLAS**: The project uses the OpenBLAS library for optimized linear algebra operations.


### Optional Dependencies:

- **Google Test**: Used for running the C++ tests.


### Installing Dependencies

On a Debian-based system, you can install most of these dependencies using:

```bash
sudo bash setup.sh
```


## Building the Project
To build both the Python bindings and the C++ tests:

```bash
make all
```

To build only the Python bindings:

```bash
make linalg
```

To build the tests:

```bash
make test
```

To clean the build artifacts:

```bash
make clean
```


## Running Tests
Once built, you can run the C++ tests using:

```bash
make run_tests
```


## Python installation

```bash
# Necessary deps
pip install pybind11

# Compile project
make linalg

# Build whl and pack
python -m build

# Install package in current environment
pip install dist/*.whl
```



## Python usage
After installation, you can use the linear algebra utilities in Python as:

```python
import linalg

matrix_a = np.random.rand(K, K).tolist()
matrix_b = np.random.rand(K, K).tolist()

linalg.LinearAlgebra.matmulBlas(matrix_a, matrix_b)
```


## Cleanup build files

```bash
python setup.py clean
make clean
rm -rf build/ dist/ linalg.egg-info/
```


## Uninstall package

```bash
pip uninstall linalg
```


## Performance
Compare performance between pure python, pure c++, c++ blas and numpy implementations:

```bash
python srcipts/perf.py
```
