#include <iostream>
#include <string>

using namespace std;

struct Class {
    std::string name;
    int size;
    double* grade;
};

int main()
{
    Class c1;
    c1.grade = new double[c1.size]; //make an array with the specific size of user's later input for "c1.size"

    cout << "Enter the class name: ";
    getline(cin, c1.name);

    cout << "Enter the class size: ";
    cin >> c1.size;

    //Get user grade input
    cout << "Enter all " << c1.size << " grade(s):" << endl;
    for (int i = 0; i < c1.size; i++) {
        cout << "Grade " << i + 1 << ": ";
        cin >> c1.grade[i];
    }

    // Calculate Max
    int max = c1.grade[0]; // assume first element is max

    for (int i = 1; i < c1.size; i++) {
        if (c1.grade[i] > max) {
            max = c1.grade[i];
        }
    }

    // Calculate Min
    int min = c1.grade[0]; // assume first element is min

    for (int i = 1; i < c1.size; i++) {
        if (c1.grade[i] > min) {
            min = c1.grade[i];
        }
    }

    // Calculate Average
    int sum = 0;

    for (int i = 0; i < c1.size; i++) {
        sum += c1.grade[i];
    }

    double ave = static_cast<double>(sum) / c1.size;

    //Output Results
    cout << "\nClass Name: " << c1.name;
    cout << "\nClass Size: " << c1.size;
    cout << "\nClass Max: " << max;
    cout << "\nClass Min: " << min;
    cout << "\nClass Ave: " << ave;
}

