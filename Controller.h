#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <systemc.h>

SC_MODULE(Controller) {

  //Variables to keep track of the traffic
  char carsDirection;
  int counter;

  sc_event switchLight;

  //Output going to InputGenerator and Monitor
  sc_out<bool> lightWestEast;
  sc_out<bool> lightEastWest;
  sc_out<bool> lightNorthSouth;
  sc_out<bool> lightSouthNorth;

  //Input coming from InputGenerator
  sc_in<bool> carWestEast;
  sc_in<bool> carEastWest;
  sc_in<bool> carNorthSouth;
  sc_in<bool> carSouthNorth;
  
  SC_CTOR(Controller);
  void checkLights();
  void changeLights();
};

#endif
