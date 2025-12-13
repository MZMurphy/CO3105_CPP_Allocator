#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <string>
#include <vector>
#include "Staff.h"
#include "Project.h"
#include "Student.h"


// Our output should be an array of 'allocations'.
// As in brief: stu001 proj42 staff123
//              stu002 proj15 staff456
struct Allocation{
    std::string student_id;
    std::string project_id;
    std::string staff_id;
};


// class Allocator {} should be where our BIG functions go e.g. assignment algo.

#endif //ALLOCATOR_H