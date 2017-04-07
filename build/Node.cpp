/*************************************************************************
	> File Name: Node.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 02:30:51 PM AEST
 ************************************************************************/

#include "Node.h"
#include "Edge.h"


void Node::addEdge(std::shared_ptr<Edge> e) {
    _edges.push_back(e);
}

std::vector<std::shared_ptr<Edge>>& Node::getEdges() {
    return _edges;
}

float Node::dist2Node(std::shared_ptr<Obj> obj) const {
    float lat1 = obj->getLat()/1000000.0;
    float lon1 = obj->getLon()/1000000.0;
    float lat2 = _nLat/1000000.0;
    float lon2 = _nLon/1000000.0;

    float R = 6371;
    float dLat = (lat2-lat1)*(std::acos(-1)/180.0);
    float dLon = (lon2-lon1)*(std::acos(-1)/180.0);
    float a = std::sin(dLat/2) * std::sin(dLat/2) +
                std::cos(lat1*(std::acos(-1)/180.0)) * std::cos(lat2*(std::acos(-1)/180.0)) * std::sin(dLon/2) * std::sin(dLon/2);

    return R * 2 * std::atan2(std::sqrt(a), std::sqrt(1-a)); 
}


