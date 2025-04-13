/*
 * Course.cpp
 *
 *  Created on: Jan 8, 2025
 *      Author: divya
 */

#include "Course.h"

const std::map<unsigned char, std::string> Course::majorById =
{
{ 'E', "EMBEDDED" },
{ 'C', "COMMUNICATION" },
{ 'A', "AUTOMATION" },
{ 'P', "POWER" }

};

Course::Course(unsigned int courseKey, std::string title, std::string newmajor,
		float creditPoints) :
		courseKey(courseKey), title(title), creditPoints(creditPoints)
{
	setmajor(newmajor);

}

const std::string& Course::gettitle() const
{
	return this->title;
}

const unsigned int Course::getcourseKey() const
{
	return this->courseKey;
}

const std::string& Course::getMajor() const
{
	if (major != ' ')
	{
		return majorById.at(major);
	}
	static const std::string emptystring;
	return emptystring;

}

const float Course::getcreditPoints() const
{
	return this->creditPoints;
}

void Course::setmajor(std::string &newmajor)
{
	std::string upper;

	for (char c : newmajor)
	{
		upper += std::toupper(c); //Converts to the upper case.
	}

	for (const auto &majorpair : majorById)
	{
		if (majorpair.second == upper)
		{
			this->major = majorpair.first;
			return;
		}
	}
	this->major = ' ';

}

void Course::write(std::ostream &out) const
{
	std::string titleupper;
	for (char c : gettitle())
	{
		titleupper += toupper(c);
	}
	out << getcourseKey() << ";" << titleupper << ";" << getMajor() << ";"
			<< getcreditPoints() << ";";

}

Course::~Course()
{
	// TODO Auto-generated destructor stub
}

void Course::read(std::istream &in)
{
	std::string courseKey, title, major, creditpoints;

	getline(in, courseKey, ';');
	getline(in, title, ';');
	getline(in, major, ';');
	getline(in, creditpoints, ';');

	this->courseKey = stoi(courseKey);
	this->title = title;

	for (auto &pair : majorById)
	{
		if (pair.second == major)
		{
			this->major = pair.first;
		}
	}

	this->creditPoints = stof(creditpoints);

}

Course::Course()
{
}
