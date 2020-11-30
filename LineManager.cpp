/*
Name: Luan Lima Campos
Student ID: 119386191
Seneca email: llima-campos@myseneca.ca
Date: 2020/11/19
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
LineManager.h
*/

#include<iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string filename, std::vector<Workstation*>& line, std::vector<CustomerOrder>& orders) {
	std::ifstream fs(filename);
	Utilities token;
	std::string first, second;
	
	bool more = true;

	if (!fs) {
		throw std::string("Unable to open [") + filename + "] file.";
	}
	std::string temp;
	bool firstLoop = true;
	while (!fs.eof()) {
		size_t pos = 0;
		std::getline(fs, temp);
		first = token.extractToken(temp, pos, more);
		//setting the first element and all the next stations
		for (auto&& station : line) {
			if (station->getItemName() == first) {
				if (more) {
					second = token.extractToken(temp, pos, more);
					for (auto&& nextStation : line) {
						if (nextStation->getItemName() == second) {
							if (firstLoop) {
								firstLoop = false;
								head = station;
							}
							station->setNextStation(*nextStation);
						}
					}
				}
			}
		}
	}
	//set the assembly line with the sync line
	AssemblyLine = line;
	m_cntCustomerOrder = orders.size();

	//set the deque of orders to be filled
	for (size_t i = 0; i < orders.size(); i++) {
		ToBeFilled.push_back(std::move(orders[i]));
	}
}

bool LineManager::run(std::ostream& os) {
	static size_t counter =0;
	counter++;
	os << "Line Manager Iteration: " << counter << std::endl;

	//get the head order and move it to the deque toBeFilled
	if (!ToBeFilled.empty()) {
		*head += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();

	}

	//run process
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}
	
	//move the orders
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->moveOrder();
	}

	//get all completed orders and move them to the Completed deque
	CustomerOrder temp;
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		if (AssemblyLine[i]->getIfCompleted(temp)) {
			Completed.push_back(std::move(temp));
		}
	}

	//return true if all orders are completed
	return (Completed.size() == m_cntCustomerOrder);
}

void LineManager::displayCompletedOrders(std::ostream& os) const {
	for (auto& order : Completed) {
		order.display(os);
	}
}

void LineManager::displayStations() const {
	for (auto& station : AssemblyLine) {
		station->display(std::cout);
	}
}

void LineManager::displayStationsSorted() const {
	//display all stations starting by the head
	const Workstation* ws = head;
	while (ws) {
		ws->display(std::cout);
		ws = ws->getNextStation();
	}

}
