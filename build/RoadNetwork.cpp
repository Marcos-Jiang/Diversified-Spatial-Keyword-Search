/*************************************************************************
	> File Name: RoadNetwork.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 01:30:19 PM AEST
 ************************************************************************/
#include "RoadNetwork.h"

void RoadNetwork::addNode(Node& n) {
    //_nodes.push_back(std::make_shared<Node>(n));
}

void RoadNetwork::buildNode(std::string file, std::map<uint32_t, nPtr>& nodes) {
    uint32_t cunt = 0;
    uint32_t latMax = 0;
    uint32_t latMin = INT_MAX;
    uint32_t lonMax = 0;
    uint32_t lonMin = INT_MAX;

    std::string line;
    std::ifstream input(file);
    int tmp;
    std::vector<uint32_t> cord;

    while (std::getline(input, line)) {
        //if(line.find("v") != 0) continue;
        ++cunt;
        //line.erase(0,2);
        cord.clear();
        std::istringstream ss(line);
        
        while(ss >> tmp) cord.push_back(abs(tmp)); 
        
        lonMax = (lonMax>cord[1]) ? lonMax : cord[1];
        lonMin = (lonMin<cord[1]) ? lonMin : cord[1];
        latMax = (latMax>cord[2]) ? latMax : cord[2];
        latMin = (latMin<cord[2]) ? latMin : cord[2];

        //nodes[cord[0]] = std::make_shared<Node>(Node(cord[0], cord[2], cord[1], computZorder(cord[2], cord[1])));
        //nodes[cord[0]] = std::make_shared<Node>(Node(cord[0], cord[2], cord[1], 0));
        nPtr n = std::make_shared<Node>(Node(cord[0], cord[2], cord[1], 0));
        nodes[cord[0]] = n;
        _nodes.insert(std::make_pair(point(cord[2], cord[1]), n));

        //if(cunt == 20) break;
    }
    std::cout << "#nodes: " << cunt << std::endl;
    //std::cout << "Lon: " << lonMin << " - " << lonMax << std::endl;
    //std::cout << "Lat: " << latMin << " - " << latMax << std::endl;
}

//void RoadNetwork::buildEdge(std::string file, std::map<uint32_t, std::vector<ePtr> >& edges, std::map<uint32_t, nPtr>& nodes) {
void RoadNetwork::buildEdge(std::string file, std::map<uint32_t, nPtr>& nodes) {
    uint32_t cunt = 0;
    std::string line;
    std::ifstream input(file);
    std::string tmp;
    std::vector<std::string> tokens;
    std::vector<ePair> edges;

    while (std::getline(input, line)) {
        //if(line.find("a") != 0) continue;
        ++cunt;
        //line.erase(0,2);
        tokens.clear();
        std::istringstream ss(line);
        
        while(ss >> tmp) tokens.push_back(tmp); 
        uint32_t n1 = std::atoi(tokens[0].c_str());
        uint32_t n2 = std::atoi(tokens[1].c_str());
        float d = std::atof(tokens[2].c_str());

        ePtr e = std::make_shared<Edge>(Edge(nodes[n1], nodes[n2], d));

        nodes[n1]->addEdge(e);
        nodes[n2]->addEdge(e);


        edges.push_back(std::make_pair(point(e->getMid().first,e->getMid().second), e));
        //if(cunt == 10) break;
        //std::getline(input, line);
    }
    std::cout << "#edges: " << cunt << std::endl;
    //_edges = bgi::rtree<ePair, bgi::quadratic<16> >(edges);
    _edges = eRtree(edges);
    std::vector<ePair>(edges).swap(edges);
}


void RoadNetwork::addObj(std::string file) {
    uint32_t cunt = 0;
    float maxDist;
    std::string line;
    std::ifstream input(file);
    int tmp;
    std::vector<uint32_t> tokens;

    while (std::getline(input, line)) {
        tokens.clear();
        std::istringstream ss(line);
        
        while(ss >> tmp) tokens.push_back(abs(tmp)); 
        size_t len = tokens.size();
        uint32_t lat = tokens[len-2];
        uint32_t lon = tokens[len-1];
        //uint64_t zOrder = computZorder(lat, lon);
        uint64_t zOrder = 0;
        tokens.erase(tokens.begin());
        tokens.pop_back();
        tokens.pop_back();

        oPtr o = std::make_shared<Obj>(Obj(lat, lon, zOrder, tokens));
        //nPtr n = binarySearch(zOrder);
        ePtr e = nearestEdge(point(lat, lon));
        maxDist = e->dist2Edge(o);
        if(maxDist>20) continue;

        e->addObj(o);
        ++cunt;
        //maxDist = (maxDist > e->dist2Edge(o)) ? maxDist : e->dist2Edge(o);

        //std::cout << "edge: " << e->getMid().first << ", " <<
        //    e->getMid().second << std::endl;
        //std::cout << "object: " << lat << ", " << lon << std::endl;
        //std::cout << "dist: " << e->dist2Edge(o) << std::endl;
        //std::cout << std::endl;


        //if(cunt == 10) break;
    }
    std::cout << "#objects: " << cunt << std::endl;
    std::cout << "maxDist: " << maxDist << std::endl;
}

void RoadNetwork::buildNetwork(std::string coFile,
                               std::string grFile,
                               std::string objFile) {
    std::map<uint32_t, std::shared_ptr<Node> > mNodes;
    buildNode(coFile, mNodes);
    buildEdge(grFile, mNodes);

    //for(auto it=mNodes.begin(); it!=mNodes.end(); ++it) {
    //    //if(!it->second->getEdges().empty())
    //    //    _nodes.push_back(it->second); 
    //    //else
    //    //    std::cout << "empty Node!!" << std::endl;
    //    
    //    _nodes.push_back(it->second); 
    //}
    
    //std::cout << "start sort" << std::endl;
    //std::sort(_nodes.begin(), _nodes.end(),
    //       [](auto a, auto b) { return a->getZorder()<b->getZorder(); });

    addObj(objFile);

    //uint32_t cunt = 0;

    //for(auto i : _nodes) {
    //    //std::cout << i->getId() << " => " << i->getLat() <<
    //    //    ", " << i->getLon() << ", " <<
    //    //    i->getZorder() << std::endl;
    //    //std::cout<<std::bitset<64>(i->getLat())<<std::endl;
    //    //std::cout<<std::bitset<64>(i->getLon())<<std::endl;
    //    //std::cout<<std::bitset<64>(i->getZorder())<<std::endl;

    //    for(auto e : i->getEdges()) {
    //        std::cout << e->getEndNode().first.lock()->getId() 
    //            << ", " << e->getEndNode().second.lock()->getId()
    //            << ": " << e->getWeight() << std::endl;
    //    }
    //    std::cout << std::endl;
    //    
    //    if(++cunt == 5) break;
    //}

}

//RoadNetwork::nPtr RoadNetwork::binarySearch(uint64_t zOrder) {
//    size_t i = 0;
//    size_t j = _nodes.size();
//
//    while(i<j-1) {
//        if(zOrder < _nodes[(i+j)/2]->getZorder()) j = (i+j)/2;
//        else if(zOrder > _nodes[(i+j)/2]->getZorder()) i = (i+j)/2;
//        else return _nodes[(i+j)/2];
//    }
//
//    return _nodes[(i+j)/2];
//}

const uint64_t RoadNetwork::computZorder(uint32_t lat, uint32_t lon) const {
     static const uint64_t MASKS[] = 
                    {0x5555555555555555, 0x3333333333333333, 
                     0x0F0F0F0F0F0F0F0F, 0x00FF00FF00FF00FF,
                     0x0000FFFF0000FFFF, 0X00000000FFFFFFFF};
    static const uint64_t SHIFTS[] = {1, 2, 4, 8, 16, 32};

    uint64_t x = lat;
    uint64_t y = lon;

    for(int i=5; i>=0; --i) {
        x = (x | (x << SHIFTS[i])) & MASKS[i];
        y = (y | (y << SHIFTS[i])) & MASKS[i];
    }

    return x | (y<<1);   
}
