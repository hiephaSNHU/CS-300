//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Hiep Ha
// Version     : 1.0
// Description : CS-300 Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
//Course Struct
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};
//BST Node Structure
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course courseData) : course(courseData), left(nullptr), right(nullptr) {}
};
//Class for Binary Search Tree
class CourseBST {
private:
    Node* root;

    void insertNode(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.courseNumber < node->course.courseNumber) {
            insertNode(node->left, course);
        }
        else {
            insertNode(node->right, course);
        }
    }

    void printInOrder(Node* node) const {
        if (node == nullptr) return;
        printInOrder(node->left);
        cout << node->course.courseNumber << ": " << node->course.title << endl;
        printInOrder(node->right);
    }

    Node* searchNode(Node* node, const string& courseNumber) const {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        }
        else {
            return searchNode(node->right, courseNumber);
        }
    }

public:
    CourseBST() : root(nullptr) {}

    void insert(Course course) {
        insertNode(root, course);
    }

    void printAllCourses() const {
        printInOrder(root);
    }

    Node* search(const string& courseNumber) const {
        return searchNode(root, courseNumber);
    }
};
//Load Courses from File
void loadCoursesFromFile(const string& fileName, CourseBST& bst) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid course entry - less than two parameters" << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        bst.insert(course);
    }

    file.close();
}
//Print Course Information
void printCourseInfo(CourseBST& bst, const string& courseNumber) {
    Node* courseNode = bst.search(courseNumber);
    if (courseNode != nullptr) {
        cout << "Course: " << courseNode->course.courseNumber << " - " << courseNode->course.title << endl;
        if (!courseNode->course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const string& prereq : courseNode->course.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
        else {
            cout << "This course has no prerequisites." << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}
//Menu and Main Function
void displayMenu() {
    cout << "1. Load courses" << endl;
    cout << "2. Print all courses (alphanumeric order)" << endl;
    cout << "3. Print course information and prerequisites" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    CourseBST bst;
    int choice;
    string fileName, courseNumber;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadCoursesFromFile(fileName, bst);
            break;
        case 2:
            bst.printAllCourses();
            break;
        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            printCourseInfo(bst, courseNumber);
            break;
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option, try again." << endl;
        }
    } while (choice != 9);

    return 0;
}

