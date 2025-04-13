/*
 * WeeklyCourse.cpp
 *
 *  Created on: Jan 14, 2025
 *      Author: divya
 */

#include "WeeklyCourse.h"
#include <iostream>

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string newmajor, float creditpoints,
		Poco::DateTime::DaysOfWeek daysOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course(courseKey, title, newmajor, creditpoints), dayOfWeek(daysOfWeek),
		startTime(startTime), endTime(endTime)
{
}

const Poco::Data::Time& WeeklyCourse::getstartTime() const
{
	return this->startTime;
}

const Poco::Data::Time& WeeklyCourse::getendTime() const
{
	return this->endTime;
}

const Poco::DateTime::DaysOfWeek& WeeklyCourse::getdaysofweek() const
{
	return this->dayOfWeek;
}

void WeeklyCourse::write(std::ostream &out) const
{
	Poco::DateTime start(1, 1, 1, getstartTime().hour(),
			getstartTime().minute());

	Poco::DateTime end(1, 1, 1, getendTime().hour(), getendTime().minute());

	//Formating the date how we want it ti be printed
	std::string starttime = Poco::DateTimeFormatter::format(start, "%H:%M");
	std::string endtime = Poco::DateTimeFormatter::format(end, "%H:%M");

	out << "W" << ";";
	Course::write(out); //Calling this function separately where calling
	//this in stream gives the error as this function does not return anything
	out << getdaysofweek() << ";" << starttime << ";" << endtime;

}

void WeeklyCourse::read(std::istream &in)
{
	std::string DayofWeek, startHour, startMin, EndHour, EndMin;
	Course::read(in);

	getline(in, DayofWeek, ';');
	getline(in, startHour, ':');
	getline(in, startMin, ';');
	getline(in, EndHour, ':');
	getline(in, EndMin, '\n');

	int dayindex = stoi(DayofWeek);
	Poco::DateTime::DaysOfWeek day_of_week =
			static_cast<Poco::DateTime::DaysOfWeek>(dayindex);

	Poco::Data::Time startTime(stoi(startHour), stoi(startMin), 0);
	Poco::Data::Time endTime(stoi(EndHour), stoi(EndMin), 0);

	this->dayOfWeek = day_of_week;
	this->startTime = startTime;
	this->endTime = endTime;
}

WeeklyCourse::~WeeklyCourse()
{
	// TODO Auto-generated destructor stub
}

WeeklyCourse::WeeklyCourse()
{
}
