#include "haversine.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double R = 3958.8;

double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double toRadians = M_PI / 180.0;
    lat1 *= toRadians;
    lon1 *= toRadians;
    lat2 *= toRadians;
    lon2 *= toRadians;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::pow(std::sin(dlat / 2), 2) +
        std::cos(lat1) * std::cos(lat2) * std::pow(std::sin(dlon / 2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c; 
}


