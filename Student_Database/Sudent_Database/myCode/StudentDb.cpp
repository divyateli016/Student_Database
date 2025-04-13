/*
 * StudentDb.cpp
 *
 *  Created on: Jan 5, 2025
 *      Author: divya
 */

#include "StudentDb.h"

#include <boost/json/src.hpp>

using namespace std;

StudentDb::StudentDb()
{
	// TODO Auto-generated constructor stub

}

void StudentDb::addStudent(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo)
{
	std::shared_ptr<Address> studentAddress = std::make_shared<Address>(street,
			postalCode, cityName, additionalInfo);

	//Adding student means we are creating the new student in student data base
	Student newStudent(firstName, lastName, dateOfBirth, studentAddress);

	students.insert(
			std::make_pair(newStudent.getmatrikelNumber(), move(newStudent)));
}

const std::map<int, Student>& StudentDb::getstudents() const
{
	return this->students;
}

void StudentDb::updateStudentInfo(unsigned int MatrikelNumber,
		unsigned int choice, std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth)
{
	switch (choice)
	{
	case 1: //Update first name
	{
		this->students.at(MatrikelNumber).setFirstName(firstName);
	}
		break;
	case 2:
	{
		this->students.at(MatrikelNumber).setlastName(lastName);
	}
		break;
	case 3:
	{
		this->students.at(MatrikelNumber).setdateOfBirth(dateOfBirth);
	}
		break;
	default:
		break;
	}
}

void StudentDb::updateAddress(unsigned int MatrikelNumber, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo)
{
	std::shared_ptr<Address> address = std::make_shared<Address>(street,
			postalCode, cityName, additionalInfo);
	this->students.at(MatrikelNumber).setAddress(address);

}

void StudentDb::updatEnrollmentinfo(unsigned int MatrikelNumber,
		unsigned int choice, int courseKey, float grade)
{
	switch (choice)
	{
	case 1: // Remove enrollment
	{
		this->students.at(MatrikelNumber).removeEnrollment(courseKey);

	}
		break;
	case 2: //add grades

	{
		this->students.at(MatrikelNumber).updateenrollment(courseKey, grade);

	}
		break;
	}
}

StudentDb::~StudentDb()
{
	// TODO Auto-generated destructor stub
}

void StudentDb::addEnrollment(unsigned int matrikelNumber,
		unsigned int courseKey, std::string semester)
{
	auto &enrollcourse = this->getcourses().at(courseKey);

	/**Enrollment constructor takes the pointer to the Course object as the para
	 * meter hence to get the raw pointer .get is used
	 */
	Enrollment newEnrollment(semester, enrollcourse.get());

	this->students.at(matrikelNumber).addEnrollment(newEnrollment);
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getcourses()const
{
	return this->courses;
}

void StudentDb::addweeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditpoints,
		Poco::DateTime::DaysOfWeek daysOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime)
{
	std::unique_ptr<WeeklyCourse> newcourse = std::make_unique<WeeklyCourse>(
			courseKey, title, major, creditpoints, daysOfWeek, startTime,
			endTime);

	this->courses.insert(make_pair(courseKey, move(newcourse)));

}

void StudentDb::addblockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditpoints, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime)
{
	std::unique_ptr<BlockCourse> newcourse = std::make_unique<BlockCourse>(
			courseKey, title, major, creditpoints, startTime, endTime,
			startDate, endDate);

	this->courses.insert(make_pair(courseKey, move(newcourse)));

}

void StudentDb::write(std::ostream &out) const
{
	if (courses.size() > 0)
	{
		out << this->courses.size() << std::endl;

	}
	for (const auto &entry : this->courses)
	{
		const Course *course = entry.second.get();
		course->write(out);
		out << endl;
	}
	if (this->students.size())
	{
		out << this->students.size() << endl;
	}
	unsigned int totalenrollments = 0;
	for (const auto &student : this->students)
	{
		//Printing the student data
		student.second.write(out);

		//Getting the number of enrollments of the each student
		totalenrollments = totalenrollments
				+ student.second.getenrollments().size();
		out << endl;
	}
	if (totalenrollments > 0)
	{
		out << totalenrollments << endl;
	}
	for (const auto &student : this->students)
	{
		for (const auto &enrollment : student.second.getenrollments())
		{
			out << student.second.getmatrikelNumber() << ";";
			enrollment.write(out);
			out << endl;
		}
	}

}
void StudentDb::read(std::istream &in)
{
	std::string data;
	getline(in, data);

	int count = stoi(data);

	for (int i = 0; i < count; i++)
	{
		string courseType;
		getline(in, courseType, ';');

		if (courseType == "W")
		{
			WeeklyCourse wCourse;
			wCourse.read(in);

			this->addweeklyCourse(wCourse.getcourseKey(), wCourse.gettitle(),
					wCourse.getMajor(), wCourse.getcreditPoints(),
					wCourse.getdaysofweek(), wCourse.getstartTime(),
					wCourse.getendTime());
		}
		if (courseType == "B")
		{
			BlockCourse bCourse;
			bCourse.read(in);

			this->addblockCourse(bCourse.getcourseKey(), bCourse.gettitle(),
					bCourse.getMajor(), bCourse.getcreditPoints(),
					bCourse.getstartDate(), bCourse.getendDate(),
					bCourse.getstartTime(), bCourse.getendTime());
		}
	}
	getline(in, data);
	int studentnumber = stoi(data);

	for (int i = 0; i < studentnumber; i++)
	{
		std::string studentdata;
		Student st;
		st.read(in);
		this->addStudent(st.getFirstName(), st.getlastName(),
				st.getDateOfbirth(), st.getaddress().get()->getstreet(),
				st.getaddress().get()->getpostalCode(),
				st.getaddress().get()->getcityName(),
				st.getaddress().get()->getadditionalInfo());

	}
	getline(in, data);
	int enrollcnt = stoi(data);

	getline(in, data, ';');
	unsigned int matrikel = stoi(data);

	std::string course;
	getline(in, course, ';');
	unsigned int courseKey = stoi(course);

	std::string semester;
	getline(in, semester, ';');

	std::string grade;
	getline(in, grade, '\n');

	for (int i = 0; i < enrollcnt; i++)
	{

		Enrollment enroll;

		addEnrollment(matrikel, courseKey, semester);
		students.at(matrikel).updateenrollment(courseKey, stof(grade));

	}

}

void StudentDb::fetchdatafromstream(unsigned int datacount)
{
	std::string hostname = "www.hhs.users.h-da.cloud";
	std::string port = "4242";

	boost::asio::ip::tcp::iostream stream;
	stream.connect(hostname, port);	//Conncécting to the server
	if (!stream)
	{
		cerr << "Connection is uncussefull" << stream.error().message() << endl;
	}
	for (unsigned int idx = 0; idx < datacount; idx++)
	{
		stream << "generate" << endl;
		stream.flush();

		string line1, line2, line3;

		getline(stream, line1);
		getline(stream, line2);
		this->parseJsonData(line2);
		getline(stream, line3);
	}
	stream << "quit" << endl;
	stream.flush();
}

void StudentDb::parseJsonData(std::string jsonString)
{
	boost::json::value parsedData = boost::json::parse(jsonString);


	string firstName =
			parsedData.at("name").at("firstName").as_string().c_str();
	string lastName = parsedData.at("name").at("lastName").as_string().c_str();
	int year = parsedData.at("dateOfBirth").at("year").as_int64() + 1900;
	int month = parsedData.at("dateOfBirth").at("month").as_int64() + 1;
	int day = parsedData.at("dateOfBirth").at("date").as_int64();

	string street = parsedData.at("location").at("street").as_string().c_str();
	string postCodeStr =
			parsedData.at("location").at("postCode").as_string().c_str();
	string city = parsedData.at("location").at("city").as_string().c_str();
	string additionalInfo =
			parsedData.at("location").at("state").as_string().c_str();

	Poco::Data::Date dateOfBirth(year, month, day);

	if (dataCheck(firstName, lastName, street, city, additionalInfo,
			postCodeStr))
	{
		int postCode = stoi(postCodeStr);
		shared_ptr<Address> address = make_shared<Address>(street, postCode,
				city, additionalInfo);
		Student addStudent(firstName, lastName, dateOfBirth, address);
this->students.insert(make_pair(addStudent.getmatrikelNumber(), addStudent));
	}
}

bool StudentDb::dataCheck(std::string firstName, std::string lastName,
		std::string street, std::string city, std::string additionalInfo,
		std::string postCodeStr)
{
	bool postCodeCheck =
			all_of(postCodeStr.begin(), postCodeStr.end(), ::isdigit) ?
					true : false;

	bool streetCheck =
			all_of(street.begin(), street.end(), ::isprint) ? true : false;
	bool cityCheck = all_of(city.begin(), city.end(), ::isprint) ? true : false;
	bool additionaInfoCheck =
			all_of(additionalInfo.begin(), additionalInfo.end(), ::isprint) ?
					true : false;

	bool firstNameCheck =
			all_of(firstName.begin(), firstName.end(), ::isalpha) ?
					true : false;
	bool lastNameCheck =
			all_of(lastName.begin(), lastName.end(), ::isalpha) ? true : false;

	if (postCodeCheck && streetCheck && additionaInfoCheck && firstNameCheck
			&& lastNameCheck && cityCheck)
	{
		return true;
	}
	else
	{
		return false;
	}
}
