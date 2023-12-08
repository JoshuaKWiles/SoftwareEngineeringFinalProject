#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <exception>
#include <iostream>
#include <string>
#include <format>

#include "Resource.h"
#include "Guest.h"

class ResourceManager {
public:
	ResourceManager(SQLite::Database* db, UUIDv4::UUIDGenerator<std::mt19937_64>* generator) : database(db), uuidGenerator(generator) {}
	Location* regesterLocation(const std::string& sessionID, const Location::RoomType& location) {
		std::string stmt = typeName(location);

		stmt = "SELECT resourceID FROM resources WHERE type ='" + stmt + "';";
		stmt = database->execAndGet(stmt.c_str()).getString();

		std::string id = stmt;

		stmt = "INSERT INTO sessionResources (sessionID, resourceID) VALUES ('" + sessionID + "', '" + stmt + "');";
		database->exec(stmt.c_str());

		return new Location(id.c_str(), location);
	}
	Location::RoomType room(const std::string& id) {
		std::string stmt = "SELECT type FROM resources WHERE resourceID='" + id + "';";
		return typeLocation(database->execAndGet(stmt.c_str()).getText());
	}
	std::string roomID(const Location::RoomType& room) {
		std::string stmt = "SELECT resourceID FROM resources WHERE type='" + typeName(room) + "';";
		return database->execAndGet(stmt.c_str()).getText();
	}

	const std::string addEquipment(const Equipment::EquipmentType& resource) {
		std::string stmt = typeName(resource), id = uuidGenerator->getUUID().str();
		stmt = "INSERT INTO resources(resourceID, type) VALUES ('" + id + "', '" + stmt + "')";
		database->exec(stmt.c_str());
		return id;
	}
	Equipment::EquipmentType type(const std::string& id) {
		std::string stmt = "SELECT type FROM resources WHERE resourceID='" + id + "';";
		return typeEquipment(database->execAndGet(stmt.c_str()).getText());
	}
	Equipment* instance(const std::string& id) {
		return new Equipment(id, type(id));
	}
	Equipment* regesterEquipment(const std::string& sessionID, const Equipment::EquipmentType& resource) { return nullptr; }

	void reportResources() const {
		SQLite::Statement stmt(*database, "SELECT * FROM RESOURCES;");
		std::cerr << "Resources Table:\n";
		while (stmt.executeStep())
			std::cerr << stmt.getColumn(0).getText() << '\t' << stmt.getColumn(1) << '\n';
		std::cerr << std::endl;
	}

private:

	SQLite::Database* database;
	UUIDv4::UUIDGenerator<std::mt19937_64>* uuidGenerator;
};

class GuestManager {
public:

private:

};

class EventManager {
public:
	EventManager(SQLite::Database* db, UUIDv4::UUIDGenerator<std::mt19937_64>* generator) : database(db), uuidGenerator(generator) {}
	std::string newSession(const std::string& name, const std::string& start, const std::string& end) {
		std::string id = uuidGenerator->getUUID().str();
		std::string stmt = "INSERT INTO sessions (sessionID, name, startTime, endTime, isSpecalSession) VALUES('" + id + "', '" + name + "', '" + start + "', '" + end + "', 0);";
		database->exec(stmt.c_str());
		return id;
	}
	std::string sessionName(const std::string& id) const {
		std::string stmt = "SELECT name FROM sessions WHERE sessionID='" + id + "';";
		return database->execAndGet(stmt.c_str()).getString();
	}
	std::string sessionStart(const std::string& id) const {
		std::string stmt = "SELECT startTime FROM sessions WHERE sessionID='" + id + "';";
		return database->execAndGet(stmt.c_str()).getString();
	}
	std::string sessionEnd(const std::string& id) const {
		std::string stmt = "SELECT endTime FROM sessions WHERE sessionID='" + id + "';";
		return database->execAndGet(stmt.c_str()).getString();
	}
	Location* sessionLocation(const std::string& id) const {
		std::string stmt = "SELECT resources.resourceID, resources.type FROM sessionResources JOIN resources ON sessionResources.resourceID = resources.resourceID WHERE sessionResources.sessionID='" + id + "' AND type IN ('Roosevelt', 'Lincoln', 'Washington');";
		SQLite::Statement select(*database, stmt.c_str());
		select.executeStep();
		return new Location(select.getColumn(0).getString(), typeLocation(select.getColumn(1).getString()));
	}
private:
	SQLite::Database* database;
	UUIDv4::UUIDGenerator<std::mt19937_64>* uuidGenerator;
};

class ConferenceManager {
private:
	static ConferenceManager* instance;

	SQLite::Database db;
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	ConferenceManager() : db(SQLite::Database("ConferenceCenter.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE, 1, NULL)),
						  resourceManager(new ResourceManager(&db, &uuidGenerator)),
						  eventManager(new EventManager(&db, &uuidGenerator))
							{ std::atexit(&Destructor); }
	~ConferenceManager() {
		delete resourceManager;
		delete eventManager;
	}

	static void Destructor() {
		delete instance;
		instance = NULL;
	}

	ConferenceManager(const ConferenceManager&) = delete;
	ConferenceManager* operator = (const ConferenceManager&) = delete;

public:
	ResourceManager* const resourceManager;
	EventManager* const eventManager;
	

	static ConferenceManager* getInstance() {
		if (instance == NULL) instance = new ConferenceManager();
		return instance;
	}

	void init() {
		db.exec("CREATE TABLE IF NOT EXISTS events(eventID TEXT PRIMARY KEY, name TEXT NOT NULL, date TEXT NOT NULL);");
		db.exec("CREATE TABLE IF NOT EXISTS sessions(sessionID TEXT PRIMARY KEY, name TEXT NOT NULL, startTime TEXT NOT NULL, endTime TEXT NOT NULL, isSpecalSession INTEGER NOT NULL);");
		db.exec("CREATE TABLE IF NOT EXISTS resources(resourceID TEXT PRIMARY KEY, type TEXT NOT NULL);");
		db.exec("CREATE TABLE IF NOT EXISTS guests(guestID TEXT PRIMARY KEY, name TEXT NOT NULL);");

		// Relation Tables
		db.exec("CREATE TABLE IF NOT EXISTS eventSessions(eventID TEXT NOT NULL, sessionID NOT NULL, PRIMARY KEY (eventID, sessionID));");
		db.exec("CREATE TABLE IF NOT EXISTS sessionResources(sessionID TEXT NOT NULL, resourceID TEXT NOT NULL, PRIMARY KEY (sessionID, resourceID));");
		db.exec("CREATE TABLE IF NOT EXISTS eventGuests(eventID TEXT NOT NULL, guestID TEXT NOT NULL, PRIMARY KEY (eventID, guestID));");
		db.exec("CREATE TABLE IF NOT EXISTS specalSessionGuests(sessionID TEXT NOT NULL, guestID TEXT NOT NULL, PRIMARY KEY (sessionID, guestID));");
		db.exec("CREATE TABLE IF NOT EXISTS presenters(guestID TEXT NOT NULL, sessionID TEXT NOT NULL, PRIMARY KEY (guestID, sessionID));");

		// Add Confrence Rooms to db
		if (db.execAndGet("SELECT COUNT(resourceID) FROM resources WHERE type='Roosevelt';").getInt() == 0) {
			std::string stmt = uuidGenerator.getUUID().str();
			stmt = "INSERT INTO resources (resourceID, type) VALUES ('" + stmt + "', 'Roosevelt');";
			db.exec(stmt.c_str());
		}
		if (db.execAndGet("SELECT COUNT(resourceID) FROM resources WHERE type='Lincoln';").getInt() == 0) {
			std::string stmt = uuidGenerator.getUUID().str();
			stmt = "INSERT INTO resources (resourceID, type) VALUES ('" + stmt + "', 'Lincoln');";
			db.exec(stmt.c_str());
		}
		if (db.execAndGet("SELECT COUNT(resourceID) FROM resources WHERE type='Washington';").getInt() == 0) {
			std::string stmt = uuidGenerator.getUUID().str();
			stmt = "INSERT INTO resources (resourceID, type) VALUES ('" + stmt + "', 'Washington');";
			db.exec(stmt.c_str());
		}
		
		//Print All Table Names
		//SQLite::Statement check(db, "SELECT name FROM sqlite_schema WHERE type='table' AND name NOT LIKE 'sqlite_%';");
		//while(check.executeStep())
		//	std::cerr << check.getColumn(0) << std::endl;
	}
};

ConferenceManager* ConferenceManager::instance = NULL;

//Additional Constructors
Location::Location(const std::string& id) : Resource(id), room(ConferenceManager::getInstance()->resourceManager->room(id)) {}
Location::Location(const Location::RoomType& hostRoom) : Resource(ConferenceManager::getInstance()->resourceManager->roomID(hostRoom)), room(hostRoom) {}
Equipment::Equipment(const std::string& id) : Resource(id), what(ConferenceManager::getInstance()->resourceManager->type(id)) {}
Equipment::Equipment(const EquipmentType& type) : Resource(ConferenceManager::getInstance()->resourceManager->addEquipment(type)), what(type) { }