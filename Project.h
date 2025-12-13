#ifndef PROJECT_H
#define PROJECT_H

#include <string>

class Project{
    public:
        // Constructors.
        Project(const std::string& id, const std::string &proposer, int capacity, const std::string &area, const std::string& project_title);
        // Attributes.
        std::string project_id;
        std::string proposer_id;
        int assignment_capacity; // Multiplixity.
        std::string subject_area;
        std::string title;
        int current_allocation;
        // Methods.
        bool is_available() const;
};


#endif // PROJECT_H