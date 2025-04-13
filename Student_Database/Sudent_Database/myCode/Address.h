/**
 * @file Address.h
 * @brief Defines the Address class for storing and handling address details.
 *
 * This file contains the declaration of the Address class, which encapsulates
 * details such as street name, postal code, city name, and additional information.
 * It provides constructors, getter functions, and methods for reading/writing
 * address data to streams.
 *
 * @date Created on: Jan 5, 2025
 * @author Divya
 */
#include <string>
#include <iostream>
#include <memory>

#ifndef ADDRESS_H_
#define ADDRESS_H_

/**
 * @class Address
 * @brief Represents an address with street, postal code, city name,
 * and additional info.
 */
class Address
{
private:
	std::string street;    /**< Street name of the address. */
	unsigned short postalCode; /**< Postal code of the address. */
	std::string cityName;      /**< City name of the address. */
	std::string additionalInfo;  /**<Additional information about the address.*/

public:
	/**
	  * @brief Default constructor initializes an empty address.
	  */
	Address();
	/**
	  * @brief Parameterized constructor initializes address with given values.
	  * @param street Name of the street.
	  * @param postalCode Postal code of the address.
	  * @param cityName Name of the city.
	  * @param additionalInfo Additional details about the address.
	  */
	Address(std::string street, unsigned short int postalCode,
			std::string cityName, std::string additionalinfo);
	/**
	  * @brief Gets the street name.
	  * @return A constant reference to the street name string.
	  */
	const std::string& getstreet() const;
	/**
	 * @brief Gets the postal code.
	 * @return The postal code as an unsigned short integer.
	 */
	const unsigned short getpostalCode() const;
	/**
	  * @brief Gets the city name.
	  * @return A constant reference to the city name string.
	  */
	const std::string& getcityName() const;
	 /**
	   * @brief Gets additional information about the address.
	   * @return A constant reference to the additional info string.
	   */
	const std::string& getadditionalInfo() const;
	   /**
	     * @brief Writes address details to an output stream.
	     * @param out Output stream to write to.
	     */
	void write(std::ostream &out) const;
	/**
	  * @brief Reads address details from an input stream.
	  * @param in Input stream to read from.
	  */
	void read(std::istream &in);
	/**
	  * @brief Destructor for the Address class.
	  */
	virtual ~Address();
};

#endif /* ADDRESS_H_ */
