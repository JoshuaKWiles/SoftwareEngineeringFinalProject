#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <string>

class Resource {
public:
	const std::string id;
	Resource(const char* resouceID) : id(resouceID) { }
	Resource(const std::string& resourceID) : id(resourceID) { }
	virtual long double getCost() = 0;
	virtual const char* getName() = 0;
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
	const char* getName() {
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
		default:
			return "Euipment Error";
		}
	}
};

class ResourceManager {
public:
	ResourceManager(SQLite::Database* db, UUIDv4::UUIDGenerator<std::mt19937_64>* generator) : database(db), uuidGenerator(generator) {}
	Location* regesterLocation(std::string sessionID, Location::RoomType location) { 
		std::string stmt;

		switch (location)
		{
		case Location::Roosevelt:
			stmt = "Roosevelt";
			break;
		case Location::Lincoln:
			stmt = "Lincoln";
			break;
		case Location::Washington:
			stmt = "Washington";
			break;
		}

		stmt = "SELECT resourceID FROM resources WHERE type ='" + stmt + "';";
		stmt = database->execAndGet(stmt.c_str()).getString();

		std::string id = stmt;

		stmt = "INSERT INTO sessionResources (sessionID, resourceID) VALUES ('" + sessionID + "', '" + stmt + "');";
		database->exec(stmt.c_str());

		return new Location(id.c_str(), location);
	}
	Equipment* regesterEquipment(const char* sessionID, Equipment::EquipmentType resource) {
		// Need to implement sql query
		// regesterEquipment will query database, filter out equipment in use that matches the day of the session (joins on the relations event/session and session/equipment), and returns the first available equipment of the specified type then updates the relation table
		std::string id = uuidGenerator->getUUID().str();
		Equipment* ret = new Equipment(id.c_str(), resource);
		return ret;
	}

private:
	SQLite::Database* database;
	UUIDv4::UUIDGenerator<std::mt19937_64>* uuidGenerator;
};