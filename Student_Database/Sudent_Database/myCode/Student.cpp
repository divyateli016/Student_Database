/*
 * Student.cpp
 *
 *  Created on: Jan 5, 2025
 *      Author: divya
 */

#include "Student.h"
#include <iostream>
#include <Poco/Data/Date.h>
using namespace std;

unsigned int Student::nextMatrikelNumber = 10000;

Student::Student()
{
}
Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date DateOfBirth, std::shared_ptr<Address> studentAddress) :
		firstName(firstName), lastName(lastName), DateOfBirth(DateOfBirth),
		studentAddress(studentAddress)
{
	matrikelNumber = nextMatrikelNumber++;
}

const std::string& Student::getFirstName() const
{
	return firstName;
}

const std::string& Student::getlastName() const
{
	return lastName;
}

const unsigned int Student::getmatrikelNumber() const
{
	return matrikelNumber;
}

const Poco::Data::Date& Student::getDateOfbirth() const
{
	return DateOfBirth;
}

const std::vector<Enrollment>& Student::getenrollments() const
{
	return enrollments;
}

void Student::setFirstName(const std::string &firstName) //Pass by reference
{
	this->firstName = firstName;
}

std::shared_ptr<Address> Student::getaddress() const
{
	return studentAddress;
}

void Student::setlastName(const std::string &lastName) //Pass by refernce
{
	this->lastName = lastName;
}

void Student::setdateOfBirth(const Poco::Data::Date &DateofBirth)
{
	this->DateOfBirth = DateofBirth;
}

void Student::setAddress(const std::shared_ptr<Address> &studentAddress)
{
	this->studentAddress = studentAddress;
}
void Student::print()
{
	std::cout << "Student Details are" << firstName << ":" << lastName << ":"
			<< DateOfBirth.day() << "/" << DateOfBirth.month() << "/"
			<< DateOfBirth.year() << ":" << matrikelNumber << ":"
			<< studentAddress->getcityName() << std::endl;
}

void Student::updateenrollment(unsigned int courseKey, float grade)
{
	for (auto &enrollment : enrollments)
	{
		if (enrollment.getcourse()->getcourseKey() == courseKey)
		{
			enrollment.setgrade(grade);
		}
	}
}

void Student::removeEnrollment(unsigned int courseKey)
{
	for (auto itenrollment = enrollments.begin();
			itenrollment != enrollments.end();)
	{
		if (itenrollment->getcourse()->getcourseKey() == courseKey)
		{
			itenrollment = enrollments.erase(itenrollment);
		}
		else
		{
			++itenrollment;
		}
	}
}

void Student::addEnrollment(Enrollment enrollment)
{
	enrollments.push_back(enrollment);
}

void Student::write(std::ostream &out) const
{
	ostringstream oss;

	oss << setw(2) << setfill('0') << getDateOfbirth().day() << "." << setw(2)
			<< setfill('0') << getDateOfbirth().month() << "."
			<< getDateOfbirth().year();

	out << getmatrikelNumber() << ";" << getFirstName() << ";" << getlastName()
			<< ";" << oss.str();

	getaddress()->write(out); //Printing address of the student

}

void Student::read(std::istream &in)
{
	std::string firstname, lastname, matrikelnumber;
	std::string day, month, year;
	std::string street, postalCode, cityName, additionalInfo;

	getline(in, matrikelnumber, ';');

	getline(in, firstname, ';');
	getline(in, lastname, ';');

	getline(in, day, '.');
	getline(in, month, '.');
	getline(in, year, ';');

	getline(in, street, ';');
	getline(in, postalCode, ';');
	getline(in, cityName, ';');
	getline(in, additionalInfo, '\n');

	Poco::Data::Date dateof_Birth(stoi(year), stoi(month), stoi(day));

	unsigned short postal_Code = (unsigned short) stoi(postalCode);
	shared_ptr<Address> studaddress = std::make_shared<Address>(street,
			postal_Code, cityName, additionalInfo);

	this->firstName = firstname;
	this->lastName = lastname;
	this->DateOfBirth = dateof_Birth;
	this->setAddress(studaddress);
}

Student::~Student()
{
	// TODO Auto-generated destructor stub
}

