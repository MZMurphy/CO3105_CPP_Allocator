CXX		= g++


# -g enables debugging information with GDB (which I bring up a lot).
CXXFLAGS	= -Wall -Wextra -std=c++17 -O0 -g

SRC = main.cpp Staff.cpp Project.cpp Student.cpp Allocator.cpp
OBJ = $(SRC:.cpp=.o)



GenAlloc: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o GenAlloc

# generic rule for  compiling .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Remove build objects so we can rebuild clean.
clean:
	rm -f *.o GenAlloc *~  
