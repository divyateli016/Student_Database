/*
 * SimpleUI.cpp
 *
 *  Created on: Jan 5, 2025
 *      Author: divya
 */

#include "SimpleUI.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb &DB) :
		db(DB)
{
}

void SimpleUI::run()
{
	bool terminate = false;

	while (!terminate)
	{
		std::cout
				<< "Enter your option to select desired function from below list:"
				<< endl << "1.Add new course " << endl << "2.List Course"
				<< endl << "3.Add new Student" << endl << "4. add Enrollment"
				<< endl << "5.print Student" << endl << "6. search Student"
				<< endl << "7.update student" << endl << "8.Write to the file"
				<< endl << "9.Read from the file" << endl
				<< "10. read the data from server" << endl << "0. Exit" << endl;

		int choice;
		cout << "enter your choice : ";
		cin >> choice;

		switch (choice)
		{
		case 0: //Exit and restart
		{
			terminate = true;
			cout << "Exited....reenter the option to start" << endl;
		}
			break;
		case 1: //Add new Course
		{
			addCourse();
		}
			break;
		case 2: //List Course
		{
			ListCourse();
		}
			break;
		case 3: //Add new Student
		{
			addStudent();
		}
			break;
		case 4: //Add enrollment
		{
			addEnrollment();
		}
			break;
		case 5: //print Student
		{
			printStudent();
		}
			break;
		case 6: //Search Student
		{
			searchStudent();
		}
			break;
		case 7: //update Student
		{
			updateStudent();
		}
			break;
		case 8: //Write to the file
		{
			std::string filename;
			cout << "Enter the file name to which the data has to be written"
					<< endl;
			cin >> filename;
			ofstream out(filename);
			this->db.write(out);
		}
			break;
		case 9: //Read from the file
		{
			std::string filename;
			cout << "Enter the file name to be read" << endl;
			cin >> filename;
			ifstream in(filename);
			//this->db.read(in);

		}
			break;
		case 10: // Read from server
		{
			unsigned int dataCount;
			cout << "Enter no. of student's data to be fetched from server: ";
			cin >> dataCount;
			this->db.fetchdatafromstream(dataCount);
		}
			break;

		default:
		{
			cout << "Please enter the valid option" << endl;
		}
			break;

		}

	}
}

void SimpleUI::addCourse()
{
	unsigned char courseType;
	std::string title;
	unsigned int courseKey;
	std::string newmajor;
	float creditPoints;

	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::DateTime::DaysOfWeek dayofweek;

	cout << "Enter the course Type : w[WeeklyCourse], b[BlockCourse]";
	cin >> courseType;

	cout << "Enter the coursekey : ";
	cin >> courseKey;

	cout << "Enter the title of the course : ";
	cin.ignore();

	getline(std::cin, title);

	cout << "Enter the newmajor : ";
	cin >> newmajor;

	cout << "Enter the credits for the course : ";
	cin >> creditPoints;

	int startHour, startMinute;
	int endHour, endMinute;

	std::cout << "Enter the start time of the course : Hour";
	std::cin >> startHour;

	std::cout << "Enter the start time of the Course : minute";
	std::cin >> startMinute;

	std::cout << "Enter the end time of course : Hour";
	std::cin >> endHour;

	std::cout << "Enter the end Time of the Course : minute";
	std::cin >> endMinute;

	startTime.assign(startHour, startMinute, 0);
	endTime.assign(endHour, endMinute, 0);

	if (courseType == 'w' || courseKey == 'W')
	{
		int day;
		std::cout << "Enter the day of the week : ";
		cin >> day;

		switch (day)
		{
		case 0: //Sunday

			dayofweek = Poco::DateTime::DaysOfWeek::SUNDAY;
			break;

		case 1: //Monday
			dayofweek = Poco::DateTime::DaysOfWeek::MONDAY;
			break;

		case 2: //Tuesday

			dayofweek = Poco::DateTime::DaysOfWeek::TUESDAY;
			break;

		case 3: //Wednesday
			dayofweek = Poco::DateTime::DaysOfWeek::WEDNESDAY;
			break;

		case 4: //Thursday

			dayofweek = Poco::DateTime::DaysOfWeek::THURSDAY;
			break;

		case 5: //Friday

			dayofweek = Poco::DateTime::DaysOfWeek::FRIDAY;
			break;

		case 6: //saturday
			dayofweek = Poco::DateTime::DaysOfWeek::SATURDAY;
			break;

		default:

			std::cerr << "Invalid day ofthe week....re enter the day" << endl;
			break;

		}
		this->db.addweeklyCourse(courseKey, title, newmajor, creditPoints,
				dayofweek, startTime, endTime);

	}
	else if (courseType == 'b' || courseType == 'B')
	{
		int startDay, startMonth, startYear;
		int endDay, endMonth, endYear;

		cout << "Enter the start date : Day : ";
		cin >> startDay;

		cout << "Enter the start date : Month : ";
		cin >> startMonth;

		cout << "Enter the start date : year : ";
		cin >> startYear;

		cout << "Enter the end date : day : ";
		cin >> endDay;

		cout << "Enter the end date : Month : ";
		cin >> endMonth;

		cout << "Enter the end date : year ; ";
		cin >> endYear;

		startDate.assign(startYear, startMonth, startDay);
		endDate.assign(endYear, endMonth, endDay);

		this->db.addblockCourse(courseKey, title, newmajor, creditPoints,
				startDate, endDate, startTime, endTime);
	}
	else
	{
		cout << "Invalid Course Type : " << endl;
	}

}

void SimpleUI::ListCourse()
{
	//Checking if the course is present in zhe list
	if (this->db.getcourses().size() > 0)
	{
		//This prints the size of the list
		cout << "Size is the list is ; " << this->db.getcourses().size()
				<< endl;

		//Iterating through the loop to get the each courses
		for (const auto &courseit : this->db.getcourses())
		{
			/**
			 * <This line returns the raw pointer assosiated with the Cours
			 *  class since the value of map is of the type map>
			 *
			 */
			const Course *courseptr = courseit.second.get();
			/**It returns the raw pointer pointing to the object of the derived
			 *  class to which it is casted**/
			if (const BlockCourse *blockcourse =
					dynamic_cast<const BlockCourse*>(courseptr))
			{
				ostringstream oss1;
				ostringstream oss2;

				//ostrinstream is used to for mat the date in this way DD:MM:YYYY

				oss1 << setw(2) << setfill('0')
						<< blockcourse->getstartDate().day() << ":" << setw(2)
						<< setfill('0') << blockcourse->getstartDate().month()
						<< ":" << blockcourse->getstartDate().year();

				oss2 << setw(2) << setfill('0')
						<< blockcourse->getendDate().day() << ":" << setw(2)
						<< setfill('0') << blockcourse->getendDate().month()
						<< ":" << blockcourse->getendDate().year();

				/**This is to format the date and the DateTime argument which
				 * needs to be transfered to the Formatter::format function
				 */
				Poco::DateTime start(1, 1, 1,
						blockcourse->getstartTime().hour(),
						blockcourse->getstartTime().minute());

				Poco::DateTime end(1, 1, 1, blockcourse->getendTime().hour(),
						blockcourse->getendTime().minute());

				std::string startTime = Poco::DateTimeFormatter::format(start,
						"%H:%M");
				std::string endTime = Poco::DateTimeFormatter::format(end,
						"%H:%M");

				std::string titleupper;

				for (char c : blockcourse->gettitle())
				{
					titleupper += std::toupper(c);
				}

				cout << "List of the blocked courses are" << endl
						<< "Course Key : " << blockcourse->getcourseKey()
						<< endl << "Title : " << titleupper << endl
						<< "Major is : " << blockcourse->getMajor() << endl
						<< "Credit Points are : "
						<< blockcourse->getcreditPoints() << endl
						<< "Start Date is : " << oss1.str() << endl
						<< "End date is : " << oss2.str() << endl
						<< "Start Time is : " << startTime << endl
						<< "End Time is : " << endTime << endl;
			}
			else if (const WeeklyCourse *weeklycourse =
					dynamic_cast<const WeeklyCourse*>(courseptr))
			{
				std::string titleupper;

				for (char c : weeklycourse->gettitle())
				{
					titleupper += std::toupper(c);
				}

				Poco::DateTime start(1, 1, 1,
						weeklycourse->getstartTime().hour(),
						weeklycourse->getstartTime().minute());

				Poco::DateTime end(1, 1, 1, weeklycourse->getendTime().hour(),
						weeklycourse->getendTime().minute());

				std::string startTime = Poco::DateTimeFormatter::format(start,
						"%H:%M");
				std::string endTime = Poco::DateTimeFormatter::format(end,
						"%H:%M");

				cout << "Weekly course details are : " << endl
						<< "Course key is : " << weeklycourse->getcourseKey()
						<< endl << "Title is : " << titleupper << endl
						<< "Major is : " << weeklycourse->getMajor() << endl
						<< "Credit Points are : "
						<< weeklycourse->getcreditPoints() << endl
						<< "Day of the week is : "
						<< weeklycourse->getdaysofweek() << endl
						<< "Start Time is : " << startTime << endl
						<< "End Time is : " << endTime << endl;

			}
			cout << endl;
		}

	}
	else
		cout << "No course is added.." << endl;
}

void SimpleUI::addStudent()
{
	std::string firstName;
	std::string lastName;
	std::string additionalInfo;
	int day;
	int month;
	int year;
	std::string street;
	std::string cityName;
	unsigned short postalCode;
	Poco::Data::Date DateOfBirth;

	std::cout << "Enter firstName of student needs to be added:";
	std::cin >> firstName;

	std::cout << "Enter lastname of the student needs to be added : ";
	std::cin >> lastName;

	std::cout << "Enter the date of DOB : ";
	std::cin >> day;

	std::cout << "Enter the month of DOB : ";
	std::cin >> month;

	std::cout << "Enter the year of DOB : ";
	std::cin >> year;

	cin.ignore(); //remove the unwanted characters left over in the input buffer

	std::cout << "Enter the street of student : ";
	getline(cin, street); // to get the entire line of input as a string.

	std::cout << "Enter the cityName of student : ";
	getline(cin, cityName); //to get the entire line of input as a string.

	std::cout << "Enter the postalCode of the student : ";
	std::cin >> postalCode;

	cin.ignore(); //remove the unwanted characters left over in the input buffer
	std::cout << "Add additional info for address : ";
	getline(cin, additionalInfo); //to get the entire line of input as a string.

	//cin.ignore();
	DateOfBirth.assign(year, month, day);

	this->db.addStudent(firstName, lastName, DateOfBirth, street, postalCode,
			cityName, additionalInfo);
}

void SimpleUI::addEnrollment()
{
	unsigned int matrikelNumber;
	unsigned int coursekey;
	std::string semester;

	std::cout << "Enter the matrikelNumber : ";
	std::cin >> matrikelNumber;

	auto studentiterator = this->db.getstudents().find(matrikelNumber);
	//If the student with desired matrikel number found
	if (studentiterator != this->db.getstudents().end())
	{
		std::cout << "Enter the courseKey : ";
		std::cin >> coursekey;

		auto courseiterator = this->db.getcourses().find(coursekey);

		if (courseiterator != this->db.getcourses().end())
		{
			bool enrollmetexists = false;

			for (auto &enrollments : studentiterator->second.getenrollments()) //Student iterator is the map pair with key and value where second gives the student object in map and first gives the enrollment int the map
			{
				if (enrollments.getcourse()->getcourseKey() == coursekey)
				{
					enrollmetexists = true;
					break;
				}
			}
			if (!enrollmetexists)
			{
				cout << "Enter the semester : ";
				cin >> semester;

				this->db.addEnrollment(matrikelNumber, coursekey, semester);
			}
			else
				cout << "enrollment already exists : " << endl;
		}
		else
			cout << "Invalid course Key : " << endl;
	}
	else
		cout << "Invalid Matrikel Number is entered." << endl;
}

void SimpleUI::printStudent()
{
	int matrikelNumber;
	cout << "Enter the matrikel number:" << endl;
	cin >> matrikelNumber;

	auto studentit = this->db.getstudents().find(matrikelNumber);
	if (studentit != this->db.getstudents().end())
	{
		auto &student = studentit->second;

		cout << "Student information is : " << endl;
		cout << "Matrikel Number is : " << student.getmatrikelNumber() << endl
				<< "First name of the student is : " << student.getFirstName()
				<< endl << "LAst name of the student is : "
				<< student.getlastName() << endl
				<< "Date of Birth if the student is : "
				<< student.getDateOfbirth().day() << "."
				<< student.getDateOfbirth().month() << "."
				<< student.getDateOfbirth().year() << endl;

		cout << "Address of the Student is : " << endl << "Street name is : "
				<< student.getaddress()->getstreet() << endl
				<< "PostalCode is : " << student.getaddress()->getpostalCode()
				<< endl << "City name is : "
				<< student.getaddress()->getcityName() << endl;

		if (student.getaddress()->getadditionalInfo() != " ")
		{
			cout << "Additional info is : "
					<< student.getaddress()->getadditionalInfo() << endl;
		}

		if (student.getenrollments().size() > 0)
		{
			cout << "Size of enrollment is : "
					<< student.getenrollments().size() << endl;
			cout << "Enrollment details are : " << endl;

			for (auto &enrollment : student.getenrollments())
			{
				cout << "courses enrolled for : "
						<< enrollment.getcourse()->getcourseKey() << endl
						<< "Semester is : " << enrollment.getsemester() << endl;

				if (enrollment.getgrade() > 0)
				{
					cout << "grades of the student is : "
							<< enrollment.getgrade();
				}
			}
		}
		else
		{
			cout << "No enrollments found." << endl;
		}

	}
	else
	{
		cout << "Invalid Matrikel Number : " << endl;
	}

}

void SimpleUI::searchStudent()
{
	std::string input;

	std::cout << "Enter the string needs to be searched : " << endl;
	std::cin >> input;

	std::string firstName;
	std::string lastName;

	bool studentexist = false;

	for (auto &studentpair : this->db.getstudents())
	{
		firstName = studentpair.second.getFirstName();
		lastName = studentpair.second.getlastName();

		/**This if condition checks if the provided input string is the substr
		 * of first name or last name
		 */
		if ((firstName.std::string::find(input) != std::string::npos)
				|| (lastName.find(input) != std::string::npos))
		{
			studentexist = true;

			std::cout << "Matrikel Number of Student is : "
					<< studentpair.second.getmatrikelNumber() << endl
					<< "First name of student is : "
					<< studentpair.second.getFirstName() << endl
					<< "lastNAme of the student is : "
					<< studentpair.second.getlastName() << endl;
		}

	}
	if (!studentexist)
	{
		cout << endl << "Student not found " << endl;
	}

}

void SimpleUI::updateStudent()
{
	unsigned short matrikelNumber;

	cout << "Enter the matrikel Number of student to be searched to update : "
			<< endl;
	cin >> matrikelNumber;

	int day, month, year;
	Poco::Data::Date dateOfBirth;

	auto Studeniterator = this->db.getstudents().find(matrikelNumber);

	if (Studeniterator != this->db.getstudents().end())
	{
		//bool exit = false;
		bool enterupdate = true;

		while (enterupdate)
		{
			cout
					<< "Enter options to update the particular student details"
					<< endl << "1. update FirstName " << endl
					<< "2. update Last Name" << endl
					<< "3. update date of Birth " << endl
					<< "4. update Enrollment " << endl << "5. update Address "
					<< endl << "0. Exit" << endl;

			unsigned int choice;
			cout << "Enter your choice : ";
			cin >> choice;

			std::string firstName;
			std::string lastName;
			Poco::Data::Date DateOfBirth;

			switch (choice)
			{
			case 0: //Exit 0
			{
				//exit = true;
				enterupdate = false;
				cout << "Exiting the update process..." << endl;

			}
				break;
			case 1: //update FirstNAme
			{
				cout << "Enter First Name : ";
				cin >> firstName;

				this->db.updateStudentInfo(matrikelNumber, choice, firstName,
						lastName, DateOfBirth);
			}
				break;
			case 2: //update second name
			{
				cout << "Enter Last Name : ";
				cin >> lastName;

				this->db.updateStudentInfo(matrikelNumber, choice, firstName,
						lastName, DateOfBirth);
			}
				break;
			case 3:
			{
				cout << "Enter Date of Birth [Day] :";
				cin >> day;

				cout << "Enter month of Birth : ";
				cin >> month;

				cout << "Enter birth year : ";
				cin >> year;

				dateOfBirth.assign(month, day, year);

				this->db.updateStudentInfo(matrikelNumber, choice, firstName,
						lastName, DateOfBirth);
			}
				break;
			case 4: //update Enrollment
			{
				unsigned int courseKey;

			cout<<"Enter the coursekey to modify the enrollment of course: ";
				cin >> courseKey;

				bool validCoursekey = false;

				const auto &student = this->db.getstudents().at(matrikelNumber);

				for (auto enrol : student.getenrollments())
				{
					if (enrol.getcourse()->getcourseKey() == courseKey)
					{
						validCoursekey = true;
					}
				}

				if (validCoursekey)
				{
					unsigned int choice;
					cout << "Enter the option to update the enrollment : "
							<< endl << "1. remove enrollment : " << endl
							<< "2. update the grade : " << endl;
					cin >> choice;

					float grade;
					switch (choice)
					{
					case 1: //remove enrollment
					{
						this->db.updatEnrollmentinfo(matrikelNumber, choice,
								courseKey, grade);

					}
						break;
					case 2: // update grade
					{
						//float grade;
						cout << "Enter grade : ";
						cin >> grade;
						this->db.updatEnrollmentinfo(matrikelNumber, choice,
								courseKey, grade);
					}
						break;
					}
				}
				else
				{
					std::cout << "Invalid Course key" << endl;
				}
			}
				break;
			case 5: //Update Address
			{
				std::string street;
				unsigned short postalCode;
				std::string cityName;
				std::string additionalInfo;

				cout << "Enter the name of street : ";
				cin >> street;
				//cout << endl;

				cout << "Enter the postalCode : ";
				cin >> postalCode;
				cin.ignore();

				cout << "Enter the cityName : ";
				getline(cin, cityName);

				cout << "Enter the additionalInfo : ";
				getline(cin, additionalInfo);

				this->db.updateAddress(matrikelNumber, street, postalCode,
						cityName, additionalInfo);

			}
				break;
			default:
			{
				cout << "Please Enter valid Choice" << endl;
			}
				break;
			}
		}
	}
}

//need to add some more options for other part of exercises

SimpleUI::~SimpleUI()
{
	// TODO Auto-generated destructor stub
}

