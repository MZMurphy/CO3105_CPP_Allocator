#include "Staff.h"

Staff::Staff(const std::string& id, int max_workload, const std::vector<std::string>& areas) : 
staff_id(id), max_supervision_workload(max_workload), subject_areas(areas), current_workload(0) {}

// Returns true if there's space for more students
bool Staff::able_to_supervise() const{
    return current_workload < max_supervision_workload; 
}