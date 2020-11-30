/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/05
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
CustomerOrder.h
*/

#include<iostream>
#include <iomanip>
#include <algorithm>

#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(std::string& record) {
	if (!record.empty()) {
		//local variables
		size_t pos{ 0 };
		bool more{ true };
		std::string temp = record;
		Utilities token;

		//setting the customer order name
		m_name = token.Utilities::extractToken(record, pos, more);
		temp.erase(0, temp.find_first_of(token.getDelimiter()) + 1);
		if (m_name.size() > m_widthField)
			m_widthField = m_name.size();

		//setting the customer order product
		m_product = token.Utilities::extractToken(record, pos, more);
		temp.erase(0, temp.find_first_of(token.getDelimiter()) + 1);
		if (m_product.size() > m_widthField)
			m_widthField = m_product.size();

		//counting the number of elements 
		size_t size = std::count(temp.begin(), temp.end(), token.getDelimiter()) + 1;
		m_cntItem = size;
		
		//setting the list of items
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(token.extractToken(record, pos, more));
			if (m_lstItem[i]->m_itemName.size() > m_widthField)
				m_widthField = m_lstItem[i]->m_itemName.size();
		}
	}
}

CustomerOrder::~CustomerOrder() {
	for (size_t i = 0; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
}

CustomerOrder::CustomerOrder(const CustomerOrder& src)
{
	throw "No Copies Allowed!";
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
	if (this != &src) {
		this->m_name = src.m_name;
		src.m_name.clear();

		this->m_product = src.m_product;
		src.m_product.clear();

		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;

		m_lstItem = src.m_lstItem;
		src.m_lstItem = nullptr;

		m_widthField = src.m_widthField;

		m_cntItem = src.m_cntItem;
		src.m_cntItem = 0;
	}
	return *this;
}

bool CustomerOrder::isOrderFilled() const {
	//check if the order is filled
	for (size_t i = 0; i < m_cntItem; i++) {
		if (!m_lstItem[i]->m_isFilled)
			return false;
	}
	return true;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	//check if the item is filled
	bool flag = true;
	if (!itemName.empty()) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (m_lstItem[i]->m_isFilled)
					flag = true;
				else flag=false;
			}
		}
	}
	return flag;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (size_t i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == station.getItemName()) {
			if (station.getQuantity() > 0) {
				station.updateQuantity(); //substract 1
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber(); //setting serial number
				m_lstItem[i]->m_isFilled = true;
				os << std::setw(11) << std::right <<"Filled " << m_name <<", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else {
				os << "Unable to fill " << m_name << ", " << m_product << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++) {
		os << "[" << std::setfill('0') << std::right << std::setw(6) << m_lstItem[i]->m_serialNumber << "]" << " ";
		os << std::setfill(' ') << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
		os << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
	}
}
