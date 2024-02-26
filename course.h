#ifndef COURSE_H
#define COURSE_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// forward declaration
class Student;

//
class Course {
  friend class Student;

  friend class University;

  friend class EnrollmentSystem;

  friend ostream &operator<<(ostream &out, const Course &course);

public:
  // Constructor
  Course(string courseNumber, string courseName);

  // Adds a student to the course
  bool addStudent(Student *student);

  // Removes a student from the course
  bool removeStudent(const Student *student);

  // Returns all the classes that a student with a given last name is taking
  vector<string> getClassListByLastName() const;

  // Returns all the classes that a student with a given student ID is taking
  vector<string> getClassListByID() const;

  // Compares student IDs
  static bool cmpID(int studentID1, int studentID2);

private:
  // Stores Course Number
  string courseNumber;

  // Stores Course Name
  string courseName;

  // A vector of students in each class
  vector<Student *> students;
};

#endif