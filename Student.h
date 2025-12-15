#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student{
    public:
        //Constructors.
        Student() = default;
        Student(const std::string& id, const std::vector<std::string>& preferences);
        // Attribtues.
        std::string student_id;
        std::vector<std::string> project_preferences;
        
};


#endif //STUDENT_H