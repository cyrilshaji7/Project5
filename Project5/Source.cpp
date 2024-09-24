#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA {
    string firstName;
    string lastName;
    string email; 
};

void readStudentData(const string& filename, vector<STUDENT_DATA>& students) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    while (getline(file, line)) {
        istringstream ss(line);
        string firstName, lastName;

        if (getline(ss, firstName, ',') && getline(ss, lastName)) {
            STUDENT_DATA student;
            student.firstName = firstName;
            student.lastName = lastName;
            students.push_back(student);
        }
    }

    file.close();
}

void readStudentEmails(const string& filename, vector<STUDENT_DATA>& students) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    int index = 0;
    while (getline(file, line)) {
        if (index < students.size()) {
            students[index].email = line; 
            index++;
        }
    }

    file.close();
}

void displayStudents(const vector<STUDENT_DATA>& students) {
    cout << "Student List:\n";
    for (const auto& student : students) {
        cout << student.firstName << " " << student.lastName;
#ifdef PRE_RELEASE
        cout << ", Email: " << student.email; 
#endif
        cout << endl;
    }
}

int main() {
    vector<STUDENT_DATA> students;

    readStudentData("C:\\Users\\Cyril\\Downloads\\resource-files\\StudentData.txt", students);

#ifdef PRE_RELEASE
    cout << "Running in Pre-Release Mode\n";
    readStudentEmails("C:\\Users\\Cyril\\Downloads\\resource-files\\StudentData_Emails.txt", students);
#else
    cout << "Running in Standard Mode\n";
#endif

#ifdef _DEBUG
    cout << "Debug Mode: Printing all student information:\n";
    for (const auto& student : students) {
        cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName << endl;
    }
#endif

    return 1;
}
