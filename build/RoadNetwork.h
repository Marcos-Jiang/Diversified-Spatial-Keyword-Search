/*************************************************************************
	> File Name: RoadNetwork.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 11:24:32 AM AEST
 ************************************************************************/

#ifndef _ROADNETWORK_H
#define _ROADNETWORK_H

#include "Node.h"
#include "Edge.h"
#include "Obj.h"

#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <iostream>
#include <fstream>
#include<memory>
#include<string>
#include <sstream>
#include <algorithm>

#include<map>
#include<vector>
#include<utility>

#include "stdlib.h"
#include<climits>
#include<bitset>

namespace bg = boost::geometry;
namespace bgi = bg::index;

class RoadNetwork{
public:
    typedef std::shared_ptr<Node>   nPtr;
    typedef std::shared_ptr<Edge>   ePtr;
    typedef std::shared_ptr<Obj>    oPtr;

    typedef bg::model::point <uint32_t, 2, bg::cs::cartesian> point;
    typedef std::pair<point, ePtr>  ePair;
    typedef std::pair<point, nPtr>  nPair;
    typedef bgi::rtree<ePair, bgi::quadratic<16> > eRtree;
    typedef bgi::rtree<nPair, bgi::quadratic<16> > nRtree;

    RoadNetwork() {};
    //void addNode(Node& n);
    void buildNetwork(std::string coFile,
            std::string grFile,
            std::string objFile);

    void qurey(uint32_t lat, uint32_t lon, std::vector<uint32_t> terms);

private:
    void buildNode(std::string file, std::map<uint32_t, nPtr>& nodes);
    void buildEdge(std::string file, std::map<uint32_t, nPtr>& nodes);
    void addObj(std::string file); 

    //nPtr binarySearch(uint64_t zOrder);
    ePtr nearestEdge(const point& p) {
        std::vector<ePair> result;
        _edges.query(bgi::nearest(p, 1), std::back_inserter(result));
        return result[0].second;
    };
    nPtr nearestNode(const point& p) {
        std::vector<nPair> result;
        _nodes.query(bgi::nearest(p, 1), std::back_inserter(result));
        return result[0].second;
    };
    const uint64_t computZorder(uint32_t lat, uint32_t lon) const;
private:
    //std::vector<nPtr> _nodes;
    nRtree _nodes;
    eRtree _edges;
};


#endif
