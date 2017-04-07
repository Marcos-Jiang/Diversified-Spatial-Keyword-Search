/*************************************************************************
	> File Name: Edge.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 12:08:35 PM AEST
 ************************************************************************/

#ifndef _EDGE_H
#define _EDGE_H

#include "Obj.h"
//#include "Node.h"

#include<vector>
#include<utility>
#include<memory>
#include<cmath>

class Node;

class Edge {
public:
    typedef std::weak_ptr<Node>     wPtr;
    typedef std::shared_ptr<Node>     sPtr;

    Edge(sPtr n1, sPtr n2, const float dist);
    //Edge(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, const uint32_t dist);
    ~Edge(){};
    void addObj(Obj& obj);
    float dist2Edge(std::shared_ptr<Obj> obj) const;
    const float getWeight() const {return _eWeight; };
    std::pair<wPtr, wPtr>& getEndNode() {return _endNode; };
    std::vector<std::shared_ptr<Obj> >& getObj(const std::vector<uint32_t>& terms);

private:
    std::pair<wPtr, wPtr> _endNode;
    std::vector<std::shared_ptr<Obj> > _obj;
    float _eWeight;
    std::pair<uint32_t, uint32_t> _midPoint;
};

//double deg2rad(double deg) {
//    return deg * (std::acos(-1)/180.0);
//}

#endif
