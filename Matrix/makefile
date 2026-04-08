CC = g++
CFLAGS = -Wall -std=c++17 -IInclude
PICFLAGS = -fPIC

DEPS = Include/matrix.hpp \
       Include/LinearSystem.hpp \
       Include/gaussian.hpp \
       Include/lu.hpp \
       Include/crouts.hpp \
       Include/dolittle.hpp \
       Include/cholsky.hpp \
       Include/gauss_jacobi.hpp \
       Include/gauss_seidle.hpp \
       Include/iterative_method.hpp \
       Include/Eigenvalue.hpp \
       Include/gerschgorin.hpp \
       Include/interpolation.hpp \
       Include/lagrange.hpp
SRC = src/matrix.cpp \
      src/Linear_system.cpp \
      src/gaussian.cpp \
      src/lu.cpp \
      src/crouts.cpp \
      src/cholsky.cpp \
      src/dolittle.cpp \
      src/gauss_jacobi.cpp \
      src/gauss_seidle.cpp \
      src/iterative_method.cpp \
      src/Eigenvalue.cpp \
      src/gerschgorin.cpp \
      src/interpolation.cpp \
      src/lagrange.cpp

OBJ    = $(SRC:.cpp=.o)
PICOBJ = $(SRC:.cpp=.pic.o)
LIB_STATIC = libmat.a
LIB_SHARED = libmat.so
TARGET = matrix_solver

%.o: %.cpp $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

%.pic.o: %.cpp $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS) $(PICFLAGS)

static: $(OBJ)
	ar rcs $(LIB_STATIC) $(OBJ)
	$(CC) MatrixMain.cpp -L. -lmat -IInclude -std=c++17 -o $(TARGET)

shared: $(PICOBJ)
	$(CC) -shared -o $(LIB_SHARED) $(PICOBJ)
	$(CC) MatrixMain.cpp -L. -lmat -IInclude -std=c++17 -o $(TARGET)

run_static: static
	./$(TARGET)

run_shared: shared
	LD_LIBRARY_PATH=. ./$(TARGET)

clean:
	rm -f src/*.o src/*.pic.o $(LIB_STATIC) $(LIB_SHARED) $(TARGET)