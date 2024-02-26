#include "course.h"
#include "student.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

Course::Course(string courseNumber, string courseName)
    : courseNumber(move(courseNumber)), courseName(move(courseName)) {}

// Adds a student to the course
bool Course::addStudent(Student *student) {
  for (const Student *stu : students) {
    if (stu->studentID == student->studentID) {
      return false; // Student is already enrolled
    }
  }
  students.push_back(student);
  return true;
}

// Removes a student from the course
bool Course::removeStudent(const Student *student) {
  for (auto it = students.begin(); it != students.end(); ++it) {
    if (*it == student) {
      students.erase(it);
      return true;
    }
  }
  return false; // Student not found
}

// Returns all the classes that a student with a given last name is taking
vector<string> Course::getClassListByLastName() const {
  vector<string> classList;
  for (const auto *student : students) {
    string studentInfo =
        student->fullName + " (" + to_string(student->studentID) + ")";
    classList.push_back(studentInfo);
  }
  return classList;
}

// Return class list sorted by id of students
vector<string> Course::getClassListByID() const {
  vector<string> classList;

  for (const auto *student : students) {
    string studentInfo =
        student->fullName + " (" + to_string(student->studentID) + ")";
    classList.push_back(studentInfo);
  }
  // Sort the class list by student IDs
  sort(classList.begin(), classList.end(),
       [this](const string &studentInfo1, const string &studentInfo2) {
         // Extract student IDs from studentInfo strings
         int studentID1 = stoi(studentInfo1.substr(studentInfo1.find('(') + 1));
         int studentID2 = stoi(studentInfo2.substr(studentInfo2.find('(') + 1));

         // Compare student IDs using cmpID function
         return cmpID(studentID1, studentID2);
       });
  return classList;
}

// Compares student IDs
bool Course::cmpID(int studentID1, int studentID2) {
  return studentID1 < studentID2;
}

// Overloaded stream insertion operator to print course details
ostream &operator<<(ostream &out, const Course &course) {
  out << "Course Number: " << course.courseNumber << "\n";
  out << "Course Name: " << course.courseName << "\n";
  return out;
}
