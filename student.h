#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// forward declaration
class Course;

class Student {
  friend class Course;
  friend class University;
  friend class EnrollmentSystem;
  friend ostream &operator<<(ostream &out, const Student &student);

private:
  // stores the ID of the student
  int studentID;
  // stores the last name of the student
  string fullName;
  // map of student IDs to student names
  map<int, string> students;
  // vector of pointers to courses the student is enrolled in
  vector<const Course *> courses;

public:
  // Constructor
  Student(const string &fullName, int studentID);

  // Drop student from given course, return true if successful
  bool dropCourse(int studentID, Course *course);

  // Add student to the given course, return true if successful
  bool addCourse(int studentID, Course *course);

  // Return true if student is in the given course
  bool isInCourse(int studentID, const Course *course) const;
};

#endif