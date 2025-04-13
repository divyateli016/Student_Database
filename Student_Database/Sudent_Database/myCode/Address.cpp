/*
 * Address.cpp
 *
 *  Created on: Jan 5, 2025
 *      Author: divya
 */

#include "Address.h"


Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalinfo):
		street(street),postalCode(postalCode),cityName(cityName),
		additionalInfo(additionalinfo)
{
}


Address::~Address()
{
	// TODO Auto-generated destructor stub
}

const std::string& Address::getstreet() const
{
	return street;
}

const unsigned short Address::getpostalCode() const
{
	return postalCode;
}

const std::string& Address::getcityName() const
{
	return this->cityName;
}

const std::string& Address::getadditionalInfo() const
{
	return additionalInfo;
}

void Address::write(std::ostream &out) const
{
	out<<";"<<getstreet()<<";"<<getpostalCode()<<";"<<getcityName()<<";"<<
			getadditionalInfo();
}

void Address::read(std::istream &in)
{
	std::string streetname;
	std::string postalCode;
	std::string cityName;
	std::string additionalInfo;

	getline(in,streetname,';');
	getline(in,postalCode,';');
	getline(in,cityName,';');
	getline(in,additionalInfo,';');

	unsigned int postalcode = (unsigned int)stoi(postalCode);
	this->street = streetname;
	this->postalCode = postalcode;
	this->cityName = cityName;
	this->additionalInfo = additionalInfo;

}

Address::Address()
{
}
