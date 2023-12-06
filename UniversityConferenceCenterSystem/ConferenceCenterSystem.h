#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <exception>
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
	
};

ConferenceManager* ConferenceManager::instance = NULL;