/*
 * BlockCourse.cpp
 *
 *  Created on: Jan 14, 2025
 *      Author: divya
 */

#include "BlockCourse.h"

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string newmajor, float creditpoints, Poco::Data::Time startTime,
		Poco::Data::Time endTime, Poco::Data::Date startDate,
		Poco::Data::Date endDate) :
		Course(courseKey, title, newmajor, creditpoints), startTime(startTime),
		endTime(endTime), startDate(startDate), endDate(endDate)

{
}

const Poco::Data::Time& BlockCourse::getstartTime() const
{
	return this->startTime;
}

const Poco::Data::Date& BlockCourse::getstartDate() const
{
	return this->startDate;
}

const Poco::Data::Time& BlockCourse::getendTime() const
{
	return this->endTime;
}

const Poco::Data::Date& BlockCourse::getendDate() const
{
	return this->endDate;
}

void BlockCourse::write(std::ostream &out) const
{
	std::ostringstream oss1;
	std::ostringstream oss2;

	/**Format the day and month of the date as two digits **/
	oss1 << std::setw(2) << std::setfill('0') << getstartDate().day() << "."
			<< std::setw(2) << std::setfill('0') << getstartDate().month()
			<< '.' << getstartDate().year();

	oss2 << std::setw(2) << std::setfill('0') << getendDate().day() << "."
			<< std::setw(2) << std::setfill('0') << getendDate().month() << "."
			<< getendDate().year();

	Poco::DateTime start(1, 1, 1, getstartTime().hour(),
			getstartTime().minute());
	Poco::DateTime end(1, 1, 1, getendTime().hour(), getendTime().minute());

	std::string starttime = Poco::DateTimeFormatter::format(start, "%H:%M");
	std::string endtime = Poco::DateTimeFormatter::format(end, "%H:%M");

	out << "B" << ";";
	Course::write(out);
	out << oss1.str() << ";" << oss2.str() << ";" << starttime << ";"
			<< endtime;

}

void BlockCourse::read(std::istream &in)
{
	Course::read(in);
	std::string startimeHour, startimeminute, endtimeHour, endtimeminute,
			startdateDay, startdateMonth, startdateYear, enddateDay,
			enddateMonth, enddateYear;

	getline(in, startdateDay, '.');
	getline(in, startdateMonth, '.');
	getline(in, startdateYear, ';');

	getline(in, enddateDay, '.');
	getline(in, enddateMonth, '.');
	getline(in, enddateYear, ';');

	getline(in, startimeHour, ':');
	getline(in, startimeminute, ';');
	getline(in, endtimeHour, ':');
	getline(in, endtimeminute, '\n');

	Poco::Data::Date startdate(stoi(startdateYear), stoi(startdateMonth),
			stoi(startdateDay));
	Poco::Data::Date enddate(stoi(enddateYear), stoi(enddateMonth),
			stoi(enddateDay));

	Poco::Data::Time starttime(stoi(startimeHour), stoi(startimeminute), 0);
	Poco::Data::Time endtime(stoi(endtimeHour), stoi(endtimeminute), 0);

	this->startDate = startdate;
	this->endDate = enddate;
	this->startTime = starttime;
	this->endTime = endtime;
}

BlockCourse::BlockCourse()
{
}

BlockCourse::~BlockCourse()
{
	// TODO Auto-generated destructor stub
}

