#include <exception>
#include <assert.h>

#include <string>

#include "ConferenceCenterSystem.h"
#include "ScheduleEvent.h"
int main()
{
	ConferenceManager& manager = *ConferenceManager::getInstance();
	manager.init();

	Event test1("Software Engineering Conference", "Jan 2, 2011", 500.0);
	test1.newSession(1, "C++", Location::Roosevelt, "10:00 AM", "3:00 PM");
	test1.newSession(2, "Python", Location::Washington, "10:00", "3:00 PM");

	std::cout << test1.name << ": ";
	std::cout << test1.getSchedule() << std::endl;

	Event test2("Game Con", "Feb 5, 2011", 500.0);
	test2.newSession(1, "DnD", Location::Roosevelt, "3:00 PM", "5:00 PM");

	std::cout << test2.name << ": ";
	std::cout << test2.getSchedule() << std::endl;

	return EXIT_SUCCESS;
}
