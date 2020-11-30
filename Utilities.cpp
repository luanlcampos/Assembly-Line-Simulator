/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/05
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Utilities.cpp
*/

#include <iostream>
#include "Utilities.h"


char Utilities::m_delimiter = '\0';

Utilities::Utilities() {
	m_widthField = 1;
}

size_t Utilities::getFieldWidth() const { return m_widthField; }

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	more = false;
	size_t i = str.find(m_delimiter, next_pos);

	std::string m_string{ "" };
	if (i != std::string::npos) {
		m_string = str.substr(next_pos, i - next_pos);
		next_pos = i + 1;
		more = true;
		if (m_string.size() > m_widthField)
			m_widthField = m_string.size();
	}

	else {
		i = str.find_last_of(m_delimiter) + 1;
		m_string = str.substr(i);
		more = false; 
	}

	if (m_string.empty())
		more = false;

	return m_string;
}

void Utilities::setDelimiter(char newDelimiter) { 
	m_delimiter = newDelimiter;
}
char Utilities::getDelimiter() { return m_delimiter; }
