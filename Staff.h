#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <vector>
#include <algorithm>

class Staff{
    public:
        // Constructors.
        Staff(const std::string& id, int max_workload, const std::vector<std::string>& areas);
        // Attributes.
        std::string staff_id;
        int max_supervision_workload; 
        std::vector<std::string> subject_areas; 
        int current_workload;

        // Methods.
        bool able_to_supervise() const; // Tells us if supervisor has room to take more studnets.
};

#endif //STAFF_H