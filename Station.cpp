/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/05
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Station.cpp
*/
#include <iostream>
#include <iomanip>

#include "Station.h"
#include "Utilities.h"


size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;


Station::Station(const std::string str) {
	//name,serial,qty,description
	if (!str.empty()) {
		bool more = true;
		size_t pos = 0;
		Utilities token;
		while (more) {
			//set station name
			m_name = token.extractToken(str, pos, more);
			if (m_name.size() > m_widthField)
				m_widthField = m_name.size();
			//set serial number
			serial_number = std::stoi(token.extractToken(str, pos, more));
			//set quantity of items
			qty_items = std::stoi(token.extractToken(str, pos, more));
			//set station description
			station_desc = token.extractToken(str, pos, more);
			//increment id
			id_generator++;
			//set id
			station_id = id_generator;
			more = false;
		}
	}
}

const std::string& Station::getItemName() const { return m_name; }

unsigned int Station::getNextSerialNumber() { 
	size_t temp = serial_number;
	serial_number++;
	return temp; 
}

unsigned int Station::getQuantity() const { return qty_items; }

void Station::updateQuantity() { --qty_items; }

void Station::display(std::ostream& os, bool full) const {
	//print station id
	os << "[" << std::setw(3) << std::setfill('0') << std::right<< station_id << "]" 
		//print item name
		<< " Item: " << std::setw(m_widthField) << std::setfill(' ')  << std::left << m_name 
		//print serial number
		<< " [" << std::setw(6) << std::setfill('0') << std::right << serial_number << "]";
	if (!full) {
		os << std::endl;
	}
	else {
		os << " Quantity: " << std::setw(m_widthField) << std::setfill(' ') << std::left << qty_items 
			<< " Description: " << station_desc << std::endl;
	}
}
