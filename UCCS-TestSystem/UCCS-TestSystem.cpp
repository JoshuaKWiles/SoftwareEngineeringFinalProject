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

	Event test1("Software Engineering Conference", "Jan 2, 2011", 500.0l);
	test1.newSession(1, "C++", Location::Roosevelt, "10:00 AM", "3:00 PM");
	test1.newSession(2, "Python", Location::Lincoln, "10:00", "3:00 PM");
	test1.session(1)->addResource(Equipment::Speaker);

	Event test2("Game Con", "Jan 2, 2011", 10.0);
	test2.newSpecialSession(5, "DnD", Location::Washington, "10:00 AM", "10:00 PM", 50.0l);
	test2.session(5)->addResource(Equipment::Speaker);

	
	Event test3(test2.scheduleID);

	std::cout << test3.name << ": ";
	std::cout << test3.getSchedule() << std::endl;

	return EXIT_SUCCESS;
}
