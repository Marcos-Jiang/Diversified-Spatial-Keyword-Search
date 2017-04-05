/*************************************************************************
	> File Name: Edge.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 12:08:35 PM AEST
 ************************************************************************/

#ifndef _EDGE_H
#define _EDGE_H

#include<vector>
#include<pair>
#include<memory>

class Edge {
public:
    Edge(const Node& n1, const Node& n2, const long dist) : _eDist{dist} {};
    void addObj(Obj& obj);
    double compDist(const Obj& obj) const;
    long getWeight() const;
    std::vector<shared_ptr<Obj> >& getObj(const std::vector<long>& terms);

private:
    std::pair<std::weak_ptr<Node> > _destNode;
    std::vector<std::shared_ptr<Obj> > _obj;
    long _eWeight;
}

#endif
