/**
 * @file StudentDb.h
 * @brief Defines the StudentDb class for managing student records and courses.
 *
 * This file contains the declaration of the StudentDb class, which provides
 * functionality for managing students, courses, and enrollments.
 *
 * @date Created on: Jan 5, 2025
 * @author Divya
 */
#include "Student.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"
#include <map>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <fstream>
#include <boost/json.hpp>

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

/**
 * @class StudentDb
 * @brief Manages student records, courses, and enrollments.
 *
 * The StudentDb class provides functionalities to add, update, and manage
 * student data and course enrollments, using unique pointers for single
 * ownership of courses.
 */
class StudentDb
{
private:
	std::map<int, Student> students;/**< Map storing students by ID. */
	std::map<int, std::unique_ptr<const Course>> courses; /**Uniq pointer to the
	 course Class deals with the single ownership at given point of time*/

public:
	/**
	 * @brief Default constructor for StudentDb.
	 */
	StudentDb();
	/**
	 * @brief Adds a new student to the database.
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param dateOfBirth Date of birth of the student.
	 * @param street Street address of the student.
	 * @param postalCode Postal code of the student's address.
	 * @param cityName City name of the student's address.
	 * @param additionalInfo Additional address information.
	 */
	void addStudent(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::string street,
			unsigned short postalCode, std::string cityName,
			std::string additionalInfo);
	/**
	 * @brief Gets the list of students.
	 * @return A constant reference to the student map.
	 */
	const std::map<int, Student>& getstudents() const;
	/**
	 * @brief Updates student information.
	 * @param MatrikelNumber Student ID.
	 * @param choice Selection for update type.
	 * @param firstName New first name.
	 * @param lastName New last name.
	 * @param dateOfBirth New date of birth.
	 */
	void updateStudentInfo(unsigned int MatrikelNumber, unsigned int choice,
			std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth);
	/**
	 * @brief Updates the student's address.
	 * @param MatrikelNumber Student ID.
	 * @param street New street address.
	 * @param postalCode New postal code.
	 * @param cityName New city name.
	 * @param additionalInfo Additional address info.
	 */
	void updateAddress(unsigned int MatrikelNumber, std::string street,
			unsigned short postalCode, std::string cityName,
			std::string additionalInfo);
	/**
	 * @brief Updates enrollment information.
	 * @param MatrikelNumber Student ID.
	 * @param choice Update selection.
	 * @param courseKey Course ID.
	 * @param grade New grade.
	 */
	void updatEnrollmentinfo(unsigned int MatrikelNumber, unsigned int choice,
			int courseKey, float grade);
	/**
	 * @brief Adds an enrollment to a student.
	 * @param matrikelNumber Student ID.
	 * @param courseKey Course ID.
	 * @param semester Semester of enrollment.
	 */
	void addEnrollment(unsigned int matrikelNumber, unsigned int courseKey,
			std::string semester);
	/**
	 * @brief Gets the list of courses.
	 * @return A constant reference to the course map.
	 */
	const std::map<int, std::unique_ptr<const Course>>& getcourses() const;
	/**
	 * @brief Adds a weekly course.
	 * @param courseKey Course ID.
	 * @param title Course title.
	 * @param major Course major.
	 * @param creditpoints Credit points of the course.
	 * @param daysOfWeek Days the course is held.
	 * @param startTime Start time of the course.
	 * @param endTime End time of the course.
	 */
	void addweeklyCourse(unsigned int courseKey, std::string title,
			std::string major, float creditpoints,
			Poco::DateTime::DaysOfWeek daysOfWeek, Poco::Data::Time startTime,
			Poco::Data::Time endTime);
	/**
	 * @brief Adds a block course.
	 * @param courseKey Course ID.
	 * @param title Course title.
	 * @param major Course major.
	 * @param creditpoints Credit points of the course.
	 * @param startDate Start date of the course.
	 * @param endDate End date of the course.
	 * @param startTime Start time of the course.
	 * @param endTime End time of the course.
	 */
	void addblockCourse(unsigned int courseKey, std::string title,
			std::string major, float creditpoints, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime);
	/**
	 * @brief Writes student database details to an output stream.
	 * @param out Output stream.
	 */
	void write(std::ostream &out) const;

	/**
	 * @brief Reads student database details from an input stream.
	 * @param in Input stream.
	 */
	void read(std::istream &in);
	/**
	 * @brief Fetches data from a stream.
	 * @param datacount Number of data entries to fetch.
	 */
	void fetchdatafromstream(unsigned int datacount);
	/**
	 * @brief Parses JSON data to extract student information.
	 * @param jsonString JSON formatted string.
	 */
	void parseJsonData(std::string jsonString);
	/**
	 * @brief Checks validity of student data.
	 * @param firstName First name.
	 * @param lastName Last name.
	 * @param street Street address.
	 * @param city City name.
	 * @param additionalInfo Additional information.
	 * @param postCodeStr Postal code as string.
	 * @return True if data is valid, false otherwise.
	 */
	bool dataCheck(std::string firstName, std::string lastName,
			std::string street, std::string city, std::string additionalInfo,
			std::string postCodeStr);
	/**
	 * @brief Destructor for the StudentDb class.
	 */
	virtual ~StudentDb();
};

#endif /* STUDENTDB_H_ */
