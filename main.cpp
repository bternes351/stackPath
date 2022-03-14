#include <iostream>
#include "gas_station.h"

int main() {    
    float numSeconds = 30.0f;
    float ms = numSeconds * 1000.0f;
    GasStation *pStation = new GasStation();
    pStation->initStationQueue();    

    std::cout << "Running Scenario for " << numSeconds << " seconds" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    while(true) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        if (elapsed.count() >= ms){
            break;
        }
    }
    pStation->destroyStation();
    pStation->printTotalFillsForCars();
    pStation->printTotalFillsForPumps();

    return 0;
}