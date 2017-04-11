/*************************************************************************
	> File Name: Node.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 02:29:21 PM AEST
 ************************************************************************/

#ifndef _NODE_H
#define _NODE_H

//#include "Edge.h"
#include "Obj.h"

#include<vector>
#include<memory>
#include<cmath>
#include<limits>

class Edge;

class Node {
public:
    Node(const uint32_t id, const uint32_t lat,
            const uint32_t lon, const uint64_t zOrder,
            const float dist = std::numeric_limits<float>::max(),
            const bool marked = false) :  
        _nId{id}, _nLat{lat}, _nLon{lon}, _zOrder{zOrder},
        _dist{dist}, _marked{marked} {};

    //Node(const uint32_t id, const uint32_t lat, const uint32_t lon);
    ~Node(){};
    void addEdge(std::shared_ptr<Edge> e);
    std::vector<std::shared_ptr<Edge>>& getEdges();
    float dist2Node(std::shared_ptr<Obj> obj) const;
    float dist2Node(uint32_t lat, uint32_t lon) const;
    uint32_t getId() const {return _nId;};
    uint32_t getLat() const {return _nLat;};
    uint32_t getLon() const {return _nLon;};
    uint64_t getZorder() const {return _zOrder;};
    float getDist() const {return _dist;};
    void setDist(const float& dist) { _dist = dist;};
    void markNode() {_marked = true; };
    void unmarkNode() {_marked = false; };
    bool isMarked() {return _marked; };

    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const {
        return !(*this == other);
    };

private:
    uint32_t _nId;
    uint32_t _nLat;
    uint32_t _nLon;
    uint64_t _zOrder;
    float _dist;
    bool _marked;

    std::vector<std::shared_ptr<Edge>> _edges;
};

#endif
