#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "g2p2c2_header.h"


using namespace std;

using namespace forF;

double D2_Oscilador (double t, double x, double v)
{
  return -(k / m) * x - (lbd / m) * v + (F0 / m) * sin(wf * t);
}


