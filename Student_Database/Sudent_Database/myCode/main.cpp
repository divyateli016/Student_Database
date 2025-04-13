// Standard (system) header files
#include <iostream>
#include <cstdlib>

#include "Student.h"
#include "StudentDb.h"
#include "Address.h"
#include "Enrollment.h"
#include "SimpleUI.h"
#include <Poco/Data/Date.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>

#include<map>
#include <utility>
#include <memory>

// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main()
{

	StudentDb db;

	SimpleUI UI(db);
	UI.run();

   /**

	ifstream file("test.txt");

	ostringstream oss;
	oss << file.rdbuf();
	string data = oss.str();
	istringstream iss(data);

	db.read(iss);
	cout << endl << "New Data";
	db.write(cout);
	file.close();
  **/


	return 0;
}
