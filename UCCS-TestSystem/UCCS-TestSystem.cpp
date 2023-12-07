#include <exception>
#include <assert.h>

#include <string>

#include "ConferenceCenterSystem.h"
#include "Resource.h"
#include "Guest.h"
#include "ScheduleEvent.h"
int main()
{
	{// Test Resource Classes
		{// Test Location Class
			{// Test Constructors on initializer type
				std::string testID("123");

				Location test1("123", Location::Roosevelt);
				Location test2(testID, Location::Roosevelt);

				assert(test1.id == test2.id);
				assert((test1.id == testID) && (test1.id == "123"));
				assert((test2.id == testID) && (test2.id == "123"));
			}
			{// Test getCost() function on all RoomTypes
				Location test1("123", Location::Roosevelt);
				Location test2("123", Location::Lincoln);
				Location test3("123", Location::Washington);

				assert(test1.getCost() == 300.0l);
				assert(test2.getCost() == 400.0l);
				assert(test3.getCost() == 500.0l);
			}
			{// Test getName() function on all RoomTypes
				Location test1("123", Location::Roosevelt);
				Location test2("123", Location::Lincoln);
				Location test3("123", Location::Washington);

				assert(test1.getName() == "Roosevelt");
				assert(test2.getName() == "Lincoln");
				assert(test3.getName() == "Washington");
			}
		}
		{// Test Equipment Class
			{// Test Constructors on initializer type
				std::string testID("123");

				Equipment test1("123", Equipment::Whiteboard);
				Equipment test2(testID, Equipment::Whiteboard);

				assert(test1.id == test2.id);
				assert((test1.id == testID) && (test1.id == "123"));
				assert((test2.id == testID) && (test2.id == "123"));
			}
			{// Test getCost() function on all EquipmentTypes
				Equipment test1("123", Equipment::Whiteboard);
				Equipment test2("123", Equipment::Projector);
				Equipment test3("123", Equipment::Speaker);
				Equipment test4("123", Equipment::Microphone);

				assert(test1.getCost() == 60.0l);
				assert(test2.getCost() == 100.0l);
				assert(test3.getCost() == 50.0l);
				assert(test4.getCost() == 30.0l);
			}
			{// Test getName() function on all EquipmentTypes
				Equipment test1("123", Equipment::Whiteboard);
				Equipment test2("123", Equipment::Projector);
				Equipment test3("123", Equipment::Speaker);
				Equipment test4("123", Equipment::Microphone);

				assert(test1.getName() == "Whiteboard");
				assert(test2.getName() == "Projector");
				assert(test3.getName() == "Speaker");
				assert(test4.getName() == "Microphone");
			}
		}
	}
	{// Test Guest structs
		{// Test Guest Constructor
			std::string testName("Test");
			std::string testID("123");

			Guest test1("Test", "123");
			Guest test2(testName, testID);

			assert((test1.name == test2.name) && (test1.guestID == test2.guestID));

			assert(((test1.name == testName) && (test1.guestID == testID)) && ((test1.name == "Test") && (test1.guestID == "123")));
			assert(((test2.name == testName) && (test2.guestID == testID)) && ((test2.name == "Test") && (test2.guestID == "123")));
		}
		{// Test Guest Copy Constructor
			Guest test1("Test", "123");
			Guest test2(test1);

			assert((test1.name == "Test") && (test2.name == "Test"));
			assert((test1.guestID == "123") && (test2.guestID == "123"));

			assert((test1.name == test2.name) && (test1.guestID == test2.guestID));
		}
		{// Test Presenter Constructor
			std::string testName("Test");
			std::string testIDG("123");
			std::string testIDP("456");

			Guest testGuest(testName, testIDG);

			Presenter test1("Test", "123", "456");
			Presenter test2(testName, testIDG, testIDP);

			Presenter test3(testGuest, "456");
			Presenter test4(testGuest, testIDP);

			assert((test1.name == test2.name) && (test1.name == test3.name) && (test1.name == test4.name) && (test2.name == test3.name) && (test2.name == test4.name) && (test3.name == test4.name));
			assert((test1.guestID == test2.guestID) && (test1.guestID == test3.guestID) && (test1.guestID == test4.guestID) && (test2.guestID == test3.guestID) && (test2.guestID == test4.guestID) && (test3.guestID == test4.guestID));
			assert((test1.presenterID == test2.presenterID) && (test1.presenterID == test3.presenterID) && (test1.presenterID == test4.presenterID) && (test2.presenterID == test3.presenterID) && (test2.presenterID == test4.presenterID) && (test3.presenterID == test4.presenterID));

			assert(((test1.name == testName) && (test1.guestID == testIDG) && (test1.presenterID == testIDP)) && ((test1.name == "Test") && (test1.guestID == "123") && (test1.presenterID == "456")));
			assert(((test2.name == testName) && (test2.guestID == testIDG) && (test2.presenterID == testIDP)) && ((test2.name == "Test") && (test2.guestID == "123") && (test2.presenterID == "456")));
			assert(((test3.name == testName) && (test3.guestID == testIDG) && (test3.presenterID == testIDP)) && ((test3.name == "Test") && (test3.guestID == "123") && (test3.presenterID == "456")));
			assert(((test4.name == testName) && (test4.guestID == testIDG) && (test4.presenterID == testIDP)) && ((test4.name == "Test") && (test4.guestID == "123") && (test4.presenterID == "456")));
		}
		{// Test Presenter Copy Constructor
			Presenter test1("Test", "123", "456");
			Presenter test2(test1);

			assert((test1.name == "Test") && (test2.name == "Test"));
			assert((test1.guestID == "123") && (test2.guestID == "123"));
			assert((test1.presenterID == "456") && (test2.presenterID == "456"));

			assert((test1.name == test2.name) && (test1.guestID == test2.guestID) && (test1.presenterID == test2.presenterID));
		}
	}
	{// Test ConferenceManager Class
		{// Test Singleton
			ConferenceManager* test1 = ConferenceManager::getInstance();
			ConferenceManager* test2 = ConferenceManager::getInstance();

			assert(test1 == test2);
		}
		{// Test Session class (Calls ConferenceManager::getInstance)
			{// Test Initialization Values
				Session test("123", "Test Session", Location::Roosevelt, "3:00 PM", "5:00 PM");

				// Test Initalizaton Values
				assert(test.scheduleID == "123");
				assert(test.name == "Test Session");
				assert(test.startTime == "3:00 PM");
				assert(test.endTime == "5:00 PM");

				assert(test.location != nullptr);
			}
			{// Test getSchedule
				Session test("123", "Test Session", Location::Roosevelt, "3:00 PM", "5:00 PM");

				assert(test.getSchedule() == "(3:00 PM - 5:00 PM)");
			}
			{// Test Session location
				{// Test with Roosevelt
					Session test("123", "Test Session", Location::Roosevelt, "3:00 PM", "5:00 PM");

					assert(test.location->room == Location::Roosevelt);
					assert(test.location->getName() == "Roosevelt");
					assert(test.location->getCost() == 300.0l);
				}
				{// Test with Lincoln
					Session test("123", "Test Session", Location::Lincoln, "3:00 PM", "5:00 PM");

					assert(test.location->room == Location::Lincoln);
					assert(test.location->getName() == "Lincoln");
					assert(test.location->getCost() == 400.0l);
				}
				{// Test with Washington
					Session test("123", "Test Session", Location::Washington, "3:00 PM", "5:00 PM");

					assert(test.location->room == Location::Washington);
					assert(test.location->getName() == "Washington");
					assert(test.location->getCost() == 500.0l);
				}
			}
			{// Test getCost with out Equipmenet
				{// Test with Roosevelt
					Session test("123", "Test Session", Location::Roosevelt, "3:00 PM", "5:00 PM");

					assert(test.getCost() == test.location->getCost());
				}
				{// Test with Lincoln
					Session test("123", "Test Session", Location::Lincoln, "3:00 PM", "5:00 PM");

					assert(test.getCost() == test.location->getCost());
				}
				{// Test with Washington
					Session test("123", "Test Session", Location::Washington, "3:00 PM", "5:00 PM");

					assert(test.getCost() == test.location->getCost());
				}
			}
			{// Test Adding Equipment
				Session test("123", "Test Session", Location::Roosevelt, "3:00 PM", "5:00 PM");

				//std::cerr << test.reportResources() << std::endl;
				assert(test.reportResources() == "No Equipment Used.");

				test.addResource(Equipment::Whiteboard);
				//std::cerr << test.reportResources() << std::endl;
				assert(test.reportResources() == "Whiteboard");

				test.addResource(Equipment::Projector);
				//std::cerr << test.reportResources() << std::endl;
				assert(test.reportResources() == "Whiteboard Projector");

				test.addResource(Equipment::Speaker);
				//std::cerr << test.reportResources() << std::endl;
				assert(test.reportResources() == "Whiteboard Projector Speaker");

				test.addResource(Equipment::Microphone);
				//std::cerr << test.reportResources() << std::endl;
				assert(test.reportResources() == "Whiteboard Projector Speaker Microphone");
			}
			{// Test getCost with Equipmenet
				{// Test with Roosevelt
					Session test("123", "Test Session", Location::Roosevelt, "3:00 PM", "5:00 PM");

					// Add Whiteboard
					test.addResource(Equipment::Whiteboard);
					assert(test.getCost() == test.location->getCost() + 60.0l);

					// Add Projector
					test.addResource(Equipment::Projector);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l);

					// Add Speaker
					test.addResource(Equipment::Speaker);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l + 50.0l);

					// Add Microphone
					test.addResource(Equipment::Microphone);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l + 50.0l + 30.0l);
				}
				{// Test with Lincoln
					Session test("123", "Test Session", Location::Lincoln, "3:00 PM", "5:00 PM");

					// Add Whiteboard
					test.addResource(Equipment::Whiteboard);
					assert(test.getCost() == test.location->getCost() + 60.0l);

					// Add Projector
					test.addResource(Equipment::Projector);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l);

					// Add Speaker
					test.addResource(Equipment::Speaker);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l + 50.0l);

					// Add Microphone
					test.addResource(Equipment::Microphone);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l + 50.0l + 30.0l);
				}
				{// Test with Washington
					Session test("123", "Test Session", Location::Washington, "3:00 PM", "5:00 PM");

					// Add Whiteboard
					test.addResource(Equipment::Whiteboard);
					assert(test.getCost() == test.location->getCost() + 60.0l);

					// Add Projector
					test.addResource(Equipment::Projector);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l);

					// Add Speaker
					test.addResource(Equipment::Speaker);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l + 50.0l);

					// Add Microphone
					test.addResource(Equipment::Microphone);
					assert(test.getCost() == test.location->getCost() + 60.0l + 100.0l + 50.0l + 30.0l);
				}
			}
			{// Test getPresenter

			}
		}
	}
	return EXIT_SUCCESS;
}
