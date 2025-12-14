#include <iostream>
#include <string>

// Our imports
#include "Staff.h"
#include "Student.h"
#include "Project.h"
#include "Allocator.h"


// Reads arguments and acts as the entry point for the program.

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <staff_file> <project_file> <student_file> <output_file>\n";
        return 1; // Failure.
    }
    std::string staffFile = argv[1];
    std::string projectFile = argv[2];
    std::string studentFile = argv[3];
    std::string outputFile = argv[4];
    

    // From here we plug in our logic from other sources/headers.
    // ANd write to an output file

    // Allocator logic! 
    // This is just a placeholder for the real deal.

    // We'd create the object, pass data/other objects, run it, then either handle the output here or within it.
    // We choose.

    Allocator allocator;
    allocator.load_staff("./Test/staffExample.txt"); //hardcoded for now.
    allocator.load_students("./Test/studentExample.txt");

    return 0; // Success.
}