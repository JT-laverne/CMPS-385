#include <iostream>
using namespace std;

//Recursive Function Declarations
void displayGrades(int grades[], int size, int index = 0) {
    if (index == size) return;        // Base case
    cout << grades[index] << " ";
    displayGrades(grades, size, index + 1);// Recursive call
}

int sumGrades(int grades[], int size) {
    if (size == 0) return 0;
    return grades[size - 1] + sumGrades(grades, size - 1);
}

int countFailing(int grades[], int size) {
    if (size == 0) return 0;
    int fail = (grades[size - 1] < 60) ? 1 : 0;
    return fail + countFailing(grades, size - 1);
}

int findMax(int grades[], int size, int index = 0, int currentMax = -1) {
    if (index == size) return currentMax;

    if (grades[index] > currentMax)
        currentMax = grades[index];

    return findMax(grades, size, index + 1, currentMax);
}

//Main
int main() {
    const int MAX = 100;
    int grades[MAX];
    int gradeCount = 0;

    int choice;

    cout << "****** Welcome to Recursive Grade Analyzer ******\n";

    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1. Enter Grades\n";
        cout << "2. Display Grades\n";
        cout << "3. Calculate Average Grade (using Recursion)\n";
        cout << "4. Count Failing Grades (using Recursion)\n";
        cout << "5. Find Highest Grade (using Recursion)\n";
        cout << "6. Exit\n";
        cout << "→ ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "How many grades do you want to enter?\n→ ";
            cin >> gradeCount;

            if (gradeCount < 0 || gradeCount > MAX) {
                cout << "Invalid number of grades.\n";
                gradeCount = 0;
                break;
            }

            for (int i = 0; i < gradeCount; i++) {
                cout << "Enter grade #" << (i + 1) << ": ";
                cin >> grades[i];
            }
            cout << "Grades successfully saved!\n";
            break;
        }

        case 2:
            if (gradeCount == 0) {
                cout << "No grades to display.\n";
            }
            else {
                cout << "Grades entered:\n→ ";
                displayGrades(grades, gradeCount);
                cout << "\n";
            }
            break;

        case 3:
            if (gradeCount == 0) {
                cout << "No grades available.\n";
            }
            else {
                double average = static_cast<double>(sumGrades(grades, gradeCount)) / gradeCount;
                cout << "The average grade is: " << average << "\n";
            }
            break;

        case 4:
            if (gradeCount == 0) {
                cout << "No grades available.\n";
            }
            else {
                int failCount = countFailing(grades, gradeCount);
                cout << "Number of failing grades: " << failCount << "\n";
            }
            break;

        case 5:
            if (gradeCount == 0) {
                cout << "No grades available.\n";
            }
            else {
                int highest = findMax(grades, gradeCount);
                cout << "Highest grade: " << highest << "\n";
            }
            break;

        case 6:
            cout << "Thank you for using Recursive Grade Analyzer!\n";
            break;

        default:
            cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
