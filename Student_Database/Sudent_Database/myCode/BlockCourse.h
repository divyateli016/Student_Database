/**
 * @file BlockCourse.h
 * @brief Defines the BlockCourse class, which represents a time-blocked course.
 *
 * This file contains the declaration of the BlockCourse class, which extends
 * the Course class and introduces additional attributes for start and end times
 * and dates. It includes methods for retrieving course details, as well as
 * reading and writing course data.
 *
 * @date Created on: Jan 14, 2025
 * @author Divya
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"
#include <sstream>
#include <iomanip>
#include <memory>


/**
 * @class BlockCourse
 * @brief Represents a course scheduled within a specific time block.
 *
 * The BlockCourse class extends the Course class by adding attributes for
 * defining the start and end times, as well as start and end dates.
 */
class BlockCourse: public Course
{
private:
	Poco::Data::Time startTime; /**<start time of the blocked courese.*/
	Poco::Data::Time endTime; /**< End time of the blocked course. */
	Poco::Data::Date startDate; /**< Start date of the blocked course. */
	Poco::Data::Date endDate; /**< End date of the blocked course. */

public:
	/**
	 * @brief Default constructor initializes an empty BlockCourse.
	 */
	BlockCourse();

	/**
	 * @brief Parameterized constructor initializes a BlockCourse with
	 * specified details.
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param newmajor Major or department the course belongs to.
	 * @param creditpoints Credit points assigned to the course.
	 * @param startTime The start time of the course.
	 * @param endTime The end time of the course.
	 * @param startDate The start date of the course.
	 * @param endDate The end date of the course.
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string newmajor,
			float creditpoints, Poco::Data::Time startTime,
			Poco::Data::Time endTime, Poco::Data::Date startDate,
			Poco::Data::Date endDate);

	/**
	 * @brief Gets the start time of the course.
	 * @return A constant reference to the start time.
	 */
	const Poco::Data::Time& getstartTime() const;
	/**
	 * @brief Gets the start date of the course.
	 * @return A constant reference to the start date.
	 */
	const Poco::Data::Date& getstartDate() const;
	/**
	 * @brief Gets the end time of the course.
	 * @return A constant reference to the end time.
	 */
	const Poco::Data::Time& getendTime() const;

	/**
	 * @brief Gets the end date of the course.
	 * @return A constant reference to the end date.
	 */
	const Poco::Data::Date& getendDate() const;
	/**
	 * @brief Writes BlockCourse details to an output stream.
	 * @param out Output stream to write to.
	 */
	void write(std::ostream &out) const override;

	/**
	 * @brief Reads BlockCourse details from an input stream.
	 * @param in Input stream to read from.
	 */
	void read(std::istream &in);

	/**
	 * @brief Destructor for the BlockCourse class.
	 */
	virtual ~BlockCourse();
};

#endif /* BLOCKCOURSE_H_ */
