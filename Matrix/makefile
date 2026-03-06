CC = g++
CFLAGS = -Wall -std=c++17 -IInclude

# Header dependencies
DEPS = Include/matrix.hpp \
       Include/LinearSystem.hpp \
       Include/gaussian.hpp \
       Include/lu.hpp \
	   Include/crouts.hpp \
       Include/dolittle.hpp \
       Include/cholsky.hpp

# Object files
OBJ = MatrixMain.o \
      src/matrix.o \
      src/Linear_system.o \
      src/gaussian.o \
      src/lu.o \
	  src/crouts.o \
	  src/dolittle.o \
      src/cholsky.o

TARGET = matrix_solver

# Rule to compile any .cpp into .o
%.o: %.cpp $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

# Link all object files
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)