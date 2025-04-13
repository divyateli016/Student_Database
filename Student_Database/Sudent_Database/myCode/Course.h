/**
 * @file Course.h
 * @brief Defines the Course class for handling course-related information.
 *
 * This file contains the declaration of the Course class, which represents
 * a general academic course. It includes attributes for a course key, title,
 * major, and credit points, along with methods for accessing and modifying
 * course details.
 *
 * @date Created on: Jan 8, 2025
 * @author Divya
 */

#include<string>
#include<iostream>
#include <map>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <Poco/DateTime.h>
#include <iomanip>

#ifndef COURSE_H_
#define COURSE_H_

/**
 * @class Course
 * @brief Represents a general academic course.
 *
 * The Course class encapsulates details of an academic course, including
 * its unique identifier, title, major, and credit points.
 */
class Course
{
private:
	static const std::map<unsigned char, std::string> majorById;/**< Mapping of
	 major IDs to their names. */
	unsigned int courseKey; /**< Unique identifier for the course. */
	std::string title; /**< Title of the course. */
	unsigned char major; /**< Major ID associated with the course. */
	float creditPoints; /**< Number of credit points for the course. */

public:
	/**
	 * @brief Default constructor initializes an empty course.
	 */
	Course();
	/**
	 * @brief Parameterized constructor initializes a Course with specified details.
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param newmajor Name of the major or department.
	 * @param creditPoints Credit points assigned to the course.
	 */
	Course(unsigned int courseKey, std::string title, std::string newmajor,
			float creditPoints);
	/**
	 * @brief Gets the title of the course.
	 * @return A constant reference to the course title string.
	 */
	const std::string& gettitle() const;
	/**
	 * @brief Gets the course key.
	 * @return The unique identifier of the course.
	 */
	const unsigned int getcourseKey() const;
	/**
	 * @brief Gets the major of the course.
	 * @return A constant reference to the major string.
	 */
	const std::string& getMajor() const;
	/**
	 * @brief Gets the credit points for the course.
	 * @return The number of credit points assigned to the course.
	 */
	const float getcreditPoints() const;
	/**
	 * @brief Sets the major of the course.
	 * @param newmajor Reference to a string representing the new major.
	 */
	void setmajor(std::string &newmajor);
	/**
	 * @brief Writes course details to an output stream.
	 * @param out Output stream to write to.
	 */
	virtual void write(std::ostream &out) const;
	/**
	 * @brief Reads course details from an input stream.
	 * @param in Input stream to read from.
	 */
	void read(std::istream &in);
	/**
	 * @brief Destructor for the Course class.
	 */
	virtual ~Course();
};

#endif /* COURSE_H_ */
