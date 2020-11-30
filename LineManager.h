/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/19
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
LineManager.h
*/
#pragma once

#include <vector>
#include <deque>

#include "Workstation.h"
class LineManager {
	std::vector<Workstation*> AssemblyLine; 
	std::deque<CustomerOrder> ToBeFilled; //queue of all orders to be filled
	std::deque<CustomerOrder> Completed; //queue of all completed orders
	unsigned int m_cntCustomerOrder{ 0 }; //number of objects in the line
	Workstation* head{ nullptr };

public:
	LineManager() {};
	LineManager(const std::string file, std::vector<Workstation*>& line, std::vector<CustomerOrder>& orders);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

