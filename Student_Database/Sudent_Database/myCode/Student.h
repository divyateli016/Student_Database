/**
 * @file Student.h
 * @brief Defines the Student class for managing student records.
 *
 * This file contains the declaration of the Student class, which represents
 * a student with personal information, enrollments, and address details.
 *
 * @date Created on: Jan 5, 2025
 * @author Divya
 */

#include "Enrollment.h"
#include "Address.h"
#include <string>
#include <Poco/Data/Date.h>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <fstream>

#ifndef STUDENT_H_
#define STUDENT_H_
/**
 * @class Student
 * @brief Represents a student with personal details and course enrollments.
 *
 * The Student class maintains information about a student, including their
 * name, date of birth, enrollment records, and address.
 */
class Student
{
private:

	static unsigned int nextMatrikelNumber;/**< Static variable to track the
	 next available student ID. */
	unsigned int matrikelNumber;/**< Unique student identification number. */
	std::string firstName;/**< First name of the student. */
	std::string lastName;/**< Last name of the student. */
	Poco::Data::Date DateOfBirth;/**< Date of birth of the student. */
	std::vector<Enrollment> enrollments; /**< List of enrollments for the stud*/
	std::shared_ptr<Address> studentAddress;/**<Shared pointer is used for shared
	 ownership>**/

public:
	/**
	 * @brief Default constructor initializes an empty student record.
	 */
	Student();
	/**
	 * @brief Parameterized constructor initializes a student with given details.
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param DateOfBirth Date of birth of the student.
	 * @param studentAddress Shared pointer to the student's address.
	 */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date DateOfBirth,
			std::shared_ptr<Address> studentAddress);
	/**
	 * @brief Gets the first name of the student.
	 * @return A constant reference to the student's first name.
	 */
	const std::string& getFirstName() const;
	/**
	 * @brief Gets the last name of the student.
	 * @return A constant reference to the student's last name.
	 */
	const std::string& getlastName() const;
	/**
	 * @brief Gets the unique student ID.
	 * @return The matrikel number of the student.
	 */
	const unsigned int getmatrikelNumber() const;

	/**
	 * @brief Gets the date of birth of the student.
	 * @return A constant reference to the date of birth.
	 */
	const Poco::Data::Date& getDateOfbirth() const;
	/**
	 * @brief Gets the list of enrollments for the student.
	 * @return A constant reference to the vector of enrollments.
	 */
	const std::vector<Enrollment>& getenrollments() const;
	/**
	 * @brief Sets the first name of the student.
	 * @param firstName The new first name.
	 */
	void setFirstName(const std::string &firstName);
	/**
	 * @brief Sets the last name of the student.
	 * @param lastName The new last name.
	 */
	void setlastName(const std::string &lastName);
	/**
	 * @brief Sets the date of birth of the student.
	 * @param DateofBirth The new date of birth.
	 */
	void setdateOfBirth(const Poco::Data::Date &DateofBirth);
	/**
	 * @brief Sets the address of the student.
	 * @param studentAddress Shared pointer to the new address.
	 */
	void setAddress(const std::shared_ptr<Address> &studentAddress);

	/**
	 * @brief Updates the grade of an existing enrollment.
	 * @param courseKey The key of the course to update.
	 * @param grade The new grade.
	 */
	void updateenrollment(unsigned int courseKey, float grade);
	/**
	 * @brief Removes an enrollment from the student's records.
	 * @param courseKey The key of the course to remove.
	 */
	void removeEnrollment(unsigned int courseKey);
	/**
	 * @brief Adds a new enrollment for the student.
	 * @param enrollment The enrollment object to add.
	 */
	void addEnrollment(Enrollment enrollment);
	/**
	 * @brief Gets the address of the student.
	 * @return A shared pointer to the student's address.
	 */
	std::shared_ptr<Address> getaddress() const;
	/**
	 * @brief Prints student details.
	 */
	void print();
	/**
	 * @brief Writes student details to an output stream.
	 * @param out Output stream to write to.
	 */
	void write(std::ostream &out) const;
	/**
	 * @brief Reads student details from an input stream.
	 * @param in Input stream to read from.
	 */
	void read(std::istream &in);
	/**
	 * @brief Destructor for the Student class.
	 */
	virtual ~Student();
};

#endif /* STUDENT_H_ */
