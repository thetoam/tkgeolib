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


int ll_arc_distance_deg(double lon, double lat, double arc, double az, double &outlon, double &outlat)
{
  int r;
  double lon_rad = lon * PI / 180.0;
  double lat_rad = lat * PI / 180.0;
  double az_rad = az * PI / 180.0;
  r = ll_arc_distance(lon_rad, lat_rad, arc, az_rad, outlon, outlat);
  outlon *= 180.0 / PI;
  outlat *= 180.0 / PI;
  return r;
}
