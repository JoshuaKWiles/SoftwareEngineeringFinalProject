#pragma once
#include "uuid_v4.h"
#include "SQLiteCpp.h"

#include <string>

struct Guest{
	const std::string guestID;
	const std::string name;

	Guest(const Guest& guest) : name(guest.name), guestID(guest.guestID) { }
	Guest(const std::string& gusetName, const std::string& guestID) : name(gusetName), guestID(guestID) { }
};
struct Presenter : public Guest{
	const std::string presenterID;

	Presenter(const Guest& guest, const std::string& presenterID) : Guest(guest), presenterID(presenterID) { }
	Presenter(const Presenter& presenter) : Guest(presenter.name, presenter.guestID), presenterID(presenter.presenterID) { }
	Presenter(const std::string& name, const std::string& guestID, const std::string& presenterID) : Guest(name, guestID), presenterID(presenterID) { }
};
