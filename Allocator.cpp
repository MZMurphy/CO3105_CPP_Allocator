#include "Allocator.h"
// See stream slides
#include <fstream>
#include <sstream>

Allocator::Allocator() {};

// Example staff files look like:
// staff_Id, workload, subject area, more subject arreas...

// Open stafffile, read line by line. 
void Allocator::load_staff(const std::string& filename)
{
    std::ifstream file(filename); // open file.
    std::string file_line; // holds each line

    DEBUG_PRINT("Loading stafffile: " <<filename <<"\n\n");

    while(std::getline(file, file_line)) // read line by line
    {
        std::istringstream iss(file_line);
        std::string id;
        int load;
        iss >> id >> load; // get staffid and workload from line

        std::vector<std::string> subject_areas; // dynamic array of strings
        std::string subject_area;
        while(iss >> subject_area)
        {
            subject_areas.push_back(subject_area);
        }
        DEBUG_PRINT("Staff ID: " << id << "\n");
        DEBUG_PRINT("Workload: " << load << "\n");

        DEBUG_PRINT("Subject Areas: ");
        for(std::string subject : subject_areas)
        {
            DEBUG_PRINT(subject << " ");
        }
        DEBUG_PRINT("\n");

        // probably need to add dictionaries
    }
    file.close();
}