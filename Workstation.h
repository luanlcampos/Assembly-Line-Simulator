/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/19
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Workstation.h
*/
#pragma once

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation : public Station{
	
	std::deque<CustomerOrder> m_orders; //fill unfilled customer order
	Workstation* m_pNextStation{ nullptr }; //pointer to a next station

public:
	Workstation() : Station() {};
	Workstation(const std::string record);

	//DENY COPY AND MOVE
	Workstation(const Workstation& src) = delete;
	Workstation& operator=(const Workstation& src) = delete;
	Workstation(Workstation&& src) = delete;
	Workstation& operator=(Workstation&& src) = delete;

	void runProcess(std::ostream& os);
	bool moveOrder(); //move the order to the next station
	void setNextStation(Station& station); //store the next station in the pointer
	const Workstation *getNextStation() const; //return next station
	bool getIfCompleted(CustomerOrder& order); //remove from the queue if it is completed
	void display(std::ostream& os) const; //print the name of items
	Workstation& operator+=(CustomerOrder&& order); //push back the order into queue


};

