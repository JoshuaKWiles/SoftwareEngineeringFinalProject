#pragma once
#include "ConferenceCenterSystem.h"

#include <string>
#include <vector>
class ScheduleEvent {
public:
	ScheduleEvent(const std::string& id, const std::string& name_) : scheduleID(id), name(name_) {}

	virtual long double getCost() const = 0;
	virtual std::string getSchedule() const = 0;
	virtual std::vector<Presenter> getPresenter() const = 0;

	const std::string scheduleID;
	const std::string name;
};

class Session : public ScheduleEvent {
public:
	Session(const std::string& name_, Location::RoomType room, const std::string& start, const std::string& end) : 
					ScheduleEvent(ConferenceManager::getInstance()->eventManager->newSession(name_,start, end), name_), 
					location(ConferenceManager::getInstance()->resourceManager->regesterLocation(scheduleID, room)), 
					startTime(start), 
					endTime(end) 
					{ }

	Session(const std::string& id) :
					ScheduleEvent(id, ConferenceManager::getInstance()->eventManager->sessionName(id)),
					location(ConferenceManager::getInstance()->eventManager->sessionLocation(id)),
					startTime(ConferenceManager::getInstance()->eventManager->sessionStart(id)),
					endTime(ConferenceManager::getInstance()->eventManager->sessionEnd(id))
					{ }
	
	~Session() {
		delete location;
		for (auto resource : equipmentList) delete resource;
	}

	const std::string startTime;
	const std::string endTime;
	Location* const location;

	long double getCost() const {
		long double total = location->getCost();
		if(!equipmentList.empty())
			for (auto resource : equipmentList) total += resource->getCost();
		return total;
	}

	std::string getSchedule() const { return '(' + startTime + " - " + endTime + ')'; }
	std::vector<Presenter> getPresenter() const {
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
	std::string reportResources() const {
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