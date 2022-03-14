#include "car.h"
#include "gas_station.h"

#include <boost/thread.hpp>

Car::Car() {         
    this->numFillups = 0;
}

void Car::thread_loop(GasStation& station, Car& inCar){
    while(!station.destroyThread)
    {
        {    
            boost::unique_lock<boost::mutex> lck(station.m);
            while(!station.hasEmptyPump()){            
                station.cond.wait(lck);            
            } 
        }   

        Car* frontCar = station.getFrontCar();
        if(&inCar == frontCar)
        {            
            station.putCarAtPump(frontCar);
            boost::this_thread::sleep(boost::posix_time::milliseconds(30));       
            station.clearPump(inCar);
            inCar.fillCar();            
            station.cond.notify_all();
        }
    }
}

void Car::fillCar() {
    this->numFillups +=1;
}

int Car::getNumFillups(){
    return this->numFillups;
}