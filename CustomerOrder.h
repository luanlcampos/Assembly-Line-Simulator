/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/05
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
CustomerOrder.h
*/
#pragma once
#include <string>
#include "Station.h"

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name{ "" };
	std::string m_product{ "" };
	unsigned int m_cntItem{ 0 };
	Item** m_lstItem{ nullptr };
	static size_t m_widthField;

public:
	CustomerOrder() {};
	CustomerOrder(std::string& record);
	~CustomerOrder();

	//Copy
	CustomerOrder(const CustomerOrder& src);
	CustomerOrder& operator=(const CustomerOrder& srd) = delete;

	//Move
	CustomerOrder(CustomerOrder&& src) noexcept;
	CustomerOrder& operator=(CustomerOrder&& src) noexcept;

	bool isOrderFilled() const; 
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;

};

