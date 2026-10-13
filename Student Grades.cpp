#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Student {
    string lastName;
    int studentID;
    double* scores;
    double average;
    char letterGrade;
};

bool openInputFile(ifstream& inFile, const string& filename);
bool readGradeData(ifstream& inFile, Student*& students, int& numStudents, int& numTests);
void calculateAverages(Student* students, int numStudents, int numTests);
void assignLetterGrades(Student* students, int numStudents);
void displayReport(const Student* students, int numStudents, int numTests);
void releaseMemory(Student*& students, int numStudents);

int main() {
    const string FILENAME = "student_data.txt";
    ifstream inFile;

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

    calculateAverages(students, numStudents, numTests);
    assignLetterGrades(students, numStudents);
    displayReport(students, numStudents, numTests);

    releaseMemory(students, numStudents);

    return 0;
}

bool openInputFile(ifstream& inFile, const string& filename) {
    inFile.open(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open input file '" << filename << "'.\n";
        return false;
    }
    return true;
}

bool readGradeData(ifstream& inFile, Student*& students, int& numStudents, int& numTests) {
    if (!(inFile >> numStudents >> numTests)) {
        cerr << "Error: Failed to read file header dimensions.\n";
        return false;
    }

    if (numStudents <= 0 || numTests <= 0) {
        cerr << "Error: Invalid header dimensions (Students: "
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
            cerr << "Error: Failed to read record header for student index " << i << ".\n";
            return false;
        }

        students[i].scores = new double[numTests];

        for (int j = 0; j < numTests; ++j) {
            if (!(inFile >> students[i].scores[j])) {
                cerr << "Error: Failed to read score " << (j + 1)
                    << " for student " << students[i].lastName << ".\n";
                return false;
            }
        }
    }

    return true;
}

void calculateAverages(Student* students, int numStudents, int numTests) {
    if (students == nullptr || numStudents <= 0 || numTests <= 0) {
        return;
    }

    for (int i = 0; i < numStudents; ++i) {
        double total = 0.0;
        for (int j = 0; j < numTests; ++j) {
            total += students[i].scores[j];
        }
        students[i].average = total / numTests;
    }
}

void assignLetterGrades(Student* students, int numStudents) {
    if (students == nullptr || numStudents <= 0) {
        return;
    }

    for (int i = 0; i < numStudents; ++i) {
        double avg = students[i].average;
        if (avg >= 90.0) {
            students[i].letterGrade = 'A';
        }
        else if (avg >= 80.0) {
            students[i].letterGrade = 'B';
        }
        else if (avg >= 70.0) {
            students[i].letterGrade = 'C';
        }
        else if (avg >= 60.0) {
            students[i].letterGrade = 'D';
        }
        else {
            students[i].letterGrade = 'F';
        }
    }
}

void displayReport(const Student* students, int numStudents, int numTests) {
    if (students == nullptr || numStudents <= 0) {
        return;
    }

    cout << "\n=================================================================================\n";
    cout << "                             COURSE GRADE REPORT\n";
    cout << "=================================================================================\n";

    cout << left << setw(12) << "Last Name"
        << setw(10) << "ID";

    for (int j = 0; j < numTests; ++j) {
        string testHeader = "T" + to_string(j + 1);
        cout << right << setw(8) << testHeader;
    }

    cout << right << setw(10) << "Average"
        << setw(8) << "Grade" << "\n";

    cout << "---------------------------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < numStudents; ++i) {
        cout << left << setw(12) << students[i].lastName
            << setw(10) << students[i].studentID;

        for (int j = 0; j < numTests; ++j) {
            cout << right << setw(8) << students[i].scores[j];
        }

        cout << right << setw(10) << students[i].average
            << setw(8) << students[i].letterGrade << "\n";
    }

    cout << "=================================================================================\n\n";
}

void releaseMemory(Student*& students, int numStudents) {
    if (students == nullptr) {
        return;
    }

    for (int i = 0; i < numStudents; ++i) {
        if (students[i].scores != nullptr) {
            delete[] students[i].scores;
            students[i].scores = nullptr;
        }
    }

    delete[] students;
    students = nullptr;
}