#include <exception>
#include <assert.h>

#include <string>

#include "ConferenceCenterSystem.h"
#include "ScheduleEvent.h"
int main()
{
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

	Event test1("Software Engineering Conference", "Jan 2, 2011", 500.0);
	test1.newSession(1, "C++", Location::Roosevelt, "10:00 AM", "3:00 PM");
	test1.newSession(2, "Python", Location::Washington, "10:00", "3:00 PM");
	test1.session(1)->addResource(Equipment::Speaker);

	Event test2("Game Con", "Jan 2, 2011", 500.0);
	test2.newSession(1, "DnD", Location::Lincoln, "3:00 PM", "5:00 PM");
	test2.session(1)->addResource(Equipment::Speaker);

	
	Event test3(test1.scheduleID);

	std::cout << test3.name << ": ";
	std::cout << test3.getSchedule() << std::endl;

	return EXIT_SUCCESS;
}
