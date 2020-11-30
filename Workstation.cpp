/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/19
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Workstation.cpp
*/

#include <iostream>
#include <string>
#include "Workstation.h"

Workstation::Workstation(const std::string record) : Station(record), m_pNextStation{ nullptr } {

}

void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty())
		m_orders.front().fillItem(*this, os); //function from CustomerOrder::fillItem(Station& station, std::ostream& os)
}

bool Workstation::moveOrder() {
	bool moved = false;
	//move the order and remove it from deque
	if (!m_orders.empty() && m_pNextStation != nullptr && m_orders.front().isItemFilled(this->getItemName())) {
			*m_pNextStation += std::move(m_orders.front());
			m_orders.pop_front();
			moved = true;
	}
	
	return moved;
}

void Workstation::setNextStation(Station& station) {
	if (station.getQuantity() > 0) {
		m_pNextStation = (Workstation*)&station; //casting station to workstation*
	}
}

const Workstation *Workstation::getNextStation() const {
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool filled = false;
	//if the order is completed, remove from the orders deque
	if (!m_orders.empty() && m_orders.front().isOrderFilled()) {
		order = std::move(m_orders.front());
		m_orders.pop_front();
		filled = true;
	}
	return filled;
}

void Workstation::display(std::ostream& os) const{
	os << getItemName() << " --> ";
	(m_pNextStation != nullptr ? os << m_pNextStation->getItemName() << std::endl : os << "END OF LINE" << std::endl);
}

Workstation& Workstation::operator+=(CustomerOrder&& order) {
	m_orders.push_back(std::move(order));
	return *this;
}
 
