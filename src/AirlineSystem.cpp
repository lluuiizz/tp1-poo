#include "../include/AirlineSystem.hpp"
#include <iostream>

// Nothing in constructor because The system will increase
// with user input
AirlineSystem::AirlineSystem(){
    std::cout << "INFO: Construido O sistema de Linhas Aereas" << std::endl;
}

// Destroying every element from the vectors
AirlineSystem::~AirlineSystem() {
    for (Airplane* airplane: airplanes)
        delete airplane;
    for (Pilot* pilot: pilots)
        delete pilot;
    for (Passenger* passenger: passengers)
        delete passenger;

    for (Flight* flight: flights_avaibles){
        flight->~Flight();
        delete flight;
    }
}

Airplane* AirlineSystem::getAirplane(std::string cod) {
    for (Airplane* airplane: airplanes) {
        if (cod == airplane->getCode())
            return airplane;
    }
    return NULL;
}
Pilot* AirlineSystem::getPilot(std::string licenseNumber){
    for (Pilot* pilot: pilots){
        if (licenseNumber == pilot->getLicense())
            return pilot;
    }
    return NULL;

}
Passenger* AirlineSystem::getPassenger(std::string cpf) {
    for (Passenger* passenger: passengers){
        if (cpf == passenger->getCPF())
            return passenger;
    }
    return NULL;

}
Flight* AirlineSystem::getFlight(std::string code) {
    for (Flight* flight : flights_avaibles) {
        if (flight->getCode() == code)
            return flight;
    }
    return NULL;
}

int AirlineSystem::getNumOfPassengers(void) {
    return this->passengers.size();
}

// The plane in newAirplane only gets here after is created
// in the Menu, so there is not really a way to have a invalid
// Airplane at this point, because the Menu would not let this
// But just to be sure we check if the pointer is not NULL

bool AirlineSystem::registerNewAirplane(Airplane* newAirplane) {
    if (newAirplane == NULL)
        return false;
    this->airplanes.push_back(newAirplane); return true;
}
bool AirlineSystem::registerNewPilot(Pilot* newPilot) {
    if (newPilot == NULL)
        return false;

    this->pilots.push_back(newPilot); return true;
}
bool AirlineSystem::registerNewPassenger(Passenger* newPassenger){
    if (newPassenger == NULL)
        return false;

    this->passengers.push_back(newPassenger); return true;
}
bool AirlineSystem::registerNewFlight(Flight* newFlight) {
    if (newFlight == NULL)
        return false;

    this->flights_avaibles.push_back(newFlight); return true;
}


void AirlineSystem::showAirplanes(void) {
    for (Airplane* airplane: airplanes) {
        airplane->showDetails();
        std::cout << std::endl << std::endl;
    }
}
void AirlineSystem::showPilots(void) {
    for (Pilot* pilot: pilots) {
        pilot->displayInfo();
        std::cout << std::endl << std::endl;
    }
}
void AirlineSystem::showPassengers(void) {
     for (Passenger* passenger: passengers) {
        passenger->displayInfo();
        std::cout << std::endl << std::endl;
    }
}
void AirlineSystem::showFlightsAvaibles(void) {
    for (Flight* flight: flights_avaibles) {
        flight->showData();
        std::cout <<  "================================="<< std::endl << std::endl;
    }
}
std::vector<std::string> AirlineSystem::serializeAirplanes(void) {

    std::vector<std::string> serialization;
    for (Airplane* ap : this->airplanes) {
        serialization.push_back(ap->serializer());
    }

    return serialization;
}
std::vector<std::string>AirlineSystem::serializePeople(void) {
    std::vector<std::string> serialization;
    for (Pilot* p : pilots)
        serialization.push_back(p->serializer());
    for (Passenger* p: passengers)
        serialization.push_back(p->serializer());

    return serialization;
}
std::vector<std::string>AirlineSystem::serializeFlights(void) {
    std::vector<std::string> serialization;
    for (Flight* f: flights_avaibles)
        serialization.push_back(f->serializer());

    return serialization;
}
