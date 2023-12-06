#pragma once
#include "ConferenceCenterSystem.h"
#include "Resource.h"
#include "Guest.h"

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

	long double getCost() {
		long double total = location->getCost();
		for (auto resource : equipmentList) total += resource->getCost();
		return total;
	}

	std::string getSchedule() { return "(" +startTime + " - " + endTime + ")"; }
	std::vector<Presenter> getPresenter() {}

	void addResource(Equipment::EquipmentType resource) {
		equipmentList.push_back(ConferenceManager::getInstance()->resourceManager->regesterEquipment(scheduleID.c_str(), resource));
	}
private:
	Location* const location;
	std::vector<Equipment*> equipmentList;
};