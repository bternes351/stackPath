#include "gas_station.h"
#include "car.h"
#include "pump.h"

#include <iostream>


GasStation::GasStation() {    
    this->numCars = 10;
    this->numPumps = 2;
    this->totalNumFillups = 0;
    this->stationQueue = std::queue<Car*>();
    this->threadPool = std::vector<boost::thread>();
    this->destroyThread = false;

    for(int i = 0; i < this->numPumps; i++){
        this->pumps.push_back(new Pump());
    }
};

GasStation::~GasStation() {
    while (!this->stationQueue.empty()){
        this->stationQueue.pop();
    }

    while(!this->pumps.empty()){
        this->pumps.pop_back();
    }
}

bool GasStation::hasEmptyPump(){    
    bool emptyPumps = false;
    for(int i = 0; i < this->pumps.size(); i++){
        if (this->pumps[i]->isEmpty()){
            emptyPumps = true;
            break;
        }
    }
    return emptyPumps;
}

void GasStation::initStationQueue() {
    std::unique_lock<boost::mutex> lck(this->m);
    for (int i = 0; i < this->numCars; i++) {
        Car *pCar = new Car();        
        this->stationQueue.push(pCar);
        this->threadPool.push_back(boost::thread(Car::thread_loop, std::ref(*this), std::ref(*pCar)));        
        
    }
}

void GasStation::putCarAtPump(Car* inCar) {
    std::unique_lock<boost::mutex> lck(this->m);        
    for (int i = 0; i < this->pumps.size(); i++) {
        if (this->pumps[i]->isEmpty()){
            this->pumps[i]->setCar(inCar);
            this->stationQueue.pop();
            break;
        }
    }
}

void GasStation::clearPump(Car& inCar){
    std::unique_lock<boost::mutex> lck(this->m);    
    for(int i = 0; i < this->pumps.size(); i++){
        if(&inCar == this->pumps[i]->getPumpCar()){
            this->pumps[i]->fillup();
            Car *pCar = this->pumps[i]->getPumpCar();
            this->stationQueue.push(pCar);
            this->pumps[i]->setCar(nullptr);
            break;
        }    
    }


}

void GasStation::destroyStation() {     
    {
        std::unique_lock<boost::mutex> lck(this->m);    
        this->destroyThread = true;    
    }
    while(!this->threadPool.empty()){
        boost::thread &t = this->threadPool.back();           
        t.join();
        this->threadPool.pop_back();
    }

    for (int i = 0; i < this->pumps.size(); i++){
        if (this->pumps[i]->getPumpCar() != nullptr)
        {
            Car* pCar = this->pumps[i]->getPumpCar();                    
            this->stationQueue.push(pCar);
            this->pumps[i]->setCar(nullptr);
        }        
    }
}

void GasStation::printTotalFillsForCars(){
    std::cout << "Fillups per car" << std::endl;
    std::cout << "Number of cars in queue: " << this->stationQueue.size() << std::endl;
    while(!this->stationQueue.empty()){
        Car *car = this->stationQueue.front();
        std::cout << car->getNumFillups() << std::endl;
        this->stationQueue.pop();

    }    
}

void GasStation::printTotalFillsForPumps(){
    std::cout << "Fillups per pump" << std::endl;
    for (int i = 0; i < this->pumps.size(); i++) {
        std::cout << this->pumps[i]->getNumFillUps() << std::endl;
    }
}

Car* GasStation::getFrontCar() {
    std::unique_lock<boost::mutex> lck(this->m);
    return this->stationQueue.front();
}