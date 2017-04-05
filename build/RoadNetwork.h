/*************************************************************************
	> File Name: RoadNetwork.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 11:24:32 AM AEST
 ************************************************************************/

#ifndef _ROADNETWORK_H
#define _ROADNETWORK_H

#include<vector>
#include<pair>
#include<memory>

class RoadNetwork{
public:
    std::vector<std::unique_ptr<Node>> _nodes;
private:
    class Node {
    public:
        Node(const int lat, const int lon) : _nLat{lat}, _nLon{lon} {};
        void addEdge(std::shared_ptr<Edge>& e);
        std::vector<std::shared_ptr<Edge>>& getEdges();
        long getDist(const Obj& obj) const;

    private:
        int _nLat;
        int _nLon;
        int _zOrder;

        std::vector<std::shared_ptr<Edge>> _adjList;
}
#endif
