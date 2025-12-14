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
        std::string staff_id;
        int load;
        iss >> staff_id >> load; // get staffid and workload from line

        std::vector<std::string> subject_areas; // dynamic array of strings
        std::string subject_area;
        while(iss >> subject_area)
        {
            subject_areas.push_back(subject_area);
        }
        DEBUG_PRINT("Staff ID: " << staff_id << ", ");
        DEBUG_PRINT("Workload: " << load << ", ");

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

// Example student file looks like
// student_id, project_id, 0-4 project ids...
// Open 
void Allocator::load_students(const std::string& filename)
{
    std::ifstream file(filename); // open file.
    std::string file_line; // holds each line

    DEBUG_PRINT("\nLoading studentfile: " <<filename <<"\n\n");

    while(std::getline(file, file_line))
    {
        std::istringstream iss(file_line);
        std::string student_id;
        iss >> student_id; // get student id

        // Non-fixed attributes.
        std::vector<std::string> project_preferences;
        std::string project_id;
        while(iss >> project_id)
        {
            project_preferences.push_back(project_id);
        }
        DEBUG_PRINT("Student ID: " << student_id << "\n");
        DEBUG_PRINT("Project Preferences: ");
        for(std::string project: project_preferences)
        {
            DEBUG_PRINT(project << " ");
        }
        DEBUG_PRINT("\n\n");
    }
    file.close();

}

// Example project file looks like:
// project_id, proposer/staff_id, max_students/multpliciyt, subject aras, and titles WITH spaces.

void Allocator::load_projects(const std::string& filename)
{
    std::ifstream file(filename); // open file.
    std::string file_line; // holds each line
    DEBUG_PRINT("Loading projectfile: " << filename << "\n\n");

    while(std::getline(file, file_line))
    {
        std::istringstream iss(file_line);
        std::string project_id, staff_owner_id, subject_area;
        int assignment_capacity;
        iss >> project_id >> staff_owner_id >> assignment_capacity >> subject_area; 

        // Get non-fixed Title with spaces.
        std::string title;
        std::getline(iss, title);
        if (!title.empty() && title[0] == ' ') {
            title = title.substr(1); // this removes leading space
          }

        DEBUG_PRINT("Project ID: "<< project_id << ", ");
        DEBUG_PRINT("Supervisor: " << staff_owner_id << ", "); // staff owner. 
        DEBUG_PRINT("Capacity: " << assignment_capacity << ", ");
        DEBUG_PRINT("Subject Area: " << subject_area << ", ");
        DEBUG_PRINT("Title: " << title << "\n");
    }
    file.close();
}
