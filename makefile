CXX		= g++

# -Wall and -Wextra enable most compiler warnings! 
# -g enables debugging information with GDB (which I bring up a lot).
CXXFLAGS	= -Wall -Wextra -std=c++17 -O0 -g

SRC = main.cpp Staff.cpp Project.cpp Student.cpp Allocator.cpp
OBJ = $(SRC:.cpp=.o) # Turn all src files into object files 


# Compile with everything we set above.
GenAlloc: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o GenAlloc

# This is new to me! It's a generic rule to make any .o from a .cpp which I usally do manually (SLOW)!
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Remove build objects so we can rebuild clean.
clean:
	rm -f *.o GenAlloc *~  
