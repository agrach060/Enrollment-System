#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "course.h"
#include "student.h"
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class University {
  friend class EnrollmentSystem;

private:       // this class should only be used in `EnrollmentSystem`
  string name; // the name of this university
  map<int, Student *> students;            // maps student ids to Student*
  unordered_map<string, Course *> courses; // maps course number to Course*

public:
  // constructs a new University
  // `name` is the name of this university
  explicit University(string name);

  // destructs this University object
  // deletes all `Course`/`Student` objects
  ~University();

  // Read the student list for current active university
  // return true if file successfully read
  bool readStudentList(const string &filename);

  // Read the course list for current active university
  // return true if file successfully read
  bool readCourseList(const string &filename);

  // Read the student enrollment information for current active university
  // return true if file successfully read
  bool readEnrollmentInfo(const string &filename);

  // Drop student from given course, return true if successful
  bool dropCourse(int studentID, const string &courseNumber);

  // Add student to the given course, return true if successful
  bool addCourse(int studentID, const string &courseNumber);

  // Return true if student is in the given course
  bool isInCourse(int studentID, const string &courseNumber) const;

  // Return the title for the course
  string getCourseTitle(const string &courseNumber) const;

  // Return the courses student is enrolled in
  vector<string> getEnrolledCourses(int studentID) const;

  // Return class list sorted by last name of students
  vector<string> getClassListByLastName(const string &courseNumber) const;

  // Return class list sorted by id of students
  vector<string> getClassListByID(const string &courseNumber) const;
};

#endif