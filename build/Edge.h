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

#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<algorithm>
#include<memory>
#include<cmath>

class Node;

class Edge {
public:
    typedef std::weak_ptr<Node>     wPtr;
    typedef std::shared_ptr<Node>   sPtr;
    typedef std::shared_ptr<Obj>    oPtr;
    typedef std::vector<oPtr>::iterator    iter;

    Edge(sPtr n1, sPtr n2, const float dist);
    ~Edge(){};
    void addObj(oPtr obj);
    float dist2Edge(oPtr obj) const;
    const float getWeight() const {return _eWeight; };
    const std::pair<uint32_t, uint32_t>& getMid() const {return _midPoint; };
    std::pair<wPtr, wPtr>& getEndNode() {return _endNode; };
    std::vector<oPtr>& getObj(const std::vector<uint32_t>& terms);
    std::vector<oPtr> matchObj(const std::vector<uint32_t>& terms);

private:
    void buildIF();
private:
    std::pair<wPtr, wPtr> _endNode;
    std::vector<oPtr > _obj;
    float _eWeight;
    std::pair<uint32_t, uint32_t> _midPoint;
    std::map<uint32_t, std::vector<oPtr> > _if;
};

//double deg2rad(double deg) {
//    return deg * (std::acos(-1)/180.0);
//}

#endif
