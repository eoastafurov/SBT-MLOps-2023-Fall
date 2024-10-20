CXX=g++
CXXFLAGS=-std=c++11 -O3 -march=native -Wall -I$(SRC_DIR) $(shell python3 -m pybind11 --includes)
PY_LDFLAGS=$(shell python3-config --ldflags) -lopenblas -shared -fPIC
GTEST_FLAGS=-lgtest -lgtest_main -pthread
LDFLAGS=-lopenblas
SRC_DIR=linalg/src
TESTS_DIR=linalg/tests
PYTHON_DIR=linalg/python

all: linalg test

linalg: $(PYTHON_DIR)/bindings.o $(SRC_DIR)/LinearAlgebra.o
	$(CXX) $^ -o $(PYTHON_DIR)/linalg_core`python3-config --extension-suffix` $(PY_LDFLAGS) $(CXXFLAGS)

$(PYTHON_DIR)/bindings.o: $(PYTHON_DIR)/bindings.cpp $(SRC_DIR)/LinearAlgebra.h
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(SRC_DIR)/LinearAlgebra.o: $(SRC_DIR)/LinearAlgebra.cpp $(SRC_DIR)/LinearAlgebra.h
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

test: $(TESTS_DIR)/test_linalg.o $(SRC_DIR)/LinearAlgebra.o
	$(CXX) $^ -o $(TESTS_DIR)/test_linalg $(GTEST_FLAGS) $(LDFLAGS)

$(TESTS_DIR)/test_linalg.o: $(TESTS_DIR)/test_linalg.cpp $(SRC_DIR)/LinearAlgebra.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_tests: test
	./$(TESTS_DIR)/test_linalg

clean:
	rm -f $(PYTHON_DIR)/*.o $(SRC_DIR)/*.o $(TESTS_DIR)/*.o $(PYTHON_DIR)/linalg_core`python3-config --extension-suffix` $(TESTS_DIR)/test_linalg
