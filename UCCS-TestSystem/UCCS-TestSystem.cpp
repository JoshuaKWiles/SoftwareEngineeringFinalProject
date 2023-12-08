#include <exception>
#include <assert.h>

#include <string>

#include "ConferenceCenterSystem.h"
#include "ScheduleEvent.h"
int main()
{
	ConferenceManager& manager = *ConferenceManager::getInstance();
	manager.init();

	manager.resourceManager->reportResources();


	return EXIT_SUCCESS;
}
