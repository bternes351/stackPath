#ifndef GAS_STATION_H
#define GAS_STATION_H

#include <vector>
#include <queue>
#include <boost/thread.hpp>

class Car;
class Pump;

class GasStation {
    public:
        GasStation();
        GasStation(GasStation&)=delete;
        GasStation(GasStation const&)=delete;
        GasStation(GasStation&&)=delete;
        ~GasStation();

        void initStationQueue();
        void putCarAtPump(Car* inCar);
        void clearPump(Car&);
        bool hasEmptyPump();
        void destroyStation();

        void printTotalFillsForPumps();
        void printTotalFillsForCars();

        Car* getFrontCar();

        boost::mutex m;        
        boost::condition_variable cond;
        bool destroyThread;

    private:
        std::queue<Car*> stationQueue;
        std::vector<boost::thread> threadPool;
        std::vector<Pump*> pumps;


        int numPumps;
        int totalNumFillups;
        int numCars;
        

};

#endif