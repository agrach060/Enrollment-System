#include "university.h"
#include "student.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Constructs a new University
// `name` is the name of this university
University::University(string name) : name(name) {}

// Destructor to deallocate dynamically allocated memory
University::~University() {
  for (auto &course : courses) {
    delete course.second;
  }

  for (auto &student : students) {
    delete student.second;
  }
}

// Read the student list for the current active university
bool University::readStudentList(const string &filename) {
  ifstream file(filename);
  if (!file) {
    return false;
  }

  vector<Student> tempStudents; // Temporary vector to store students

  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    int studentID;
    string lastName;
    string firstName;
    if (iss >> studentID >> firstName >> lastName) {
      string fullName = lastName + ", " + firstName;
      tempStudents.push_back(
          Student(fullName, studentID)); // Add student to temporary vector
    }
  }

  file.close();

  // Reverse the order of students in the temporary vector
  reverse(tempStudents.begin(), tempStudents.end());

  // Add the students to the 'students' map
  for (const auto &student : tempStudents) {
    if (students.count(student.studentID) != 0) {
      delete students[student.studentID];
    }
    students[student.studentID] =
        new Student(student.fullName, student.studentID);
  }

  return true;
}

// Read the course list for the current active university
bool University::readCourseList(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  vector<Course> tempCourses;
  string line;
  while (getline(file, line)) {
    stringstream stringStream(line);
    string courseNumber;
    string courseName;
    stringStream >> courseNumber;
    getline(stringStream >> ws, courseName);
    tempCourses.push_back(Course(courseNumber, courseName));
  }
  file.close();

  for (const auto &course : tempCourses) {
    if (courses.count(course.courseNumber) != 0) {
      delete courses[course.courseNumber];
    }
    courses[course.courseNumber] =
        new Course(course.courseNumber, course.courseName);
  }
  return true;
}

// Read the student enrollment information for the current active university
bool University::readEnrollmentInfo(const string &filename) {
  ifstream file(filename);
  if (!file) {
    return false;
  }

  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    int studentID;
    string courseNumber;
    if (iss >> studentID >> courseNumber) {
      if (students.find(studentID) != students.end() &&
          courses.find(courseNumber) != courses.end()) {
        students[studentID]->addCourse(studentID, courses[courseNumber]);
      }
    }
  }

  file.close();
  return true;
}

// Drop student from given course, return true if successful
bool University::dropCourse(int studentID, const string &courseNumber) {
  if (students.find(studentID) != students.end() &&
      courses.find(courseNumber) != courses.end()) {
    return students[studentID]->dropCourse(studentID, courses[courseNumber]);
  }
  return false;
}

// Add student to the given course, return true if successful
bool University::addCourse(int studentID, const string &courseNumber) {
  if (students.find(studentID) != students.end() &&
      courses.find(courseNumber) != courses.end()) {
    return students[studentID]->addCourse(studentID, courses[courseNumber]);
  }
  return false;
}

// Return true if student is in the given course
bool University::isInCourse(int studentID, const string &courseNumber) const {
  if (students.find(studentID) != students.end() &&
      courses.find(courseNumber) != courses.end()) {
    return students.at(studentID)->isInCourse(studentID,
                                              courses.at(courseNumber));
  }
  return false;
}

// Return the title for the course
string University::getCourseTitle(const string &courseNumber) const {
  if (courses.find(courseNumber) != courses.end()) {
    return courses.at(courseNumber)->courseName;
  }
  return "";
}

// Return the courses a student is enrolled in
vector<string> University::getEnrolledCourses(int studentID) const {
  vector<string> enrolledCourses;
  if (students.find(studentID) != students.end()) {
    vector<const Course *> &courses = students.at(studentID)->courses;
    for (const auto *course : courses) {
      enrolledCourses.push_back(course->courseNumber);
    }
  }
  return enrolledCourses;
}

// Return class list sorted by last name of students
vector<string>
University::getClassListByLastName(const string &courseNumber) const {
  vector<string> classList;
  if (courses.find(courseNumber) != courses.end()) {
    const vector<string> &classListFromCourse =
        courses.at(courseNumber)->getClassListByLastName();
    classList = classListFromCourse;
    sort(classList.begin(), classList.end());
  }
  return classList;
}

// Return class list sorted by id of students
vector<string> University::getClassListByID(const string &courseNumber) const {
  vector<string> classList;
  if (courses.find(courseNumber) != courses.end()) {
    const vector<string> &classListFromCourse =
        courses.at(courseNumber)->getClassListByID();
    classList = classListFromCourse;
  }
  return classList;
}