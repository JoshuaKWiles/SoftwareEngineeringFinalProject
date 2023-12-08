#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <exception>
#include <iostream>
#include <string>
#include <format>

#include "Resource.h"

class ConferenceManager {
private:
	static ConferenceManager* instance;

	SQLite::Database db;
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	ConferenceManager() : db(SQLite::Database("ConferenceCenter.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE, 1, NULL)), resourceManager(new ResourceManager(&db, &uuidGenerator)) { std::atexit(&Destructor); }
	~ConferenceManager() {
		delete resourceManager;
	}

	static void Destructor() {
		delete instance;
		instance = NULL;
	}

	ConferenceManager(const ConferenceManager&) = delete;
	ConferenceManager* operator = (const ConferenceManager&) = delete;

public:
	ResourceManager* const resourceManager;

	static ConferenceManager* getInstance() {
		if (instance == NULL) instance = new ConferenceManager();
		return instance;
	}

	void init() {
		db.exec("CREATE TABLE IF NOT EXISTS event(eventID TEXT PRIMARY KEY, name TEXT NOT NULL, date TEXT NOT NULL);");
		db.exec("CREATE TABLE IF NOT EXISTS session(sessionID TEXT PRIMARY KEY, name TEXT NOT NULL, startTime TEXT NOT NULL, endTime TEXT NOT NULL, isSpecalSession TEXT NOT NULL);");
		db.exec("CREATE TABLE IF NOT EXISTS resource(resourceID TEXT PRIMARY KEY, type TEXT NOT NULL);");
		db.exec("CREATE TABLE IF NOT EXISTS guest(guestID TEXT PRIMARY KEY, name TEXT NOT NULL);");

		db.exec("PRAGMA foreign_keys = ON;");

		// Relation Tables
		db.exec("CREATE TABLE IF NOT EXISTS eventSessions(eventID TEXT NOT NULL, sessionID NOT NULL, PRIMARY KEY (eventID, sessionID), FOREIGN KEY (eventID) REFERENCES event (eventID), FOREIGN KEY (sessionID) REFERENCES session (sessionID));");
		db.exec("CREATE TABLE IF NOT EXISTS sessionResources(sessionID TEXT NOT NULL, resourceID TEXT NOT NULL, PRIMARY KEY (sessionID, resourceID), FOREIGN KEY (sessionID) REFERENCES session (sessionID), FOREIGN KEY (resourceID) REFERENCES resource (resourceID));");
		db.exec("CREATE TABLE IF NOT EXISTS eventGuests(eventID TEXT NOT NULL, guestID TEXT NOT NULL, PRIMARY KEY (eventID, guestID), FOREIGN KEY (eventID) REFERENCES event (eventID), FOREIGN KEY (guestID) REFERENCES guest (guestID));");
		db.exec("CREATE TABLE IF NOT EXISTS specalSessionGuests(sessionID TEXT NOT NULL, guestID TEXT NOT NULL, PRIMARY KEY (sessionID, guestID), FOREIGN KEY (sessionID) REFERENCES session (sessionID), FOREIGN KEY (guestID) REFERENCES guest (guestid));");
		db.exec("CREATE TABLE IF NOT EXISTS presenters(guestID TEXT NOT NULL, sessionID TEXT NOT NULL, PRIMARY KEY (guestID, sessionID), FOREIGN KEY (guestID) REFERENCES guest (guestID), FOREIGN KEY (sessionID) REFERENCES session (sessionID));");

		//Print All Table Names
		//SQLite::Statement check(db, "SELECT name FROM sqlite_schema WHERE type='table' AND name NOT LIKE 'sqlite_%';");
		//while(check.executeStep())
		//	std::cerr << check.getColumn(0) << std::endl;
	}
};

ConferenceManager* ConferenceManager::instance = NULL;