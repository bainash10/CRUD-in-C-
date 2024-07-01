#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
};

void createRecord() {
    ofstream file("students.txt", ios::app);

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student student;
    cout << "Enter name: ";
    cin >> student.name;
    cout << "Enter age: ";
    cin >> student.age;

    file << student.name << " " << student.age << endl;

    file.close();
}

void displayRecords() {
    ifstream file("students.txt");

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string name;
    int age;

    cout << "\nList of Students:\n";
    while (file >> name >> age) {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    file.close();
}

void updateRecord() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string name;
    int newAge;
    bool found = false;
    Student student;

    cout << "Enter name to update: ";
    cin >> name;
    cout << "Enter new age: ";
    cin >> newAge;

    while (file >> student.name >> student.age) {
        if (student.name == name) {
            temp << student.name << " " << newAge << endl;
            found = true;
        } else {
            temp << student.name << " " << student.age << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found) {
        cout << "Record not found!" << endl;
    } else {
        cout << "Record updated successfully." << endl;
    }
}

void deleteRecord() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string name;
    bool found = false;
    Student student;

    cout << "Enter name to delete: ";
    cin >> name;

    while (file >> student.name >> student.age) {
        if (student.name == name) {
            found = true;
        } else {
            temp << student.name << " " << student.age << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found) {
        cout << "Record not found!" << endl;
    } else {
        cout << "Record deleted successfully." << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\nCRUD Operations on Students Records\n";
        cout << "1. Create Record\n";
        cout << "2. Display Records\n";
        cout << "3. Update Record\n";
        cout << "4. Delete Record\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                updateRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}

