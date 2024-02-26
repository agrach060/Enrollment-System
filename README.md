# Project 5 

### _CSS 342, Spring 2023_

### Design: Group 8: Dustin Standish, Matt Taniguchi, Anna Gracheva, Quynh Lam

### PAIR: Anna Gracheva and Quyhn Lam

# Overview
This document lays out implementation details for Project 5. In this project, we created an enrollment system application which processes enrollments for multiple universities. 

Here are some basic requirements for this project:

- The completed enrollment system must...
  - Load course/student/enrollment information from .txt files.
  - Provide functions for retrieving information about courses/students/enrollments. 
  - Provide functions for adding/dropping students from courses.
  - Handle enrollments for multiple universities.
  - Perform actions only upon the active/current university.

### Class Overview

Here is a brief overview of the four classes implemented in this project:

- `EnrollmentSystem`
  - Represents the enrollment system
  - Stores multiple `University` instances
  - Provides functions for retrieving information and adding/dropping students to/from courses for the active university
- `University`
  - Represents a single university in the enrollment system
  - Stores information about courses and students at the university
  - Provides functions for retrieving information and adding/dropping students to/from courses
- `Course`
  - Represents a single course in the university system
  - Stores course information (course name, course number, students enrolled)
  - Provides functions for retrieving information and adding/dropping students to/from this course
- `Student`
  - Represents a single student in a university system
  - Stores the student's information (last name, ID, enrolled courses)
  - Provides functions for retrieving information and adding/dropping courses

# Class Descriptions

This section describes extra implementation details for each class. Header files for all classes are provided.

- `EnrollmentSystem`
  - `EnrollmentSystem` is the class that the application uses to perform all actions. `EnrollmentSystem` must keep track of the active `University` to perform actions on.
  - `EnrollmentSystem` will receive sorted string vectors from some of  `University`'s `get...()` functions. This means that `EnrollmentSystem` must combine these strings together in an appropriate format and return it as a single string.
- `University`
  - Many of `University`'s functions have the same name as `EnrollmentSystem`'s, as `EnrollmentSystem` calls `University` to perform most of its actions, such as getting student/course info or adding/dropping classes. Keeping the names the same makes this more clear.
  - `University` performs all reading of .txt files and instantiates all `Student`/`Course` objects. Enrollment information (read from .txt files) is processed by calling `addCourse()` or `addStudent()`.
- `Course`
   - Stores a vector of `Student *` which represents the students that are enrolled in this course.
   - When adding/dropping students to/from courses, it's important to remember that the information needs be the same between the `Course` and the `Student` objects. This means that when calling `addStudent()`, either `Course` or `University` should also call the `Student`'s `addCourse()` function to ensure the course is in the `Student`'s `Course *` vector.
- `Student`
   - Stores a vector of `Course *` which represents the courses the student is enrolled in.
   - As stated in the `Course` section, the course information needs to be the same between the `Student` and the `Course` objects. Again, this means that if `addCourse()` were to be called, `Course::addStudent()` should also be called to ensure the information is the same. This can be done here in `Student` or in `University`.

# EnrollmentSystem Function Descriptions

This section describes how some of `EnrollmentSystem`'s member functions should work in the implementation.

- `readCourseList(const string &filename)`
  - `EnrollmentSystem` calls `University::readCourseList()`
  - `University` will load the file, instantiate all `Course` objects and store it in its `courses` map.
- `readEnrollmentInfo(const string &filename)`
  - `EnrollmentSystem` calls `University::readEnrollmentInfo()`
  - `University` will load the file and call either `Student::addCourse()` or `Course::addStudent()` (or both, if desired) to process enrollments.
- `addCourse(int studentID, const string &courseNumber)`
  - `EnrollmentSystem` calls `University::addCourse()`
  - `University` will either look through its `students` or `courses` vector and will call `addCourse()`/`addStudent()` (or both).
- `getEnrolledCourses(int studentID)`
  - `EnrollmentSystem` calls `University::getEnrolledCourses()`
  - `University` will retrieve the appropriate `Student` by looking at its `students` array. It then calls `Student::getEnrolledCourses()` to get the sorted vector of course strings.
  - `EnrollmentSystem` takes the sorted string vector, combines it together and returns it.
- `getClassListByLastName(const string &courseNumber)`
  - `EnrollmentSystem` calls `University::getClassListByLastName()`
  - `University` finds the appropriate `Course` object by looking at its `courses` map. It then calls `Course::getClassListByLastName()` to get a sorted string vector of enrolled students.
  - `EnrollmentSystem` takes the sorted string vector, combines it together and returns it.

clang-tidy:

/home/NETID/agrach/2023win342d-p5-agrach060/main.cpp:11:20: error: variable name 'es' is too short, expected at least 3 characters [readability-identifier-length,-warnings-as-errors]
  EnrollmentSystem es;
                   ^
This error cannot be fixed due to the original design of the test1() function.