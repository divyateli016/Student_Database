/*
 * Enrollment.cpp
 *
 *  Created on: Jan 5, 2025
 *      Author: divya
 */

#include "Enrollment.h"
#include <string>

Enrollment::Enrollment(std::string semeseter,const Course *course):
		semester(semeseter),course(course)
{
	this->grade = 0;

}

const float Enrollment::getgrade() const
{
	return this->grade;
}

const std::string& Enrollment::getsemester() const
{
	return this->semester;
}

const Course* Enrollment::getcourse() const
{
	return this->course;
}

void Enrollment::setgrade(float grade)
{
	this->grade = grade;

}

void Enrollment::write(std::ostream &out) const
{
	out << getcourse()->getcourseKey() << ";" << getsemester();
	if (getgrade() > 0)
	{
		out << ";"<<getgrade();
	}

}

void Enrollment::read(std::istream &in)
{
	std::string Semester;
	std::string gradeptr;

	getline(in,Semester,';');

	getline(in,gradeptr,'\n');

	this->semester = Semester;
	setgrade(stof(gradeptr));

}

Enrollment::Enrollment()
{
}

Enrollment::~Enrollment()
{
	// TODO Auto-generated destructor stub
}

