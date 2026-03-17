#include <iostream>
#include <fstream>
using namespace std;

class Student {
    int id;
    char name[50];
    float marks;

public:
    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nMarks: " << marks << endl;
    }

    int getId() {
        return id;
    }
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("student.dat", ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
}

// Display All
void displayAll() {
    Student s;
    ifstream file("student.dat", ios::binary);
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "-------------------";
    }
    file.close();
}

// Search Student
void searchStudent(int id) {
    Student s;
    bool found = false;
    ifstream file("student.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == id) {
            s.display();
            found = true;
        }
    }

    if (!found)
        cout << "Student not found!";
    file.close();
}

// Delete Student
void deleteStudent(int id) {
    Student s;
    ifstream file("student.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() != id) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("student.dat");
    rename("temp.dat", "student.dat");

    cout << "Record deleted successfully!";
}

// Update Student
void updateStudent(int id) {
    Student s;
    fstream file("student.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getId() == id) {
            cout << "Enter new details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record updated!";
            return;
        }
    }

    cout << "Student not found!";
    file.close();
}

int main() {
    int choice, id;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search\n";
        cout << "4. Update\n";
        cout << "5. Delete\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                cout << "Enter ID: ";
                cin >> id;
                searchStudent(id);
                break;
            case 4:
                cout << "Enter ID: ";
                cin >> id;
                updateStudent(id);
                break;
            case 5:
                cout << "Enter ID: ";
                cin >> id;
                deleteStudent(id);
                break;
        }

    } while (choice != 6);

    return 0;
}