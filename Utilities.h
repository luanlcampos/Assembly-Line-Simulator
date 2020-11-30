/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/05
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Utilities.h
*/
#pragma once
#include<string>

class Utilities {
	size_t m_widthField; //lenght of the token
	static char m_delimiter;

public:
	Utilities();
	size_t getFieldWidth() const; //returns m_widthField
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(char newDelimiter);
	static char getDelimiter();
};

