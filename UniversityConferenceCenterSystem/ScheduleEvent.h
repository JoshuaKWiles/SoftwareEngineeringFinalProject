#pragma once
#include "ConferenceCenterSystem.h"

#include <string>
#include <vector>
class ScheduleEvent {
public:
	ScheduleEvent(const char* id, const char* name_) : scheduleID(id), name(name_) {}

	virtual long double getCost() = 0;
	virtual std::string getSchedule() = 0;
	virtual std::vector<Presenter> getPresenter() = 0;

	const std::string scheduleID;
	const std::string name;
};

class Session : public ScheduleEvent {
public:
	Session(const char* id, const char* name_, Location::RoomType room, const char* start, const char* end) : ScheduleEvent(id, name_), location(ConferenceManager::getInstance()->resourceManager->regesterLocation(id, room)), startTime(start), endTime(end) { }
	~Session() {
		delete location;
		for (auto resource : equipmentList) delete resource;
	}

	const std::string startTime;
	const std::string endTime;
	Location* const location;

	long double getCost() {
		long double total = location->getCost();
		if(!equipmentList.empty())
			for (auto resource : equipmentList) total += resource->getCost();
		return total;
	}

	std::string getSchedule() { return '(' + startTime + " - " + endTime + ')'; }
	std::vector<Presenter> getPresenter() {
		std::vector<Presenter> ret;
		// Need to implement sql query
		//getPresenter will query the database and return all presenter associated with the session id
		return ret;
	}

	void addResource(Equipment::EquipmentType resource) {
		equipmentList.push_back(ConferenceManager::getInstance()->resourceManager->regesterEquipment(scheduleID.c_str(), resource));
	}
	std::vector<Equipment const*> getResources() {
		std::vector<Equipment const*> ret;
		if (!equipmentList.empty())
			for (auto equipment : equipmentList) ret.push_back(equipment);
		return ret;
	}

	// reprotResources is an alternate take on getResources
	std::string reportResources() {
		std::string ret = "";
		if (!equipmentList.empty()) {
			for (auto equipment : equipmentList) {
				ret.append(equipment->getName());
				ret.push_back(' ');
			}
			if (ret.back() == ' ') ret.pop_back();
		}
		else ret = "No Equipment Used.";
		return ret;
	}

private:
	std::vector<Equipment*> equipmentList;
};

class Event : public ScheduleEvent {
public:
	Event(const char* id, const char* name, const char* date_) : ScheduleEvent(id, name), date(date_) {}

	long double getCost() { return 0.0l; }
	

	const std::string date;
private:

};

class EventManager {
public:
	EventManager(SQLite::Database* db, UUIDv4::UUIDGenerator<std::mt19937_64>* generator) : database(db), uuidGenerator(generator) {}

private:
	SQLite::Database* database;
	UUIDv4::UUIDGenerator<std::mt19937_64>* uuidGenerator;
};