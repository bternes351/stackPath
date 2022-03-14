#ifndef CAR_H
#define CAR_H


class GasStation;

class Car 
{
public:
    Car();            
    Car(Car const&)=default;
    Car(Car& other)=default;
    Car(Car&& other)=default;
    ~Car()=default;

    static void thread_loop(GasStation&, Car&);
    
    void fillCar();
    int getNumFillups();


private: 
    int numFillups;
};

#endif