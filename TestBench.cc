#include <iostream>
#include <cstring>
#include <systemc.h>
#include "Controller.h"
#include "InputGenerator.h"
#include "Monitor.h"

int sc_main(int argc, char **argv)
{
  //This was given by the compiler
  sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                           sc_core::SC_DO_NOTHING );

  //Checking if user asked for random generation or not
  bool random = 0;
  if(argc > 1 && !strcmp(argv[1], "1")){
    random = 1;
  }

  // Channels
  sc_signal<bool> lightWestEast;
  sc_signal<bool> lightEastWest;
  sc_signal<bool> lightNorthSouth;
  sc_signal<bool> lightSouthNorth;

  sc_signal<bool> carWestEast;
  sc_signal<bool> carEastWest;
  sc_signal<bool> carNorthSouth;
  sc_signal<bool> carSouthNorth;

  // Modules
  InputGenerator inputgenerator("InputGenerator", random);
  Controller controller("Controller");
  Monitor monitor("Monitor");

  // Channel connections
  inputgenerator(carWestEast, carEastWest, carNorthSouth, carSouthNorth,
    lightWestEast, lightEastWest, lightNorthSouth, lightSouthNorth);

  monitor(lightWestEast, lightEastWest, lightNorthSouth, lightSouthNorth);

  controller(lightWestEast, lightEastWest, lightNorthSouth, lightSouthNorth,
      carWestEast, carEastWest, carNorthSouth, carSouthNorth);

  // Simulation
  sc_start();

  return 0;
}
