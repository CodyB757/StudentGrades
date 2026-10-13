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
    return 0;
}