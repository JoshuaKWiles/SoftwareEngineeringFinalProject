#include <exception>
#include <assert.h>

#include <string>

#include "Resource.h"
int main()
{
	{// Test Resource Classes
		{// Test Location Class
			{// Test Constructors on initializer type
				std::string ID("123");

				Location test1("123", Location::Roosevelt);
				Location test2(ID, Location::Roosevelt);

				assert(test1.id == test2.id);
				assert((test1.id == ID) && (test1.id == "123"));
				assert((test2.id == ID) && (test2.id == "123"));
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
				std::string ID("123");

				Equipment test1("123", Equipment::Whiteboard);
				Equipment test2(ID, Equipment::Whiteboard);

				assert(test1.id == test2.id);
				assert((test1.id == ID) && (test1.id == "123"));
				assert((test2.id == ID) && (test2.id == "123"));
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
		}
	}
	return EXIT_SUCCESS;
}
