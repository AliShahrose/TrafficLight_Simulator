#include <iostream>
#include <cstdlib>
#include <ctime>
#include "InputGenerator.h"

InputGenerator::InputGenerator(sc_module_name name, bool random)
  : sc_module(name)
{
  west = 0;
  east = 0;
  north = 0;
  south = 0;

  if(random){
    cout << "RANDOM CARS" << endl;
    srand(time(NULL));
    for(int i = 0; i < 16; i++){
      carsWest[i] = ((rand() % 2) >= 1);
      carsEast[i] = ((rand() % 2) >= 1);
      carsNorth[i] = ((rand() % 2) >= 1);
      carsSouth[i] = ((rand() % 2) >= 1);
    }
  }
  else{
    cout << "INDEPENDENT CARS" << endl;
    for(int i = 0; i < 16; i++){
      carsWest[i] = ( i >> 0 ) & 0x01;
      carsEast[i] = ( i >> 1 ) & 0x01;
      carsNorth[i] = ( i >> 2 ) & 0x01;
      carsSouth[i] = ( i >> 3 ) & 0x01;
    }
  }

  // Setting up methods and threads
  SC_THREAD(generateCarsThread);

  SC_METHOD(generateCars);
  dont_initialize();
  sensitive << generateCarsEvent;

  SC_METHOD(carsDirection);
  dont_initialize();
  sensitive << carsDirectionEvent;
}

void InputGenerator::generateCarsThread(){
  for(;;){
    notify(generateCarsEvent);
    wait(1, SC_SEC);
    notify(carsDirectionEvent);
  }
}

void InputGenerator::carsDirection(){
  if(west >= 16 && east >= 16 && north >= 16 && south >=16)
    sc_stop();

  if(lightWestEast || !carsWest[west])
    west++;
  if(lightEastWest || !carsEast[east])
    east++;
  if(lightNorthSouth || !carsNorth[north])
    north++;
  if(lightSouthNorth || !carsSouth[south])
    south++;
}

void InputGenerator::generateCars(){
  cout << "Time: " << sc_time_stamp() << " Cars on: ";

  if(west < 16){
    if(carsWest[west])
      cout << " WestEast ";
    carWestEast = carsWest[west];
  }

  if(east < 16){
    if(carsEast[east])
      cout << " EastWest ";
    carEastWest = carsEast[east];
  }

  if(north < 16){
    if(carsNorth[north])
      cout << " NorthSouth ";
    carNorthSouth = carsNorth[north];
  }

  if(south < 16){
    if(carsSouth[south])
      cout << " SouthNorth ";
    carSouthNorth = carsSouth[south];
  }

  cout << endl;
}
