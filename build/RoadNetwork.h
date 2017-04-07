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

class RoadNetwork{
public:
    typedef std::shared_ptr<Node>   nPtr;
    typedef std::shared_ptr<Edge>   ePtr;
    typedef std::shared_ptr<Obj>    oPtr;

    RoadNetwork() {};
    void addNode(Node& n);
    void buildNetwork(std::string coFile,
            std::string grFile,
            std::string objFile);

private:
    void buildNode(std::string file, std::map<uint32_t, nPtr>& nodes);
    //void buildEdge(std::string file, std::map<int, std::vector<ePtr> >& edges, std::map<int, nPtr>& nodes);
    void buildEdge(std::string file, std::map<uint32_t, nPtr>& nodes);
    void addObj(std::string file); 
    std::vector<nPtr> _nodes;

    nPtr binarySearch(uint64_t zOrder);
    const uint64_t computZorder(uint32_t lat, uint32_t lon) const;
};


#endif
