/**
* Library for various geographical calculations
*
* @author  Tom Kane
* @version 1.0
* @since   2016-09-22
*/


/**
* Move some distance in some direction from a point on a sphere
* <p>
* Move from a specified longitude and latitude, in a specified azimuthal direction, a specified arc
* distance.
*
* @param lon Initial longitude (radians)
* @param lat Initial latitude (radians)
* @param arc Arc length (radians)
* @param az Azimuthal direction (radians)
* @param outlon Final longitude (radians) (passed by reference)
* @param outlat Final latitude (radians) (passed by reference)
*/
int ll_arc_distance(double lon, double lat, double arc, double az, double &outlon, double &outlat);

/**
* Calculate the azimuth and arc length from two points on a sphere
* <p>
* Calculate the azimuth and arc length of point two from point one on a sphere
*
* @param lon0 Initial longitude (radians)
* @param lat0 Initial latitude (radians)
* @param lon1 Final longitude (radians)
* @param lat1 Final latitude (radians)
* @param arc Arc distance travelled (radians) (passed by reference)
* @param az Azimuthal direction (radians) (passed by reference)
*/
int map_2points(double lon0, double lat0, double lon1, double lat1, double &arc, double &az);

/**
* Move some distance in some direction from a point on a sphere
* <p>
* Move from a specified longitude and latitude, in a specified azimuthal direction, a specified arc
* distance.
*
* @param lon Initial longitude (degrees)
* @param lat Initial latitude (degrees)
* @param arc Arc length (radians)
* @param az Azimuthal direction (degrees)
* @param outlon Final longitude (degrees) (passed by reference)
* @param outlat Final latitude (degrees) (passed by reference)
*/
int ll_arc_distance_deg(double lon, double lat, double arc, double az, double &outlon, double &outlat);

/**
* Calculate the azimuth and arc length from two points on a sphere
* <p>
* Calculate the azimuth and arc length of point two from point one on a sphere
*
* @param lon0 Initial longitude (degrees)
* @param lat0 Initial latitude (degrees)
* @param lon1 Final longitude (degrees)
* @param lat1 Final latitude (degrees)
* @param arc Arc distance travelled (radians) (passed by reference)
* @param az Azimuthal direction (degrees) (passed by reference)
*/
int map_2points_deg(double lon0, double lat0, double lon1, double lat1, double &arc, double &az);
