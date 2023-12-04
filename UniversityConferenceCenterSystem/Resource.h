#pragma once
#include <string>
class Resource {
public:
	const std::string id;
	Resource(const char* resouceID) : id(resouceID) { }
	Resource(const std::string& resourceID) : id(resourceID) { }
	virtual long double getCost() = 0;
};

class Location : public Resource {
public:
	enum RoomType{
		Roosevelt,
		Lincoln,
		Washington
	};
	const RoomType room;
	Location(const char* locationID, RoomType hostRoom) : Resource(locationID), room(hostRoom) { }
	Location(const std::string locationID, RoomType hostRoom) : Resource(locationID), room(hostRoom) { }
	long double getCost() {
		switch (room){
		case Roosevelt:
			return 300.0l;
		case Lincoln:
			return 400.0l;
		case Washington:
			return 500.0l;
		default:
			return 0.0l; // There is an error if this happens
		}
	}
	const char* getName() {
		switch (room){
		case Roosevelt:
			return "Roosevelt";
		case Lincoln:
			return "Lincoln";
		case Washington:
			return "Washington";
		default:
			return "Location Error"; // There is an error if this happens
		}
	}
};

class Equipment : public Resource {
public:
	enum EquipmentType {
		Whiteboard,
		Projector,
		Speaker,
		Microphone
	};
	const EquipmentType what;
	Equipment(const char* equipmentID, EquipmentType type) : Resource(equipmentID), what(type) { }
	Equipment(const std::string& equipmentID, EquipmentType type) : Resource(equipmentID), what(type) { }
	long double getCost() {
		switch (what){
		case Whiteboard:
			return 60.0l;
		case Projector:
			return 100.0l;
		case Speaker:
			return 50.0l;
		case Microphone:
			return 30.0l;
		default:
			return 0.0l; // There is an error if this happens
		}
	}
};