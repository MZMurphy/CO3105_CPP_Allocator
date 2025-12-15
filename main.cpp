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
    
    // Flow is that main never never directly accesses our Staff, Student, Project
    // Data strcutures. Allocator is our inbetween of main and the data. 

    Allocator allocator;
    allocator.load_staff(staffFile);
    allocator.load_projects(projectFile);
    allocator.load_students(studentFile);

    allocater.perform_allocation();
    allocator.save_allocation(outputFile);

    return 0; // Success.
}