#include <exception>
#include <assert.h>

#include <string>

#include "ConferenceCenterSystem.h"
#include "ScheduleEvent.h"
int main()
{
	ConferenceManager& manager = *ConferenceManager::getInstance();
	manager.init();

	Session test("Test Session", Location::Washington, "11:00 AM", "3:00 PM");
	std::cerr << test.scheduleID << std::endl;
	std::cerr << manager.eventManager->sessionName(test.scheduleID) << "\t(" << manager.eventManager->sessionStart(test.scheduleID) << " - " << manager.eventManager->sessionEnd(test.scheduleID) << ')' << std::endl;

	Location* tmp = manager.eventManager->sessionLocation(test.scheduleID);

	std::cerr << tmp << '\n' << tmp->getName() << std::endl;

	return EXIT_SUCCESS;
}
