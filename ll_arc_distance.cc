#include <cmath>

#include "tkgeolib.h"

const long double PI = 3.141592653589793238L;

int ll_arc_distance(double lon, double lat, double arc, double az, double &outlon, double &outlat)
{
  double cdist, sdist, clat, slat, caz, saz;

  cdist = cos(arc);
  sdist = sin(arc);
  clat = cos(lat);
  slat = sin(lat);
  caz = cos(az);
  saz = sin(az);

  outlat = asin(slat * cdist + clat * sdist * caz);
  outlon = lon + atan2(sdist * saz, clat * cdist - slat * sdist * caz);

  while (outlon < -1 * PI) outlon += 2 * PI;
  while (outlon > PI) outlon -= 2 * PI;

  return 0;
}
