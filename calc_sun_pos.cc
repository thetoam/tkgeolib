#include <cmath>
#include <iostream>

#include "tkgeolib.h"

const long double PI = 3.141592653589793238L;

/* Functions required internally - may make them available within library later */
long ymd2jd(int yr, int mo, int dy);
double calc_dec_sun(double js);
double calc_rec_sun(double js);
double calc_parallaxe(double lon, double lat, double ha, double dec, double alt);
double calc_geo_pos(double lat, double ha, double dec, double &azm, double &zen, double alt);
double calc_ellipsoid(double za, double lat, double az, double alt);


int calc_sun_pos(int yr, int mo, int dy, int hr, int mt, int sc, double lon, double lat, \
                 double alt, double &az, double &zn)
{
  double js;
  double rs,ds;
  double gh;
  double ha;
  double sl;
  double d,d0,h,t;
  double azm,zen;

  /* Only sensible for 1970-2030 */
  if (yr >= 2030 || yr < 1970)
    ::std::cerr << "Warning: date outside solar zenith model range (1970-2030)" << ::std::endl;

  /* Decimal Julian date */
  js = ymd2jd(yr, mo, dy) - 0.5 + (((double) hr) / 24.0) + ((double) mt / 1440.0) + ((double) sc / 86400.0);

  ds = calc_dec_sun((js - 2451545.0) / 36525.0);
  rs = calc_rec_sun((js - 2451545.0) / 36525.0);

  /* Sidereal Time
   * From http://www.usno.navy.mil/USNO/astronomical-applications/astronomical-information-center/approx-sider-time
   */
  d = js - 2451545.0;
  d0 = ((int) js) - 0.5 - 2451545.0;
  h = (d - d0) * 24;
  t = d / 36525;
  gh = 6.697374558 + 0.06570982441908 * d0 + 1.00273790935 * h + 0.000026 * t * t;
  while(gh > 24) gh -= 24;
  while(gh < 0) gh += 24; /* Sidereal time, between 0-24 */

  ha = gh - rs;
  ha = ha - 24.0 * floor(ha / 24.0); /* Hour angle (in hours) */  /* Hour angle is correct */
  sl = ha - (lon / (-15.0)); /*longitude of the sun (in hours?) */
  ha = calc_parallaxe((-1) * lon, lat, sl, ds, alt / 1000.0);

  calc_geo_pos(lat, ha, ds, azm, zen, alt / 1000.0);

  az = azm * 180.0 / PI;
  zn = zen;

  return 0;
}




/* Convert a year-month-day to Julian Day Number */
long ymd2jd(int yr, int mo, int dy)
{
  long y = (long) yr;
  long m = (long) mo;
  long d = (long) dy;
  return 367 * y - 7 * (y + (m + 9) / 12) / 4 - 3 * ((y + (m - 9) / 7) / 100 + 1) / 4 + 275 * m / 9 + d + 1721029; /* JDN (integer) */
}



/* Declination of the Sun */
double calc_dec_sun(double js)
{
  double dr = PI / 180.0;
  double dec = 0;

  dec = 23.2643 * cos(dr * (36000.7696 * js + 190.4602)) \
    -  0.0127 * js * cos(dr * (36000.7696 * js + 190.4602)) \
    +  0.3888 * cos(dr * (1.72 * js + 12.94)) \
    -  0.0012 * js * cos(dr * (1.72 * js + 12.94)) \
    +  0.3886 * cos(dr * (71999.82 * js + 187.99)) \
    -  0.0012 * js * cos(dr * (71999.82 * js + 187.99)) \
    +  0.1646 * cos(dr * (108002.3 * js + 211.4)) \
    -  0.0003 * js * cos(dr * (108002.3 * js + 211.4)) \
    +  0.0082 * cos(dr * (72003.0 * js + 34.0)) \
    +  0.0082 * cos(dr * (144001.0 * js + 209.0)) \
    +  0.0073 * cos(dr * (107999.0 * js +  186.0)) \
    +  0.0031 * cos(dr * (180004.0 * js + 232.0)) \
    +  0.0022 * cos(dr * (37935.0 * js + 65.0)) \
    +  0.0008 * cos(dr * (35997.0 * js + 345.0)) \
    +  0.0004 * cos(dr * (68965.0 * js + 78.0)) \
    +  0.0004 * cos(dr * (3036.0 * js + 123.0)) \
    +  0.0003 * cos(dr * (481268.0 * js + 128.0)) \
    +  0.0003 * cos(dr * (35982.0 * js + 121.0)) \
    +  0.0003 * cos(dr * (36020.0 * js + 80.0)) \
    +  0.0003 * cos(dr * (409266.0 * js + 287.0)) \
    +  0.0003 * cos(dr * (13482.0 * js + 293.0)) \
    +  0.0003 * cos(dr * (9037.0 * js + 332.0)) \
    +  0.0003 * cos(dr * (180000.0 * js + 206.0));
    return dec;
}


/* Right ascention of the Sun */
double calc_rec_sun(double js)
{
  double dr = PI / 180.0;
  double rec = 0;
  rec = 18.69735 + 2400.05130 * js \
      + 0.16419 * cos(dr * (72001.539 * js + 290.920)) \
      - 0.00019 * js * cos(dr * (72001.539 * js + 290.920)) \
      + 0.12764 * cos(dr * (35999.050 * js + 267.520)) \
      - 0.00032 * js * cos(dr * (35999.050 * js + 267.520)) \
      + 0.00549 * cos(dr * (36002.5 * js +113.4)) \
      - 0.00002 * js * cos(dr * (36002.5 * js + 113.4)) \
      + 0.00549 * cos(dr * (108000.6 * js + 288.5)) \
      - 0.00002 * js * cos(dr * (108000.6 * js +288.5)) \
      + 0.00353 * cos(dr * (144003.1 * js +311.9)) \
      + 0.00133 * cos(dr * (71998.1 * js + 265.1)) \
      + 0.00032 * cos(dr * (1934.0 * js + 145.0)) \
      + 0.00024 * cos(dr * (108004.0 * js + 134.0)) \
      + 0.00024 * cos(dr * (180002.0 * js + 309.0)) \
      + 0.00015 * cos(dr * (144000.0 * js + 286.0)) \
      + 0.00013 * cos(dr * (32964.0 * js + 158.0)) \
      + 0.00012 * cos(dr * (19.0 * js + 159.0)) \
      + 0.00012 * cos(dr * (445267.0 * js + 208.0)) \
      + 0.00010 * cos(dr * (45038.0 * js + 254.0)) \
      + 0.00010 * cos(dr * (216005.0 * js + 333.0)) \
      + 0.00009 * cos(dr * (22519.0 * js + 352.0)) \
      + 0.00005 * cos(dr * (65929.0 * js + 45.0)) \
      + 0.00005 * cos(dr * (3035.0 * js + 110.0)) \
      + 0.00005 * cos(dr * (9038.0 * js + 64.0)) \
      + 0.00004 * cos(dr * (33718.0 * js + 316.0)) \
      + 0.00003 * cos(dr * (155.0 * js + 118.0)) \
      + 0.00003 * cos(dr * (73936.0 * js + 166.0)) \
      + 0.00003 * cos(dr * (2281.0 * js + 221.0)) \
      + 0.00003 * cos(dr * (3.0 * js + 296.0)) \
      + 0.00003 * cos(dr * (29930.0 * js + 48.0)) \
      + 0.00003 * cos(dr * (31557.0 * js + 161.0));

  return rec - ((long int)(rec / 24)) * 24;
}


double calc_parallaxe(double lon, double lat, double ha, double dec, double alt)
{
  double dr = PI / 180.0;
  double dist = 1.495954e8;
  double rho = 6378.14 + alt; /* km */
  double r_st = sqrt(dist * dist + rho * rho - 2 * dist * rho * cos(dr * dec));
  double x = dist * cos(dr * dec) * sin(dr * ha * 15.0) - rho * cos(dr * lat) * sin(dr * lon);
  double y = dist * cos(dr * dec) * cos(dr * ha * 15.0) - rho * cos(dr * lat) * cos(dr * lon);
  double dec_c = asin((dist * sin(dr * dec) - rho * sin(dr * lat)) / r_st) / dr;
  double z = r_st * cos(dec_c * dr);
  double a_sin;
  a_sin = ((x / z) < 1) ? x / z : 1;
  a_sin = (a_sin > (-1)) ? a_sin : -1;
  a_sin = asin(a_sin);
  double a_cos;
  a_cos=((y / z) < 1) ? y / z : 1;
  a_cos=(a_cos > (-1)) ? a_cos : -1;
  a_cos=acos(a_cos);
  double hk = atan(x / y) / (dr * 15.0);
  hk = hk + ((double) (a_sin >= 0.0)) * (12.0 * (double) (a_cos >= (PI / 2.0))) + ((double) (a_sin < 0.0)) * (12.0 * (double) (a_cos >= (PI / 2.0)) + 24.0 * (double) (a_cos < (PI / 2.0)));
  return hk;
}


double calc_geo_pos(double lat, double ha, double dec, double &azm, double &zen, double alt)
{
  double dr = PI / 180.0;
  double za = acos(sin(dr * lat) * sin(dr * dec) + cos(dr * lat) * cos(dr * dec) * cos(dr * ha * 15.0));
  double sa = cos(dr * dec) * sin(dr * ha * 15.0) / sin(za);
  double ca = (-1) * (cos(dr * lat) * sin(dr * dec) - sin(dr * lat) * cos(dr * dec) * cos(dr * ha * 15.0)) / sin(za);
  double absasinsa = (asin(sa) >= 0) ? asin(sa) : (-1) * asin(sa);
  double az = asin(sa) * (ca >= 0) + (ca < 0) * ((PI - asin(sa)) * (sa >= 0) + (absasinsa - PI) * (sa < 0)) + PI * (sin(za) > 0);
  az = az - 360.0 * floor((az / dr) / 360.0);
  zen = calc_ellipsoid(za / dr, lat, az, alt);
  azm = az;
  return 0;
}

double calc_ellipsoid(double za, double lat, double az, double alt)
{
  double dr = PI / 180.0;
  double e_rad = 6378.14 + alt;
  double p_rad = 6356.755 + alt;
  double x = p_rad / e_rad;
  double lat_cor = lat - atan(x * x * tan(lat * dr)) / dr;
  return za + cos(az * dr) * lat_cor;
}
