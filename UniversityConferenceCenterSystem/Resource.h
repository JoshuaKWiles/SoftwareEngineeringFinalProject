#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <exception>
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
	Location(const std::string& id);
	Location(const Location::RoomType& hostRoom);
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
		throw std::logic_error("Room Does Not Exist.");
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
		throw std::logic_error("Room Does Not Exist.");
	}
};

Location::RoomType typeLocation(const std::string& location) {
	if (location == "Roosevelt") return Location::Roosevelt;
	else if (location == "Lincoln") return Location::Lincoln;
	else if (location == "Washington") return Location::Washington;
	throw std::logic_error("Room Does Not Exist.");
}

std::string typeName(const Location::RoomType& resource) {
	switch (resource) {
	case Location::Roosevelt:
		return "Roosevelt";
	case Location::Lincoln:
		return "Lincoln";
	case Location::Washington:
		return "Washington";
	}
	throw std::logic_error("Room Does Not Exist.");
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
	Equipment(const std::string& id);
	Equipment(const EquipmentType& type);
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
		throw std::logic_error("Equipment Type Does Not Exist.");
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
		throw std::logic_error("Equipment Type Does Not Exist.");
	}
};

Equipment::EquipmentType typeEquipment(const std::string& type) {
	if (type == "Whiteboard") return Equipment::Whiteboard;
	else if (type == "Projector") return Equipment::Projector;
	else if (type == "Speaker") return Equipment::Speaker;
	else if (type == "Microphone") return Equipment::Microphone;
	throw std::logic_error("Equipment Type Does Not Exist.");
}

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
	throw std::logic_error("Equipment Type Does Not Exist.");
}