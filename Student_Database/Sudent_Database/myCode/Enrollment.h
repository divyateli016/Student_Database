/**
 * @file Enrollment.h
 * @brief Defines the Enrollment class for managing course enrollments.
 *
 * This file contains the declaration of the Enrollment class, which represents
 * a student's enrollment in a course. It includes details such as the semester,
 * the course enrolled in, and the grade received.
 *
 * @date Created on: Jan 5, 2025
 * @author Divya
 */
#include <string>
#include "Course.h"

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

/**
 * @class Enrollment
 * @brief Represents a student's enrollment in a course.
 *
 * The Enrollment class encapsulates information about a student's enrollment,
 * including the semester, the course they are enrolled in, the grade received.
 */

class Enrollment
{
private:
	float grade;
	std::string semester;
	const Course *course;

public:

	/**
	 * @brief Default constructor initializes an empty enrollment.
	 */
	Enrollment();
	/**
	 * @brief Parameterized constructor initializes enrollment with given values.
	 * @param semester The semester in which the course is taken.
	 * @param course Pointer to the enrolled course.
	 */
	Enrollment(std::string semeseter, const Course *course);
	/**
	 * @brief Gets the grade received for the course.
	 * @return The grade as a floating-point value.
	 */
	const float getgrade() const;
	/**
	 * @brief Gets the semester of enrollment.
	 * @return A constant reference to the semester string.
	 */
	const std::string& getsemester() const;

	/**
	 * @brief Gets the enrolled course.
	 * @return A pointer to the enrolled course.
	 */
	const Course* getcourse() const;

	/**
	 * @brief Sets the grade for the enrollment.
	 * @param grade The new grade value.
	 */
	void setgrade(float grade);

	/**
	 * @brief Writes enrollment details to an output stream.
	 * @param out Output stream to write to.
	 */
	void write(std::ostream &out) const;
	/**
	 * @brief Reads enrollment details from an input stream.
	 * @param in Input stream to read from.
	 */
	void read(std::istream &in);
	/**
	 * @brief Destructor for the Enrollment class.
	 */
	virtual ~Enrollment();
};

#endif /* ENROLLMENT_H_ */
