#include "student.h"
#include "course.h"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
Student::Student(const string &fullName, int studentID)
    : studentID(studentID), fullName(fullName) {}

// Drop student from given course, return true if successful
bool Student::dropCourse(int studentID, Course *course) {
  if (isInCourse(studentID, course)) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
      if (*it == course) {
        courses.erase(it);
        course->removeStudent(this);
        return true;
      }
    }
  }
  return false;
}

// Add student to the given course, return true if successful
bool Student::addCourse(int studentID, Course *course) {
  if (!isInCourse(studentID, course)) {
    for (const auto *cour : courses) {
      if (cour->courseNumber == course->courseNumber) {
        return false; // Student is already enrolled in the course
      }
    }
    courses.push_back(course);
    course->addStudent(this);
    return true;
  }

  return false;
}

// Return true if student is in the given course
bool Student::isInCourse(int studentID, const Course *course) const {
  if (studentID == this->studentID) {
    return std::any_of(courses.begin(), courses.end(),
                       [&](const Course *cour) { return cour == course; });
  }
  return false;
}

// Overloaded stream insertion operator to print student details
ostream &operator<<(ostream &out, const Student &student) {
  out << "Student ID: " << student.studentID << "\n";
  out << "Last Name: " << student.fullName << "\n";
  return out;
}