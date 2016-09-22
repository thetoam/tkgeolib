#include <cmath>

#include "tkgeolib.h"

const long double PI = 3.141592653589793238L;

int map_2points(double lon0, double lat0, double lon1, double lat1, double &arc, double &az)
{
  double clat0, slat0, clat1, slat1, cdlon, sdlon, cosc, sinc, caz, saz;

  clat0 = cos(lat0);
  slat0 = sin(lat0);
  clat1 = cos(lat1);
  slat1 = sin(lat1);
  cdlon = cos(lon1 - lon0);
  sdlon = sin(lon1 - lon0);
  cosc = slat0 * slat1 + clat0 * clat1 * cdlon;
  if (cosc < -1) cosc = -1.0;
  if (cosc > 1) cosc = 1.0;
  sinc = sqrt(1.0 - cosc * cosc);
  caz = (clat0 * slat1 - slat0 * clat1 * cdlon) / sinc;
  saz = sdlon * clat1 / sinc;		// Note: IDL checks for tiny angle to decide if point is antipodal
  arc = acos(cosc);
  az = atan2(saz, caz);
  return 0;
}


int map_2points_deg(double lon0, double lat0, double lon1, double lat1, double &arc, double &az)
{
  int r;
  double lon0_rad = lon0 * PI / 180.0;
  double lat0_rad = lon0 * PI / 180.0;
  double lon1_rad = lon0 * PI / 180.0;
  double lat1_rad = lon0 * PI / 180.0;
  r = map_2points(lon0_rad, lat0_rad, lon1_rad, lat1_rad, arc, az);
  az *= 180.0 / PI;
  return r;
}
