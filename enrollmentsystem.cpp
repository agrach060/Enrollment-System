#include "enrollmentsystem.h"
#include "university.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

EnrollmentSystem::~EnrollmentSystem() {
  for (const auto &pair : universities) {
    delete pair.second;
  }
}
// Add university to the enrollment system
bool EnrollmentSystem::addUniversity(const string &name) {
  if (universities.count(name) == 0) {
    University *newUniversity = new University(name);
    universities[name] = newUniversity;
    return true;
  }
  return false;
}

// Set this university as the active university for other functions
bool EnrollmentSystem::setCurrentUniversity(const string &name) {
  if (universities.find(name) != universities.end()) {
    currentUniversity = universities[name];
    return true;
  }
  return false;
}

// Return the current active university name
string EnrollmentSystem::getUniversityName() const {
  if (currentUniversity != nullptr) {
    return currentUniversity->name;
  }
  return "";
}

// Read the student list for the current active university
bool EnrollmentSystem::readStudentList(const string &filename) {
  if (currentUniversity != nullptr) {
    currentUniversity->readStudentList(filename);
    return true;
  }
  return false;
}

// Read the course list for the current active university
bool EnrollmentSystem::readCourseList(const string &filename) {
  if (currentUniversity != nullptr) {
    currentUniversity->readCourseList(filename);
    return true;
  }
  return false;
}

// Read the student enrollment information for the current active university
bool EnrollmentSystem::readEnrollmentInfo(const string &filename) {
  if (currentUniversity != nullptr) {
    currentUniversity->readEnrollmentInfo(filename);
    return true;
  }
  return false;
}

// Drop student from given course, return true if successful
bool EnrollmentSystem::dropCourse(int studentID, const string &courseNumber) {
  if (currentUniversity != nullptr) {
    return currentUniversity->dropCourse(studentID, courseNumber);
  }
  return false;
}

// Add student to the given course, return true if successful
bool EnrollmentSystem::addCourse(int studentID, const string &courseNumber) {
  if (currentUniversity != nullptr) {
    return currentUniversity->addCourse(studentID, courseNumber);
  }
  return false;
}

// Return true if student is in the given course
bool EnrollmentSystem::isInCourse(int studentID,
                                  const string &courseNumber) const {
  if (currentUniversity != nullptr) {
    return currentUniversity->isInCourse(studentID, courseNumber);
  }
  return false;
}

// Return the courses student is enrolled in
string EnrollmentSystem::getEnrolledCourses(int studentID) const {
  if (currentUniversity != nullptr) {
    vector<string> enrolledCourses =
        currentUniversity->getEnrolledCourses(studentID);
    sort(enrolledCourses.begin(), enrolledCourses.end());
    string result = "[";
    for (const auto &course : enrolledCourses) {
      result += course + ", ";
    }
    if (!result.empty()) {
      result = result.substr(0, result.size() - 2);
    }
    result += "]";
    return result;
  }
  return "";
}

// Return the title for the course
string EnrollmentSystem::getCourseTitle(const string &courseNumber) {
  if (currentUniversity != nullptr) {
    return currentUniversity->getCourseTitle(courseNumber);
  }
  return "";
}

// Return class list sorted by last name of students
string
EnrollmentSystem::getClassListByLastName(const string &courseNumber) const {
  if (currentUniversity != nullptr) {
    vector<string> classList =
        currentUniversity->getClassListByLastName(courseNumber);
    sort(classList.begin(), classList.end());
    string result = "[";
    for (const auto &student : classList) {
      result += student + ", ";
    }
    if (!result.empty()) {
      result = result.substr(0, result.size() - 2);
    }
    result += "]";
    return result;
  }
  return "";
}

// Return class list sorted by id of students
string EnrollmentSystem::getClassListByID(const string &courseNumber) const {
  if (currentUniversity != nullptr) {
    vector<string> classList =
        currentUniversity->getClassListByID(courseNumber);
    string result = "[";
    for (const auto &student : classList) {
      result += student + ", ";
    }
    if (!result.empty()) {
      result = result.substr(0, result.size() - 2);
    }
    result += "]";
    return result;
  }
  return "";
}