#ifndef INPUTGENERATOR_H
#define INPUTGENERATOR_H

#include <systemc.h>

SC_MODULE(InputGenerator){


  //Variables used to generate cars
  bool carsWest[16];
  bool carsEast[16];
  bool carsNorth[16];
  bool carsSouth[16];


  int west;
  int east;
  int north;
  int south;

  //Output going to Controller
  sc_out<bool> carWestEast;
  sc_out<bool> carEastWest;
  sc_out<bool> carNorthSouth;
  sc_out<bool> carSouthNorth;

  //Input coming from Controller
  sc_in<bool> lightWestEast;
  sc_in<bool> lightEastWest;
  sc_in<bool> lightNorthSouth;
  sc_in<bool> lightSouthNorth;
  

  //Events
  sc_event generateCarsEvent;
  sc_event carsDirectionEvent;

  SC_HAS_PROCESS(InputGenerator);
  InputGenerator(sc_module_name name, bool random);
  void generateCarsThread();
  void carsDirection();
  void generateCars();
};

#endif
