#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

class Logger {
public:
    static Logger& instance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& msg) {
        std::ofstream logfile;
        logfile.open("log.txt", std::ios_base::app);
        logfile << msg << std::endl;
    }

private:
    Logger() = default;
};

class Student {
    int id;
    std::string surname, name;
    std::string dob;
    std::string phone_number;
    std::string faculty;
    std::string course;
    std::string group;

public:
    Student(int id, const std::string& surname, const std::string& name, const std::string& dob, 
            const std::string& phone_number, const std::string& faculty, 
            const std::string& course, const std::string& group)
        : id(id), surname(surname), name(name), dob(dob), phone_number(phone_number), 
          faculty(faculty), course(course), group(group) {}

    const std::string& getFaculty() const { return faculty; }
    const std::string& getCourse() const { return course; }
    const std::string& getDOB() const { return dob; }
    const std::string& getGroup() const { return group; }
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

std::ostream& operator<<(std::ostream& os, const Student& s) {
    return os << "ID: " << s.id << " Name: " << s.name << " " << s.surname;
}

int main() {
    std::vector<Student> students = {
        {1, "Smith", "John", "2002-06-01", "+1234567890", "Comp Sci", "CS101", "A"},
        {2, "Doe", "Jane", "2001-09-12", "+0987654321", "Comp Sci", "CS102", "B"},
        {3, "Leila", "Jane", "2003-09-12", "+5437654321", "Bioscience", "BIO101", "B"},
        // Add more students as needed...
    };
    
    std::string faculty = "Comp Sci";

    Logger::instance().log("Listing students in faculty " + faculty + "...");
    std::cout << "Listing students in faculty" << std::endl;
    for (const auto& student : students) {
        if (student.getFaculty() == faculty) {
            std::cout << student << std::endl;
        }
    }
    std::cout << "====" << std::endl;
    
    std::cout << "Listing students for each faculty and course..." << std::endl;
    Logger::instance().log("Listing students for each faculty and course...");
    std::map<std::string, std::vector<Student>> facultyCourseMap;
    for (const auto& student : students) {
        std::string key = student.getFaculty() + "-" + student.getCourse();
        facultyCourseMap[key].push_back(student);
    }
    
    for (const auto& pair : facultyCourseMap) {
        std::cout << pair.first << ":\n";
        for (const auto& student : pair.second) {
            std::cout << student << '\n';
        }
        std::cout << '\n';
    }
    std::cout << "====" << std::endl;
    
    std::cout << "Listing students born after a given yea (2001)r..." << std::endl;
    // List of students born after a given year
    Logger::instance().log("Listing students born after a given year...");
    std::string givenYear = "2001";
    for (const auto& student : students) {
        if (student.getDOB().substr(0, 4) > givenYear) {
            std::cout << student << std::endl;
        }
    }
    std::cout << "====" << std::endl;
    
    std::cout << "Listing students of a study group (A)..." << std::endl;
    // List of students of a study group
    Logger::instance().log("Listing students of a study group...");
    std::string studyGroup = "A";
    for (const auto& student : students) {
        if (student.getGroup() == studyGroup) {
            std::cout << student << std::endl;
        }
    }
    std::cout << "====" << std::endl;
    return 0;
}


