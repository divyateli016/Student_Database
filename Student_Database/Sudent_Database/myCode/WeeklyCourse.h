/**
 * @file WeeklyCourse.h
 * @brief Declaration of the WeeklyCourse class.
 *
 * This file contains the declaration of the WeeklyCourse class,
 * which represents a course that occurs on a weekly basis.
 *
 * @author Divya
 * @date January 14, 2025
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include <memory>

/**
 * @class WeeklyCourse
 * @brief A derived class representing a weekly recurring course.
 */
class WeeklyCourse: public Course
{
private:
	Poco::DateTime::DaysOfWeek dayOfWeek; /**< The day of the week the course
	 occurs. */
	Poco::Data::Time startTime; /**<start time of the Weekly course>*/
	Poco::Data::Time endTime; /*<endtime of the Weekly course>*/

public:
	/**
	 * @brief Default constructor.
	 */
	WeeklyCourse();
	/**
	 * @brief Parameterized constructor.
	 * @param courseKey Unique identifier for the course.
	 * @param title The title of the course.
	 * @param newmajor The major field of study for the course.
	 * @param creditpoints The number of credit points assigned to the course.
	 * @param dayOfWeek The day of the week the course is scheduled.
	 * @param startTime The start time of the course.
	 * @param endTime The end time of the course.
	 */
	WeeklyCourse(unsigned int courseKey, std::string title,
			std::string newmajor, float creditpoints,
			Poco::DateTime::DaysOfWeek, Poco::Data::Time startTime,
			Poco::Data::Time endTime);
	/**
	 * @brief Gets the start time of the course.
	 * @return The start time.
	 */
	const Poco::Data::Time& getstartTime() const;
	/**
	 * @brief Gets the end time of the course.
	 * @return The end time.
	 */

	const Poco::Data::Time& getendTime() const;
	/**
	 * @brief Gets the day of the week the course occurs.
	 * @return The day of the week.
	 */

	const Poco::DateTime::DaysOfWeek& getdaysofweek() const;

	/**
	 * @brief Writes the course details to an output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream &out) const override;
	/**
	 * @brief Reads the course details from an input stream.
	 * @param in The input stream to read from.
	 */
	void read(std::istream &in);
	/**
	 * @brief Destructor.
	 */
	virtual ~WeeklyCourse();
};

#endif /* WEEKLYCOURSE_H_ */
