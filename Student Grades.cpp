#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

struct Student {
    std::string lastName;
    int studentID;
    double* scores;
    double average;
    char letterGrade;
};

bool openInputFile(std::ifstream& inFile, const std::string& filename);
bool readGradeData(std::ifstream& inFile, Student*& students, int& numStudents, int& numTests);
void calculateAverages(Student* students, int numStudents, int numTests);
void assignLetterGrades(Student* students, int numStudents);
void displayReport(const Student* students, int numStudents, int numTests);
void releaseMemory(Student*& students, int numStudents);

int main() {
    const std::string FILENAME = "student_data.txt";
    std::ifstream inFile;

    Student* students = nullptr;
    int numStudents = 0;
    int numTests = 0;

    if (!openInputFile(inFile, FILENAME)) {
        return 1;
    }

    if (!readGradeData(inFile, students, numStudents, numTests)) {
        inFile.close();
        releaseMemory(students, numStudents);
        return 1;
    }

    inFile.close();

    std::cout << "Successfully read " << numStudents << " students with "
        << numTests << " test scores each.\n";

    if (students != nullptr) {
        for (int i = 0; i < numStudents; ++i) {
            delete[] students[i].scores;
        }
        delete[] students;
        students = nullptr;
    }

    return 0;
}

bool openInputFile(std::ifstream& inFile, const std::string& filename) {
    inFile.open(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open input file '" << filename << "'.\n";
        return false;
    }
    return true;
}

bool readGradeData(std::ifstream& inFile, Student*& students, int& numStudents, int& numTests) {
    if (!(inFile >> numStudents >> numTests)) {
        std::cerr << "Error: Failed to read file header dimensions.\n";
        return false;
    }

    if (numStudents <= 0 || numTests <= 0) {
        std::cerr << "Error: Invalid header dimensions (Students: "
            << numStudents << ", Tests: " << numTests
            << "). Counts must be positive integers.\n";
        return false;
    }

    students = new Student[numStudents];

    for (int i = 0; i < numStudents; ++i) {
        students[i].scores = nullptr;
    }

    for (int i = 0; i < numStudents; ++i) {
        if (!(inFile >> students[i].lastName >> students[i].studentID)) {
            std::cerr << "Error: Failed to read record header for student index " << i << ".\n";
            return false;
        }

        students[i].scores = new double[numTests];

        for (int j = 0; j < numTests; ++j) {
            if (!(inFile >> students[i].scores[j])) {
                std::cerr << "Error: Failed to read score " << (j + 1)
                    << " for student " << students[i].lastName << ".\n";
                return false;
            }
        }
    }

    return true;
}

void releaseMemory(Student*& students, int numStudents) {
}