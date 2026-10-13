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

    if (!openInputFile(inFile, FILENAME)) {
        return 1;
    }

    std::cout << "File opened successfully!\n";
    inFile.close();

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