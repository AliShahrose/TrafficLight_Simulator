#include "Monitor.h"

using std::cout;
using std::endl;

Monitor::Monitor(sc_module_name name)
  : sc_module(name)
{
  SC_METHOD(MonitorLights);
  dont_initialize();
  sensitive << lightWestEast << lightEastWest << lightNorthSouth << lightSouthNorth;
}

void Monitor::MonitorLights(){
  cout << "Time: " << sc_time_stamp() << " Traffic Lights: WestEast = " << lightWestEast << ", EastWest = " << lightEastWest <<
  ", NorthSouth = " << lightNorthSouth << ", SouthNorth = " << lightSouthNorth << endl;

  if((lightWestEast || lightEastWest) && (lightNorthSouth || lightSouthNorth)){
    cout << "Not possible!" << endl;
    sc_stop();
  }
}
