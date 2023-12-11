#include <exception>
#include <assert.h>

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "ConferenceCenterSystem.h"
#include "ScheduleEvent.h"

bool inputYN(std::string prompt) {
	std::string in;
	
	std::cout << prompt + " [Y/N] ";
	std::getline(std::cin, in);

	if (in == "Y" || in == "y" || in == "YES" || in == "Yes" || in == "yes") return true;
	else if (in == "N" || in == "n" || in == "NO" || in == "No" || in == "no") return false;
	
	return inputYN(prompt);
}

Location::RoomType inputRoom() {
	std::string in;
	
	std::cout << "Enter the location, [R]oosevelt/[L]incoln/[W]ashington: ";
	std::getline(std::cin, in);

	if (in == "R" || in == "r" || in == "Roosevelt" || in == "roosevelt") return Location::Roosevelt;
	else if (in == "L" || in == "l" || in == "Lincoln" || in == "lincoln") return Location::Lincoln;
	else if (in == "W" || in == "w" || in == "Washington" || in == "washington") return Location::Washington;
	
	return inputRoom();
}

int main()
{
	std::cout << "Event Builder Example." << std::endl;

	ConferenceManager& manager = *ConferenceManager::getInstance();
	manager.init();

	manager.resourceManager->addEquipment(Equipment::Microphone);
	manager.resourceManager->addEquipment(Equipment::Microphone);
	manager.resourceManager->addEquipment(Equipment::Microphone);
	manager.resourceManager->addEquipment(Equipment::Projector);
	manager.resourceManager->addEquipment(Equipment::Projector);
	manager.resourceManager->addEquipment(Equipment::Projector);
	manager.resourceManager->addEquipment(Equipment::Speaker);
	manager.resourceManager->addEquipment(Equipment::Speaker);
	manager.resourceManager->addEquipment(Equipment::Speaker);
	manager.resourceManager->addEquipment(Equipment::Whiteboard);
	manager.resourceManager->addEquipment(Equipment::Whiteboard);
	manager.resourceManager->addEquipment(Equipment::Whiteboard);

	std::vector<Event*> events;

	do {
		std::string name, date;
		std::string tmp;
		long double charge;

		std::cout << "Enter the name of the event: ";
		std::getline(std::cin, name);

		std::cout << "Enter the date of the event: ";
		std::getline(std::cin, date);

		std::cout << "Enter the cost of the event: ";
		std::getline(std::cin, tmp);
		charge = std::stod(tmp);

		events.push_back(new Event(name, date, charge));
		short morning = 1, evening = 3, special = 5;
		do {
			if (morning < 3 && inputYN("Would you like to add a morning session?")) {
				std::string start, end;
				Location::RoomType room;

				std::cout << "Enter the name of the session: ";
				std::getline(std::cin, name);

				room = inputRoom();

				std::cout << "Enter the starting time of the session: ";
				std::getline(std::cin, start);

				std::cout << "Enter the ending time of the session: ";
				std::getline(std::cin, end);

				events.back()->newSession(morning, name, room, start, end);

				if (inputYN("Does this session require a piece of equipment?")) {
					do {
						if (inputYN("Does this session require a Whiteboard?")) events.back()->session(morning)->addResource(Equipment::Whiteboard);
						else if (inputYN("Does this session require a Projector?")) events.back()->session(morning)->addResource(Equipment::Projector);
						else if (inputYN("Does this session require a Speaker?")) events.back()->session(morning)->addResource(Equipment::Speaker);
						else if (inputYN("Does this session require a Microphone?")) events.back()->session(morning)->addResource(Equipment::Microphone);
					} while (inputYN("Does this sessin require another piece of equipment?"));
				}
				morning++;
			}
			else if (morning >= 3) std::cout << "There are alrady two mornng sessions.\n";

			if (evening < 5 && inputYN("Would you like to add a evening session?")) {
				std::string start, end;
				Location::RoomType room;

				std::cout << "Enter the name of the session: ";
				std::getline(std::cin, name);

				room = inputRoom();

				std::cout << "Enter the starting time of the session: ";
				std::getline(std::cin, start);

				std::cout << "Enter the ending time of the session: ";
				std::getline(std::cin, end);

				events.back()->newSession(evening, name, room, start, end);

				if (inputYN("Does this session require a piece of equipment?")) {
					do {
						if (inputYN("Does this session require a Whiteboard?")) events.back()->session(evening)->addResource(Equipment::Whiteboard);
						else if (inputYN("Does this session require a Projector?")) events.back()->session(evening)->addResource(Equipment::Projector);
						else if (inputYN("Does this session require a Speaker?")) events.back()->session(evening)->addResource(Equipment::Speaker);
						else if (inputYN("Does this session require a Microphone?")) events.back()->session(evening)->addResource(Equipment::Microphone);
					} while (inputYN("Does this session require another piece of equipment?"));
				}
				evening++;
			}
			else if (evening >= 5) std::cout << "There are alrady two mornng sessions.\n";

			if (special < 7 && inputYN("Would you like to add a special session?")) {
				std::string start, end;
				long double additionalCharge;
				Location::RoomType room;

				std::cout << "Enter the name of the session: ";
				std::getline(std::cin, name);

				room = inputRoom();

				std::cout << "Enter the starting time of the session: ";
				std::getline(std::cin, start);

				std::cout << "Enter the ending time of the session: ";
				std::getline(std::cin, end);

				std::cout << "Enter the additinal charge for the special session: ";
				std::getline(std::cin, tmp);
				additionalCharge = std::stod(tmp);

				events.back()->newSpecialSession(special, name, room, start, end, additionalCharge);

				if (inputYN("Does this session require a piece of equipment?")) {
					do {
						if (inputYN("Does this session require a Whiteboard?")) events.back()->session(special)->addResource(Equipment::Whiteboard);
						else if (inputYN("Does this session require a Projector?")) events.back()->session(special)->addResource(Equipment::Projector);
						else if (inputYN("Does this session require a Speaker?")) events.back()->session(special)->addResource(Equipment::Speaker);
						else if (inputYN("Does this session require a Microphone?")) events.back()->session(special)->addResource(Equipment::Microphone);
					} while (inputYN("Does this sessin require another piece of equipment?"));
				}
				special++;
			}
			else if (special >= 7) std::cout << "There are alrady two mornng sessions.\n";
		} while ((morning < 3 && evening < 5 && special < 7) && (inputYN("Would you like to add another session?")));
	} while (inputYN("Would you like to make another event?"));

	std::cout << std::endl << std::endl << std::endl;

	for (auto event : events) {
		std::cout << event->name << std::endl;
		std::cout << "Charge per guest: " << event->charge << std::endl;
		std::cout << event->getSchedule();
	}

	for (auto event : events) delete event;

	return EXIT_SUCCESS;
}
