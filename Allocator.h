#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <string>
#include <vector>
#include "Staff.h"
#include "Project.h"
#include "Student.h"
#include "DEBUG.h"  


// Our output should be an array of 'allocations'.
// As in brief: stu001 proj42 staff123
//              stu002 proj15 staff456
struct Allocation{
    std::string student_id;
    std::string project_id;
    std::string staff_id;
};


// class Allocator {} should be where our BIG functions go e.g. assignment algo.

class Allocator{
    public:
        // Constructors
        Allocator();

        // Parse files
        void load_staff(const std::string& staff_file);
        void load_projects(const std::string& project_file);
        void load_students(const std::string& student_file);
};

#endif //ALLOCATOR_H