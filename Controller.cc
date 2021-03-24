#include <iostream>
#include "Controller.h"

using std::cout;
using std::endl;

Controller::Controller(sc_module_name name)
  : sc_module(name)
{
  carsDirection = 'W';
  counter = 0;

  SC_METHOD(changeLights);
  dont_initialize();
  sensitive << carWestEast << carEastWest << carNorthSouth << carSouthNorth << switchLight;
  SC_THREAD(checkLights);
}

void Controller::checkLights(){
  for(;;){
    if(carsDirection == 'W'){
      if(carWestEast || carEastWest){
        carsDirection = 'E';
        cout << "Time: " << sc_time_stamp() << " Light on: EastWest" << endl;
      }else if(carNorthSouth || carSouthNorth){
        carsDirection = 'S';
        cout << "Time: " << sc_time_stamp() << " Light on: SouthNorth" << endl;
      }else{
        carsDirection = 'W';
        cout << "Time: " << sc_time_stamp() << " Light on: WestEast" << endl;
      }
    }
    else if(carsDirection == 'E'){
      if(counter <= 5){
        carsDirection = 'N';
        cout << "Time: " << sc_time_stamp() << " Light on: NorthSouth" << endl;
      }else{
        carsDirection = 'E';
        cout << "Time:" << sc_time_stamp() << " Light on: EastWest" << endl;
        counter++;
      }
    }
    else if(carsDirection == 'N'){
      if(carNorthSouth || carSouthNorth){
        carsDirection = 'S';
        cout << "Time: " << sc_time_stamp() << " Light on: SouthNorth" << endl;
      }else if(carWestEast || carEastWest){
        carsDirection = 'E';
        cout << "Time: " << sc_time_stamp() << " Light on: EastWest" << endl;
      }else{
        carsDirection = 'N';
        cout << "Time: " << sc_time_stamp() << " Light on: NorthSouth" << endl;
      }
    }
    else if(carsDirection == 'S'){
      if(counter <= 5){
        carsDirection = 'W';
        cout << "Time: " << sc_time_stamp() << " Light on: WestEast" << endl;
      }else{
        carsDirection = 'S';
        cout << "Time: " << sc_time_stamp() << " Light on: SouthNorth" << endl;
        counter++;
      }
    }
    else{
      cout << "Wrong direction!" << endl;
    }
    notify(switchLight);
    wait(1, SC_SEC);
  }
}

void Controller::changeLights(){
  if(carsDirection == 'E'){
    lightWestEast = carWestEast;
    lightEastWest = carEastWest;
  }else if(carsDirection == 'S'){
    lightNorthSouth = carNorthSouth;
    lightSouthNorth = carSouthNorth;
  }else{
    lightWestEast = 0;
    lightEastWest = 0;
    lightNorthSouth = 0;
    lightSouthNorth = 0;
  }
}
