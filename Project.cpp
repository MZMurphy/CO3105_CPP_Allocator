#include "Project.h"

Project::Project(const std::string& id, const std::string &proposer, int capacity, const std::string &area, const std::string& project_title) :
project_id(id), proposer_id(proposer), assignment_capacity(capacity), subject_area(area), title(project_title), current_allocation(0) {}


// returns true if projec is available.
bool Project::is_available() const{
    return current_allocation < assignment_capacity; 
}