#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <string>

class Resource {
public:
	const std::string id;
	Resource(const std::string& resourceID) : id(resourceID) { }
	virtual long double getCost() const = 0;
	virtual std::string getName() const = 0;
};

class Location : public Resource {
public:
	enum RoomType{
		Roosevelt,
		Lincoln,
		Washington
	};
	const RoomType room;
	Location(const std::string& locationID, const RoomType& hostRoom) : Resource(locationID), room(hostRoom) { }
	long double getCost() const {
		switch (room){
		case Roosevelt:
			return 300.0l;
		case Lincoln:
			return 400.0l;
		case Washington:
			return 500.0l;
		}
	}
	std::string getName() const {
		switch (room){
		case Roosevelt:
			return "Roosevelt";
		case Lincoln:
			return "Lincoln";
		case Washington:
			return "Washington";
		}
	}
};

std::string typeName(const Location::RoomType& resource) {
	switch (resource) {
	case Location::Roosevelt:
		return "Roosevelt";
	case Location::Lincoln:
		return "Lincoln";
	case Location::Washington:
		return "Washington";
	}
}

class Equipment : public Resource {
public:
	enum EquipmentType {
		Whiteboard,
		Projector,
		Speaker,
		Microphone
	};
	const EquipmentType what;
	Equipment(const std::string& equipmentID, const EquipmentType& type) : Resource(equipmentID), what(type) { }
	long double getCost() const {
		switch (what){
		case Whiteboard:
			return 60.0l;
		case Projector:
			return 100.0l;
		case Speaker:
			return 50.0l;
		case Microphone:
			return 30.0l;
		}
	}
	std::string getName() const {
		switch (what)
		{
		case Whiteboard:
			return "Whiteboard";
		case Projector:
			return "Projector";
		case Speaker:
			return "Speaker";
		case Microphone:
			return "Microphone";
		}
	}
};

std::string typeName(const Equipment::EquipmentType& resource) {
	switch (resource) {
	case Equipment::Whiteboard:
		return "Whiteboard";
	case Equipment::Projector:
		return "Projector";
	case Equipment::Speaker:
		return "Speaker";
	case Equipment::Microphone:
		return "Microphone";
	}
}