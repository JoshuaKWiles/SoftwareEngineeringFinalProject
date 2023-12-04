#pragma once
#include <exception>
#include <string>
#include <format>
#include "uuid_v4.h"
#include "SQLiteCpp.h"
class ConferenceManager {
private:
	static ConferenceManager* instance;

	SQLite::Database db;
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	ConferenceManager() : db(SQLite::Database("ConferenceCenter.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE, 1, NULL)) { std::atexit(&Destructor); }
	static void Destructor() {
		delete instance;
		instance = NULL;
	}

	ConferenceManager(const ConferenceManager&) = delete;
	ConferenceManager* operator = (const ConferenceManager&) = delete;

	class ResourceManager {
	private:
		SQLite::Database& db;
	protected:
		void newResource(const char* uuid, const char* type) {
			std::string script = std::format("INSERT INTO resource (resourceID, type) VALUES ('{}', '{}');", uuid, type);
			SQLite::Statement stmt(db, script.c_str());
			stmt.exec();
		}
	public:
		ResourceManager(SQLite::Database& database) : db(database) {}
	};
	class LocationManager : public ResourceManager {
		
	};
public:
	static ConferenceManager* getInstance() {
		if (instance == NULL) instance = new ConferenceManager();
		return instance;
	}
	void init() {
		std::string script;
		std::string uuid = uuidGenerator.getUUID().str();
		//script = "DROP TABLE resource";
		//script = "CREATE TABLE resource (id INTEGER AUTOINCREMENT, resourceID TEXT UNIQUE, type TEXT)";
		//script = std::format("INSERT INTO resource(resourceID, type) VALUES ('{}', 'Roosevelt'); ", uuid.c_str());
		//script = std::format("INSERT INTO resource(resourceID, type) VALUES ('{}', 'Lincoln'); ", uuid.c_str());
		//script = std::format("INSERT INTO resource(resourceID, type) VALUES ('{}', 'Washington'); ", uuid.c_str());
		SQLite::Statement stmt(db, script.c_str());
		stmt.exec();
	}
};

ConferenceManager* ConferenceManager::instance = NULL;