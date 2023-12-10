#pragma once
#include "ConferenceCenterSystem.h"
#include <exception>
#include <cassert>
#include <string>
#include <vector>
class ScheduleEvent {
public:
	ScheduleEvent(const std::string& id, const std::string& name_) : scheduleID(id), name(name_) {}

	virtual std::string getSchedule() const = 0;
	virtual std::vector<Presenter*> getPresenter() const = 0;

	const std::string scheduleID;
	const std::string name;
};

class Session : public ScheduleEvent {
public:
	Session(const std::string& eventID, const std::string& name_, const Location::RoomType room, const std::string& start, const std::string& end) :
					ScheduleEvent(ConferenceManager::getInstance()->eventManager->newSession(eventID, name_,start, end), name_),
					location(ConferenceManager::getInstance()->resourceManager->regesterLocation(scheduleID, room)),
					startTime(start),
					endTime(end)
					{ }

	Session(const std::string& sessionID) :
					ScheduleEvent(sessionID, ConferenceManager::getInstance()->eventManager->sessionName(sessionID)),
					location(ConferenceManager::getInstance()->eventManager->sessionLocation(sessionID)),
					equipmentList(ConferenceManager::getInstance()->eventManager->equipmentList(sessionID)),
					startTime(ConferenceManager::getInstance()->eventManager->sessionStart(sessionID)),
					endTime(ConferenceManager::getInstance()->eventManager->sessionEnd(sessionID))
					{ }
	
	~Session() {
		delete location;
		for (auto resource : equipmentList) delete resource;
	}

	const std::string startTime;
	const std::string endTime;
	Location* const location;

	std::string getSchedule() const { return '(' + startTime + " - " + endTime + ')'; }
	std::vector<Presenter*> getPresenter() const {
		std::vector<Presenter*> ret;
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

class SpecialSession : public Session {
public:
	SpecialSession(const std::string& eventID, const std::string& name_, const Location::RoomType room, const std::string& start, const std::string& end, const long double& charge_) :
							Session(eventID, name_, room, start, end),
							charge(charge_)
							{ 
								ConferenceManager::getInstance()->eventManager->registerSpecialSession(scheduleID, charge);
							}
	SpecialSession(const std::string& sessionID) :
							Session(sessionID),
							charge(ConferenceManager::getInstance()->eventManager->getSpeicalSessionCharge(sessionID))
							{ }

	const long double charge;
private:

};

class Event : public ScheduleEvent {
public:
	Event(const std::string& name_, const std::string& date_, const long double& charge_) :
					ScheduleEvent(ConferenceManager::getInstance()->eventManager->newEvent(name_, date_, charge_), name_),
					date(date_),
					charge(charge_)
					{ }
	Event(const std::string& eventID) :
					ScheduleEvent(eventID, ConferenceManager::getInstance()->eventManager->eventName(eventID)),
					date(ConferenceManager::getInstance()->eventManager->eventDate(eventID)),
					charge(ConferenceManager::getInstance()->eventManager->getCharge(eventID))
					{
						std::vector<std::string> sessionList = ConferenceManager::getInstance()->eventManager->getSessions(eventID);
						for (int i = 0; i < (6 < sessionList.size() ? 6 : sessionList.size()); i++)
							if (i < 4) sessions[i] = new Session(sessionList.at(i));
							else if (i >= 4 && i < 6) sessions[i] = new SpecialSession(sessionList.at(i));
					}
	~Event() {
		for (int i = 0; i < 4; i++)
			if (sessions[i] != nullptr) delete sessions[i];
	}

	long double getCost() const { return 0.0l; }
	std::string getSchedule() const { 
		std::string schedule = date + '\n';
		for (int i = 0; i < 4; i++)
			if (sessions[i] != nullptr) schedule += sessions[i]->name + ": " + sessions[i]->getSchedule() + '\n';
		return schedule;
	}
	std::vector<Presenter*> getPresenter() const {
		std::vector<Presenter*> ret;
		return ret;
	}
	void newSession(const unsigned short sessionNo, const std::string& name_, const Location::RoomType room, const std::string& start, const std::string& end) {
		assert(sessionNo == 1 || sessionNo == 2 || sessionNo == 3 || sessionNo == 4);
		if (sessions[sessionNo - 1] == nullptr)
			sessions[sessionNo - 1] = new Session(scheduleID, name_, room, start, end);
		else throw std::domain_error("Session alrady exists. Select a diffrent session number.");
	}
	void newSpecialSession(const unsigned short sessionNo, const std::string& name_, const Location::RoomType room, const std::string& start, const std::string& end, const long double& extraCharge) {
		assert(sessionNo == 5 || sessionNo == 6);
		if (sessions[sessionNo - 1] == nullptr)
			sessions[sessionNo - 1] = new SpecialSession(scheduleID, name_, room, start, end, extraCharge);
		else throw std::domain_error("Session alrady exists. Select a diffrent session number.");
	}
	Session* session(const unsigned short sessionNo) {
		assert(sessionNo == 1 || sessionNo == 2 || sessionNo == 3 || sessionNo == 4 || sessionNo == 5 || sessionNo == 6);
		return sessions[sessionNo - 1];
	}
	const std::string date;
	const long double charge;
private:
	Session* sessions[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
};