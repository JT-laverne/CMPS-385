#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// struct definitions
struct Name {
    string first;
    string last;
};

struct Scores {
    double exam1;
    double exam2;
    double exam3;
    double average;
    char letter;
};

struct Student {
    int id;
    Name name;
    string semester;
    Scores scores;
};

// function declarations
int generateUniqueID(Student gradebook[], int count);
void addStudent(Student gradebook[], int& count);
void updateScores(Student gradebook[], int count);
void displayStudentReport(Student gradebook[], int count);
void displaySemesterReport(Student gradebook[], int count);
void listAllStudents(Student gradebook[], int count);
char computeLetter(double avg);
void pressAnyKey();

// MAIN
int main() {
    const int MAX = 100;
    Student gradebook[MAX];
    int count = 0;
    int choice;

    srand(time(0));

    do {
        system("cls");
        cout << "*************** Faculty Gradebook ***************\n";
        cout << "Please choose one of the following operations\n";
        cout << "1 - Add a new student record\n";
        cout << "2 - Enter/Update scores (by ID)\n";
        cout << "3 - Display report for a student (by ID)\n";
        cout << "4 - Display report for a semester\n";
        cout << "5 - List all students\n";
        cout << "0 - Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: addStudent(gradebook, count); break;
        case 2: updateScores(gradebook, count); break;
        case 3: displayStudentReport(gradebook, count); break;
        case 4: displaySemesterReport(gradebook, count); break;
        case 5: listAllStudents(gradebook, count); break;
        case 0:
            cout << "Thank you for using the Faculty Gradebook!\nGoodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            pressAnyKey();
        }
    } while (choice != 0);

    return 0;
}

//Function definitions:
int generateUniqueID(Student gradebook[], int count) {
    int id;
    bool unique;
    do {
        id = 10000 + rand() % 90000;
        unique = true;
        for (int i = 0; i < count; i++) {
            if (gradebook[i].id == id) {
                unique = false;
                break;
            }
        }
    } while (!unique);
    return id;
}

void addStudent(Student gradebook[], int& count) {
    if (count >= 100) {
        cout << "Gradebook is full! Cannot add more students.\n";
        pressAnyKey();
        return;
    }

    Student s;
    cout << "First name: ";
    getline(cin, s.name.first);
    cout << "Last name: ";
    getline(cin, s.name.last);
    cout << "Semester (e.g., Fall 2025): ";
    getline(cin, s.semester);

    s.id = generateUniqueID(gradebook, count);
    s.scores = { 0, 0, 0, 0, 'F' };

    gradebook[count++] = s;

    cout << "Great! " << s.name.first << " " << s.name.last << " has been added.\n";
    cout << "Assigned Student ID: " << s.id << "\n";
    pressAnyKey();
}

void updateScores(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students to update.\n";
        pressAnyKey();
        return;
    }

    int id;
    cout << "Enter student ID: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (gradebook[i].id == id) {
            found = true;
            cout << "Enter Exam 1 (0-100): ";
            cin >> gradebook[i].scores.exam1;
            cout << "Enter Exam 2 (0-100): ";
            cin >> gradebook[i].scores.exam2;
            cout << "Enter Exam 3 (0-100): ";
            cin >> gradebook[i].scores.exam3;

            double avg = (gradebook[i].scores.exam1 + gradebook[i].scores.exam2 + gradebook[i].scores.exam3) / 3.0;
            gradebook[i].scores.average = avg;
            gradebook[i].scores.letter = computeLetter(avg);

            cout << "Scores updated for " << gradebook[i].name.first << " " << gradebook[i].name.last
                << " (ID: " << gradebook[i].id << ").\n";
            cout << fixed << setprecision(2);
            cout << "Average: " << gradebook[i].scores.average << "\n";
            cout << "Letter: " << gradebook[i].scores.letter << "\n";
            break;
        }
    }

    if (!found)
        cout << "Student ID not found.\n";

    pressAnyKey();
}

void displayStudentReport(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students in the gradebook.\n";
        pressAnyKey();
        return;
    }

    int id;
    cout << "Enter student ID: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (gradebook[i].id == id) {
            found = true;
            cout << "------ Student Report ------\n";
            cout << "Name: " << gradebook[i].name.last << ", " << gradebook[i].name.first << endl;
            cout << "ID: " << gradebook[i].id << endl;
            cout << "Semester: " << gradebook[i].semester << endl;
            cout << "Exam 1: " << gradebook[i].scores.exam1 << endl;
            cout << "Exam 2: " << gradebook[i].scores.exam2 << endl;
            cout << "Exam 3: " << gradebook[i].scores.exam3 << endl;
            cout << fixed << setprecision(2);
            cout << "Average: " << gradebook[i].scores.average << endl;
            cout << "Letter: " << gradebook[i].scores.letter << endl;
            cout << "----------------------------\n";
            break;
        }
    }

    if (!found)
        cout << "Student ID not found.\n";

    pressAnyKey();
}

void displaySemesterReport(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students in the gradebook.\n";
        pressAnyKey();
        return;
    }

    string sem;
    cout << "Enter semester (e.g., Fall 2025): ";
    getline(cin, sem);

    bool found = false;
    double totalAvg = 0, highest = -1, lowest = 101;
    int semCount = 0;

    cout << "ID | Name | E1 E2 E3 | Avg | Letter\n";
    cout << "-------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        if (gradebook[i].semester == sem) {
            found = true;
            semCount++;
            double avg = gradebook[i].scores.average;
            totalAvg += avg;
            if (avg > highest) highest = avg;
            if (avg < lowest) lowest = avg;

            cout << gradebook[i].id << " | "
                << gradebook[i].name.last << ", " << gradebook[i].name.first << " | "
                << gradebook[i].scores.exam1 << " "
                << gradebook[i].scores.exam2 << " "
                << gradebook[i].scores.exam3 << " | "
                << fixed << setprecision(2) << avg << " | "
                << gradebook[i].scores.letter << "\n";
        }
    }

    if (!found) {
        cout << "No records for that semester.\n";
    }
    else {
        cout << "Students: " << semCount << endl;
        cout << "Semester Average: " << fixed << setprecision(2) << (totalAvg / semCount) << endl;
        cout << "Highest Average: " << highest << endl;
        cout << "Lowest Average: " << lowest << endl;
    }

    pressAnyKey();
}

void listAllStudents(Student gradebook[], int count) {
    if (count == 0) {
        cout << "No students added yet.\n";
    }
    else {
        cout << "ID | Name | Semester\n";
        cout << "-----------------------------------------\n";
        for (int i = 0; i < count; i++) {
            cout << gradebook[i].id << " | "
                << gradebook[i].name.last << ", " << gradebook[i].name.first
                << " | " << gradebook[i].semester << "\n";
        }
    }
    pressAnyKey();
}

char computeLetter(double avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

void pressAnyKey() {
    cout << "Press any key to return to Main Menu!";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
