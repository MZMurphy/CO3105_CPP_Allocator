#include "Allocator.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
const int NUM_ITERATIONS = 1000;                                                                                             

Allocator::Allocator() {};

// Parses staff file.
void Allocator::load_staff(const std::string& staff_file)
{
    std::ifstream file(staff_file);
    if (!file.is_open()) {
        std::cerr << staff_file << " not found.\n";
        exit(1);
    }
    std::string file_line;

    DEBUG_PRINT("staffile: " <<staff_file <<"\n\n");

    while(std::getline(file, file_line))
    {
        if (file_line.empty()) continue;
        std::istringstream iss(file_line);
        std::string staff_id;

        iss >> staff_id;
        // comments were getting interpreted as student id
        if (staff_id.empty() || staff_id[0] == '#') continue;

        int workload;
        iss >> workload;

        std::vector<std::string> subject_areas;
        std::string subject_area;
        while(iss >> subject_area)
        {
            subject_areas.push_back(subject_area);
        }
        DEBUG_PRINT("Staff ID: " << staff_id << ", ");
        DEBUG_PRINT("Workload: " << workload << ", ");

        DEBUG_PRINT("Subject Areas: ");
        for(std::string subject : subject_areas)
        {
            DEBUG_PRINT(subject << " ");
        }
        DEBUG_PRINT("\n");


        Staff staff(staff_id, workload, subject_areas);
        staff_dict_.insert({staff_id, staff});
    }
        
    DEBUG_PRINT("Staff dict data: " << staff_dict_.size() << " in staff dict.\n\n");
    file.close();
}

// Parses student file.
void Allocator::load_students(const std::string& student_file)
{
    std::ifstream file(student_file);
    if(!file.is_open()) {
        std::cerr << student_file << " not found.\n";
        exit(1);
    }
    std::string file_line;

    DEBUG_PRINT("\nstudentfile: " <<student_file <<"\n\n");

    while(std::getline(file, file_line))
    {
        if (file_line.empty()) continue;
        std::istringstream iss(file_line);
        std::string student_id;
        iss >> student_id;

        // checks for comments as those were confused with ids
        if (student_id.empty() || student_id[0] == '#') continue;
        // Non-fixed attributes.
        std::vector<std::string> project_preferences;
        std::string project_id;
        while(iss >> project_id)
        {
            project_preferences.push_back(project_id);
        }

        Student student(student_id, project_preferences);
        student_dict_.insert({student_id, student});


        DEBUG_PRINT("Student ID: " << student_id << "\n");
        DEBUG_PRINT("Project Preferences: ");
        for(std::string project: project_preferences)
        {
            DEBUG_PRINT(project << " ");
        }
        DEBUG_PRINT("\n\n");
    }
    DEBUG_PRINT("Student dict data: " << student_dict_.size() << " in student dict.\n\n");
    file.close();

}

// Parses project file.
void Allocator::load_projects(const std::string& project_file)
{
    std::ifstream file(project_file);
    if(!file.is_open()) {
        std::cerr << project_file << " not found.\n";
        exit(1);
    }
    std::string file_line;
    DEBUG_PRINT("projectfile: " << project_file << "\n\n");

    while(std::getline(file, file_line))
    {
        if (file_line.empty()) continue;
        std::istringstream iss(file_line);
        std::string project_id;

        iss >> project_id;
        // checks for comments as those were confused with ids
        if (project_id.empty() || project_id[0] == '#') continue;

        std::string staff_owner_id, subject_area;
        int assignment_capacity;
        iss >> staff_owner_id >> assignment_capacity >> subject_area;

        // Get non-fixed Title with spaces.
        std::string title;
        std::getline(iss, title);
        if (!title.empty() && title[0] == ' ') {
            title = title.substr(1); // this removes leading space
        }


        Project project(project_id, staff_owner_id,
        assignment_capacity, subject_area, title);
        project_dict_.insert({project_id, project});

        DEBUG_PRINT("Project ID: "<< project_id << ", ");
        DEBUG_PRINT("Supervisor: " << staff_owner_id << ", "); // staff owner. 
        DEBUG_PRINT("Capacity: " << assignment_capacity << ", ");
        DEBUG_PRINT("Subject Area: " << subject_area << ", ");
        DEBUG_PRINT("Title: " << title << "\n");
    
    }
    DEBUG_PRINT("Project dict data: " << project_dict_.size() << " in dict.\n\n");
    file.close();
}



void Allocator::save_allocation(const std::string& allocation_file) {
    std::ofstream file(allocation_file);

    for (auto const& entry : allocations_) {
        Allocation alloc = entry.second;
        file << alloc.student_id << " " << alloc.project_id << " " << alloc.staff_id << "\n";
    }

    file << calculate_score() << "\n";
    file.close();
}
// According to reqs: students first choice (4 points), second (3),
// third (2), fourth (1). staff's proposal (4), subject area match (2)
// 0 for illegal alloc.
int Allocator::calculate_score() const{
    int score = 0;

    for (const auto& entry : allocations_) {
        const Allocation& alloc = entry.second;

        // without this, students will be left with no supervisor but
        // they still get their project choice, so get a higher score anyway.
        // this doesn't fulfill allocation reqs.
        if (alloc.staff_id.empty()) {
            return -1;
        }
        // student preference score
        const Student& student = student_dict_.at(alloc.student_id);
        int choice_score = 0;

        for (size_t i = 0; i < student.project_preferences.size(); ++i) {
            if (student.project_preferences[i] == alloc.project_id) {
                if (i == 0) choice_score = 4;
                else if (i == 1) choice_score = 3;
                else if (i == 2) choice_score = 2;
                else if (i == 3) choice_score = 1;
                break;
            }
        }
        score += choice_score;

        if (!alloc.staff_id.empty()) {
            const Staff& staff = staff_dict_.at(alloc.staff_id);
            const Project& project = project_dict_.at(alloc.project_id);

            // highest priority - project proposer
            if (project.proposer_id == staff.staff_id) {
                score += 4;
            } else {
                // second priority - subject area match
                bool subject_match = false;
                for (const auto& area : staff.subject_areas) {
                    if (area == project.subject_area) {
                        subject_match = true;
                        break;
                    }
                }
                if (subject_match) score += 2;
            }
        }
    }
    // DEBUG_PRINT("Final Score: " << score << "\n");
    return score;
}

void Allocator::reset_allocations() {
    allocations_.clear();

    for (auto& entry : project_dict_) {
        Project& project = entry.second;
        project.current_allocation = 0;
    }

    for (auto& entry : staff_dict_) {
        Staff& staff = entry.second;
        staff.current_workload = 0;
    }
}

// example greedy algo with suggested improvement of repeating w/
// a different random order of students & staff, and then choosing
// the best one
void Allocator::perform_allocation() {
    max_score_ = -1;
    best_allocations_.clear();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    std::vector<std::string> student_ids;
    for (auto& entry : student_dict_) {
        student_ids.push_back(entry.first);
    }

    std::vector<std::string> staff_ids;
    for (auto& entry : staff_dict_) {
        staff_ids.push_back(entry.first);
    }

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        reset_allocations();

        // shuffle student and staff order
        std::shuffle(student_ids.begin(), student_ids.end(), rng);
        std::shuffle(staff_ids.begin(), staff_ids.end(), rng);

        // Phase 1 - allocate based on student preferences
        for (const auto& student_id : student_ids) {
            Student& student = student_dict_.at(student_id);

            for (const auto& project_id : student.project_preferences) {
                if (project_dict_.count(project_id)) {
                    Project& project = project_dict_.at(project_id);

                    if (project.is_available()) {
                        project.current_allocation++;

                        Allocation alloc;
                        alloc.student_id = student_id;
                        alloc.project_id = project_id;
                        alloc.staff_id = "";

                        allocations_[student_id] = alloc;
                        break;
                    }
                }
            }
        }

        // 1.5a assigns leftover students to staff proposals first, so staff scores are
        // at least maximised
        for (const auto& staff_id : staff_ids) {
            Staff& staff = staff_dict_.at(staff_id);
            if (!staff.able_to_supervise()) continue;

            for (auto& proj_entry : project_dict_) {
                Project& project = proj_entry.second;

                if (project.proposer_id == staff_id && project.is_available()) {

                    for (const auto& student_id : student_ids) {
                        if (allocations_.find(student_id) == allocations_.end()) {
                            project.current_allocation++;
                            staff.current_workload++;

                            Allocation alloc;
                            alloc.student_id = student_id;
                            alloc.project_id = project.project_id;
                            alloc.staff_id = staff_id;

                            allocations_[student_id] = alloc;
                            break;
                        }
                    }
                }
                if (!staff.able_to_supervise()) break;
            }
        }
        // 1.5b assigns leftover students to any remaining projects, as per reqs.
        for (const auto& student_id : student_ids) {
            if (allocations_.find(student_id) == allocations_.end()) {

                for (auto& proj_entry : project_dict_) {
                    Project& project = proj_entry.second;

                    if (project.is_available()) {
                        project.current_allocation++;

                        Allocation alloc;
                        alloc.student_id = student_id;
                        alloc.project_id = project.project_id;
                        alloc.staff_id = "";

                        allocations_[student_id] = alloc;
                        break;
                    }
                }
            }
        }

        // Phase 2 - assign supervisors
        // 2.1 - assigned based on project proposer
        for (const auto& staff_id : staff_ids) {
            Staff& staff = staff_dict_.at(staff_id);
            if (!staff.able_to_supervise()) continue;

            for (auto& alloc_entry : allocations_) {
                Allocation& alloc = alloc_entry.second;

                if (alloc.staff_id.empty()) {
                    Project& project = project_dict_.at(alloc.project_id);
                    if (project.proposer_id == staff.staff_id) {
                        alloc.staff_id = staff.staff_id;
                        staff.current_workload++;
                        if (!staff.able_to_supervise()) break;
                    }
                }
            }
        }

        // 2.2 - assign based on subject area match
        for (const auto& staff_id : staff_ids) {
            Staff& staff = staff_dict_.at(staff_id);
            if(!staff.able_to_supervise()) continue;

            for (auto& alloc_entry : allocations_) {
                Allocation& alloc = alloc_entry.second;
                if (alloc.staff_id.empty()) {
                    Project& project = project_dict_.at(alloc.project_id);
                    for (const auto& area : staff.subject_areas) {
                        if (area == project.subject_area) {
                            alloc.staff_id = staff.staff_id;
                            staff.current_workload++;
                            break;
                        }
                    }
                    if (!staff.able_to_supervise()) break;
                }
            }
        }

        // 2.3 - assign to any available staff
        for (const auto& staff_id : staff_ids) {
            Staff& staff = staff_dict_.at(staff_id);
            if(!staff.able_to_supervise()) continue;

            for (auto& alloc_entry : allocations_) {
                Allocation& alloc = alloc_entry.second;
                if (alloc.staff_id.empty()) {
                    alloc.staff_id = staff.staff_id;
                    staff.current_workload++;
                    if (!staff.able_to_supervise()) break;
                }
            }
        }

        // check if this is the best score so far
        int current_score = calculate_score();
        if (current_score != -1 && current_score > max_score_) {
            max_score_ = current_score;
            best_allocations_ = allocations_;
        }
    }

    allocations_ = best_allocations_;

}