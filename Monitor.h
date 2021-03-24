#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>

SC_MODULE(Monitor) {
  //Input coming from Controller
  sc_in<bool> lightWestEast;
  sc_in<bool> lightEastWest;
  sc_in<bool> lightNorthSouth;
  sc_in<bool> lightSouthNorth;

  SC_CTOR(Monitor);
  void MonitorLights();
};
#endif
