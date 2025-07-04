#include "../include/Flight.hpp"
#include <iostream>
#include <sstream>

// Constructors
Flight::Flight(){};
Flight::Flight(std::string code, std::string origin, std::string destination, Airplane* airplane, Pilot* pilot, Pilot* copilot) {
   this->code = code;
   this->origin = origin;
   this->destination = destination;
   this->airplane = airplane;
   this->pilot = pilot;
   this->copilot = copilot;
}

// Destructors
Flight::~Flight() {
    for (Passenger* passenger: passengers)
        delete passenger;
}

// Setters
void Flight::setAirplane(Airplane* airplane) {
    this->airplane = airplane;
}
void Flight::setPilot(Pilot* pilot) {
    this->pilot = pilot;
}
void Flight::setCopilot(Pilot* copilot) {
    this->copilot = copilot;
}
void Flight::setCode(const std::string code) {
    this->code = code;
}
void Flight::setArrivalDate(const std::string arrivalDate) {
    this->arrivalDate = arrivalDate;
}
void Flight::setDepartureDate(const std::string departureDate) {
    this->departureDate = departureDate;
}
void Flight::setDestination(const std::string destination) {
    this->destination = destination;
}
void Flight::setOrigin(const std::string origin) {
    this->origin = origin;
}
void Flight::setDistance(const std::string distance) {
    this->distance = distance;
}

// Getters
Airplane* Flight::getAirplane() const {
    return this->airplane;
}
Pilot* Flight::getPilot() const {
    return this->pilot;
}
Pilot* Flight::getCopilot() const {
    return this->copilot;
}
float Flight::getEstimatedDuration() const{
    return this->estimatedDuration;
}
int Flight::getScalesNumber() const {
    return this->scalesNumber;
}

std::string Flight::getOrigin() const {
    return this->origin;
}
std::string Flight::getDestination() const {
    return this->destination;
}
std::string Flight::getArrivalDate() const {
    return this->arrivalDate;
}
std::string Flight::getDepartureDate() const {
    return this->departureDate;
}
std::string Flight::getDistance() const {
    return this->distance;
}
std::vector<Passenger*> Flight::getPassengers() const {
    return this->passengers;
}
std::string Flight::getCode() const {
    return this->code;
}

// Methods
bool Flight::addPassenger(Passenger* newPassenger) {
    // Checks if can't add New passenger because of capacity
    if ((int)this->passengers.size() + 1 > this->airplane->getCapacity()) {
        std::cout << "Impossível embarcar um novo passageiro: Capacidade Máxima Excedida!" << std::endl;
        return false;
    }

    // Check if passenger is already in Flight
    for (Passenger* passenger : passengers) {
        if (passenger->getCPF() == newPassenger->getCPF()) {
            std::cout << "Passageiro " << newPassenger->getName() << " já está a bordo deste Voo!" << std::endl;
            return false;
        }
    }
    this->passengers.push_back(newPassenger); return true;
}


float Flight::calculateAndSetDuration() {
    float velocity = this->airplane->getMediumVelocity();
    float distance = std::stof(this->distance);
    float duration = (distance/velocity);
    duration += this->scalesNumber;

    this->estimatedDuration = duration;
    return this->estimatedDuration;

    return 0;
}

int Flight::calculateAndSetScalesNumber(){
    float autonomy = this->airplane->getAutonomy();
    if (autonomy <= 0) throw std::runtime_error("Autonomy must be positive!");

    float distance = std::stof(this->distance);
    float scales = distance/autonomy;

    // Rounds up if has a decimal portion != 0
    if (scales / ((int) scales) != 1)
        scales++;

    this->scalesNumber = (int) scales - 1;
    return this->scalesNumber;
}

std::string Flight::serializer() const {
    std::ostringstream oss;
    oss << this->airplane->serializer() << ","
        << this->airplane->getCode() << ","
        << this->departureDate << ","
        << this->scalesNumber << ","
        << this->estimatedDuration<< ","
        << this->pilot->serializer() << ","
        << this->copilot->serializer() << ",";

    for (Passenger* p: passengers)
        oss << p->getCPF() << ",";

    return oss.str();
}

void Flight::showData() const {
    std::cout << "Código do voo: " << this->code << std::endl;
    std::cout << "Código da Aeronave: " << this->airplane->getCode() << std::endl;
    std::cout << "Modelo da Aeronave: " << this->airplane->getModel() << std::endl;
    std::cout << "Matricula do Comandante: " << this->pilot->getRegistration() << std::endl;
    std::cout << "Origem: " << this->origin << std::endl;
    std::cout << "Destino: " << this->destination << std::endl;
    std::cout << "Numero de Passageiros: " << this->passengers.size() << std::endl;
    std::cout << "Data e Hora de saída: " << this->departureDate << std::endl;
    std::cout << "Data e Hora de chegada: " << this->arrivalDate << std::endl;

}
