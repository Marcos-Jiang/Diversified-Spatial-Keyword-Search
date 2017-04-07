/*************************************************************************
	> File Name: Edge.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 01:29:21 PM AEST
 ************************************************************************/

#include "Edge.h"
#include "Node.h"


Edge::Edge(sPtr n1, sPtr n2, const float dist) {
//Edge::Edge(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, const uint32_t dist) {
    _eWeight = dist;
    _endNode = std::make_pair<wPtr, wPtr> (n1, n2);
    _midPoint = std::make_pair<uint32_t, uint32_t>((n1->getLat()+n2->getLat())/2, (n1->getLon()+n2->getLon())/2);
}

void Edge::addObj(Obj& obj) {
    _obj.push_back(std::make_shared<Obj>(obj));
}

float Edge::dist2Edge(std::shared_ptr<Obj> obj) const {
    double lat1 = _midPoint.first/1000000.0;
    double lon1 = _midPoint.second/1000000.0;
    double lat2 = obj->getLat()/1000000.0;
    double lon2 = obj->getLon()/1000000.0;

    double R = 6371;
    double dLat = (lat2-lat1)*(std::acos(-1)/180.0);
    double dLon = (lon2-lon1)*(std::acos(-1)/180.0);
    double a = std::sin(dLat/2) * std::sin(dLat/2) +
                std::cos(lat1*(std::acos(-1)/180.0)) * std::cos(lat2*(std::acos(-1)/180.0)) * std::sin(dLon/2) * std::sin(dLon/2);

    return R * 2 * std::atan2(std::sqrt(a), std::sqrt(1-a)); 
}

std::vector<std::shared_ptr<Obj> >& Edge::getObj(const std::vector<uint32_t>& terms) {
    return _obj;
}

//double Edge::deg2rad(double deg) const {
//    return deg * (std::acos(-1)/180.0);
//}

