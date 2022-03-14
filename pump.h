#ifndef PUMP_H
#define PUMP_H

class Car;

class Pump {

public:
    Pump();
    Pump(Pump&)=default;
    Pump(Pump const&)=default;
    Pump(Pump&&)=default;
    ~Pump()=default;

    void fillup();
    bool isEmpty();
    int getNumFillUps();

    void setCar(Car*);
    Car* getPumpCar();   

private:
    Car* pCar;
    int numFillups;

};

#endif