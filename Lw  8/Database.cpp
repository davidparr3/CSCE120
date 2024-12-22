# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
Database::Database() : stateParkList(), camperList() {}

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	// TODO: implement function
	StatePark* newpark = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(newpark);
	return;
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function
	Passport* newpassport = new Passport(camperName, isJuniorPassport);
	camperList.push_back(newpassport);
	return;
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)
	bool Visited1, Visited2;
	Passport* camper = nullptr;
	StatePark* park = nullptr;

	// TODO: implement function
	for(size_t i = 0; i < camperList.size(); i++){
		if((camperList[i]->getCamperName()) == camperName){
			Visited1 = true;
			camper = camperList[i];
		}
	}

	for(size_t i = 0; i < stateParkList.size(); i++){
		if((stateParkList[i]->getParkName()) == parkName){
			Visited2 = true;
			park = stateParkList[i];
		}
	}

	if(Visited1 && Visited2){
		camper -> addParkVisited(park);
	}

	return;
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
