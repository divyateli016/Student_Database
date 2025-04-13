/**
 * @file SimpleUI.h
 * @brief Defines the SimpleUI class for user interaction with the student database.
 *
 * This file contains the declaration of the SimpleUI class, which provides
 * a command-line interface for managing student records, courses, and enrollments.
 *
 * @date Created on: Jan 5, 2025
 * @author Divya
 */

#include "StudentDb.h"
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <Poco/Data/Date.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_
/**
 * @class SimpleUI
 * @brief Provides a command-line user interface for student database management.
 *
 * The SimpleUI class allows users to interact with the student database by
 * adding courses, students, and enrollments, listing available courses,
 * searching for students, and updating student records.
 */
class SimpleUI
{
private:
	StudentDb &db;/**< Reference to the student database. */
	std::map<int, std::unique_ptr<const Course>> courses;/**< Map of course IDs
	                                                      to course objects. */
public:
	/**
	 * @brief Constructs a SimpleUI object with a reference to the student
	 * database.
	 * @param DB Reference to an instance of StudentDb.
	 */
	SimpleUI(StudentDb &DB);

	/**
	 * @brief Runs the user interface, providing menu options.
	 */
	void run();
	/**
	 * @brief Adds a new course to the system.
	 */
	void addCourse();
	/**
	 * @brief Lists all available courses.
	 */
	void ListCourse();
	/**
	 * @brief Adds a new student to the database.
	 */
	void addStudent();
	/**
	 * @brief Enrolls a student in a course.
	 */
	void addEnrollment();
	/**
	 * @brief Prints student details.
	 */
	void printStudent();
	/**
	 * @brief Searches for a student by name or ID.
	 */
	void searchStudent();
	/**
	 * @brief Updates student information in the database.
	 */
	void updateStudent();
	/**
	 * @brief Destructor for the SimpleUI class.
	 */
	virtual ~SimpleUI();
};

#endif /* SIMPLEUI_H_ */
