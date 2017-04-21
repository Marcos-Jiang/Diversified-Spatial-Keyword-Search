/*************************************************************************
	> File Name: Obj.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 01:29:06 PM AEST
 ************************************************************************/

#include "Obj.h"

//const std::vector<uint32_t> & Obj::getTerms() const {
//    return _oTerms;
//}


//const std::pair<float, float>& Obj::getDist() const {
//    return _oDist;
//}

float Obj::dist2Obj(const Obj& other) const {
    return dist2Obj(other.getLat(), other.getLon());
}

float Obj::dist2Obj(uint32_t lat, uint32_t lon) const {
    float lat1 = lat/1000000.0;
    float lon1 = lon/1000000.0;
    float lat2 = _oLat/1000000.0;
    float lon2 = _oLon/1000000.0;

    float R = 6371;
    float dLat = (lat2-lat1)*(std::acos(-1)/180.0);
    float dLon = (lon2-lon1)*(std::acos(-1)/180.0);
    float a = std::sin(dLat/2) * std::sin(dLat/2) +
                std::cos(lat1*(std::acos(-1)/180.0)) * std::cos(lat2*(std::acos(-1)/180.0)) * std::sin(dLon/2) * std::sin(dLon/2);

    return R * 2 * std::atan2(std::sqrt(a), std::sqrt(1-a)); 
}

bool Obj::operator==(const Obj &other) const {
    return _oId == other._oId;
}
