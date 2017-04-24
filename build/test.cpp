/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 05:20:10 PM AEST
 ************************************************************************/

#include<iostream>
#include<memory>
#include "RoadNetwork.h"
#include "Node.h"
#include "Edge.h"

int main() {
    RoadNetwork* r = new RoadNetwork();
    //std::map<long, std::shared_ptr<Node> > mNodes;
    //std::map<long, std::vector<std::shared_ptr<Edge> > > mEdges;
    //r->buildNode("../USA-road-d.BAY.co", mNodes);
    //r->buildEdge("../USA-road-d.BAY.gr", mEdges, mNodes);

    //for (auto it=mNodes.begin(); it!=mNodes.end(); ++it)
    //    std::cout << it->first << " => " << it->second->getLat() << ", " << it->second->getLon() << std::endl;

    //for (auto it=mEdges.begin(); it!=mEdges.end(); ++it) {
    //    std::cout << it->first << " => " << std::endl;
    //    for(auto e : it->second) {
    //        std::pair<std::weak_ptr<Node>, std::weak_ptr<Node>> p = e->getEndNode();
    //        std::cout << p.first.lock()->getId() << ", " << p.second.lock()->getId() << " : " << e->getWeight() << std::endl;
    //    }
    //    std::cout << std::endl;
    //}

    //r->buildNetwork("../dataset/Bay/BayRoadNetWork.co",
    //                "../dataset/Bay/BayRoadNetWork.gr",
    //                "../dataset/Bay/BayToken");

    r->buildNetwork("../dataset/Ca/CaRoadNetWork.co",
                    "../dataset/Ca/CaRoadNetWork.gr",
                    "../dataset/Ca/CaToken");


}
