#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
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

        void perform_allocation();
        void save_allocation(const std::string& allocation_file);
    private:
        int calculate_score() const;

        std::unordered_map<std::string, Staff>staff_dict_;
        std::unordered_map<std::string, Project>project_dict_;
        std::unordered_map<std::string, Student>student_dict_;

        // Sorted by student_id for easy output
        std::map<std::string, Allocation>allocations;
};

#endif //ALLOCATOR_H