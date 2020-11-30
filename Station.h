/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/05
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Station.h
*/
#pragma once
#include<string>


class Station {
	size_t station_id{ 0 };
	std::string m_name{ "" }; //the name of the item handled that the station
	std::string station_desc{ "" };
	size_t serial_number{ 0 };
	size_t qty_items{ 0 };
	static size_t m_widthField;
	static size_t id_generator; //incremented every time a new instance is created
public:
	Station() {};
	Station(const std::string str);
	const std::string& getItemName() const; //returns m_name
	unsigned int getNextSerialNumber(); //returns next serial number and increment serialnumber
	unsigned int getQuantity() const; //returns items left
	void updateQuantity(); //substracts one from items_left
	void display(std::ostream& os, bool full) const;

};

