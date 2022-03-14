#include "pump.h"

Pump::Pump(){
    this->pCar = nullptr;
    this->numFillups = 0;
}

void Pump::fillup(){
    this->numFillups +=1;
}

int Pump::getNumFillUps() {
    return this->numFillups;
}

bool Pump::isEmpty(){
    return this->pCar == nullptr;
}

Car* Pump::getPumpCar(){
    return this->pCar;
}

void Pump::setCar(Car* inCar) {
    this->pCar = inCar;
}