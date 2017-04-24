/*************************************************************************
	> File Name: RoadNetwork.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 01:30:19 PM AEST
 ************************************************************************/
#include "RoadNetwork.h"

//void RoadNetwork::addNode(Node& n) {
//    //_nodes.push_back(std::make_shared<Node>(n));
//}

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

std::vector<RoadNetwork::oPtr> RoadNetwork::searchCandidates(uint32_t lat, uint32_t lon, std::vector<uint32_t>& terms, const float& maxDist) {
    auto comp = [](nPtr a, nPtr b) { return a->getDist() < b->getDist(); };
    std::priority_queue<nPtr, std::vector<nPtr>, decltype(comp)> minqueue(comp);
    std::vector<oPtr> candidates;

    nPtr node = nearestNode(point(lat, lon));
    ePtr edge = nearestEdge(point(lat, lon));

    node->setDist(node->dist2Node(lat, lon));
    minqueue.push(node);
    nPtr n1 = edge->getEndNode().first.lock();
    nPtr n2 = edge->getEndNode().second.lock();
    n1->setDist(n1->dist2Node(lat, lon));
    n2->setDist(n2->dist2Node(lat, lon));
    minqueue.push(n1);
    minqueue.push(n2);
    for(oPtr o : edge->matchObj(terms)) {
        o->setDist(o->dist2Obj(lat, lon));
    }

    //if(node->dist2Node(lat, lon) < edge->dist2Edge(lat, lon)) {
    //    node->setDist(node->dist2Node(lat, lon));
    //    minqueue.push(node);
    //} else {
    //    nPtr n1 = edge->getEndNode().first.lock();
    //    nPtr n2 = edge->getEndNode().second.lock();
    //    n1->setDist(n1->dist2Node(lat, lon));
    //    n2->setDist(n2->dist2Node(lat, lon));
    //    for(oPtr o : edge->matchObj(terms)) {
    //        o->setDist(o->dist2Obj(lat, lon));
    //    }
    //}

    while(!minqueue.empty()) {
        nPtr n = minqueue.top();
        minqueue.pop();
        std::cout << "Node: " << n->getLat() << ", " << n->getLon() << " => ";
        std::cout << "dist = " << n->getDist() << " <=> " << n->dist2Node(lat, lon) << std::endl;
        if(n->getDist() > maxDist) break;
        n->markNode();
        for(ePtr e : n->getEdges()) {
            nPtr n1 = e->getEndNode().first.lock();
            nPtr n2 = e->getEndNode().second.lock();
            //nPtr ni = *e->getEndNode().first == *n ? e->getEndNode().second : e->getEndNode().first;
            nPtr ni = *n1 == *n ? n2 : n1;
            //std::cout << "nid: " << n->getId() << " <=> "
            //<< "niid: " << ni->getId() << std::endl;

            if(ni->getDist() > e->getWeight()+n->getDist()) {
                //if(ni->isMarked()) {
                //    ni->setDist(e->getWeight() + n->getDist());
                //    minqueue.push(ni);
                //}
                
                ni->setDist(e->getWeight() + n->getDist());
            }


            if(ni->isMarked()) {
                for(auto o : e->matchObj(terms)) {
                    if(o->getDist()>n->getDist()+n->dist2Node(o))
                        o->setDist(n->getDist()+n->dist2Node(o));
                }
            }
            else {
                //if(ni->getDist() > e->getWeight()+n->getDist()) 
                //    ni->setDist(e->getWeight() + n->getDist());
                for(auto o : e->matchObj(terms)) {
                    o->setDist(n->getDist()+n->dist2Node(o));
                    std::cout << "push" << std::endl;
                    candidates.push_back(o);
                }
                minqueue.push(ni);
            }
        }
    }

    size_t cunt = 0;
    std::cout << "qurey: " << lat << ", " << lon << std::endl;
    std::cout << "Node: " << node->getLat() << ", " <<
    node->getLon() << " => " << std::endl;
    std::cout << "#candidate: " << candidates.size() <<std::endl;

    for(oPtr o : candidates) {
        if(o->getDist()>maxDist) continue;
        std::cout << ++cunt << " => ";
        std::cout << o->getLat() << ", " << o->getLon() << ", " << o->getDist() << "<=>" << o->dist2Obj(lat, lon) <<  ": ";
        for(const uint32_t t : o->getTerms()) 
            std::cout << t << ", ";
        std::cout << std::endl;
    }



    //std::cout << "qurey: " << lat << ", " << lon << std::endl;
    //std::cout << "Node: " << node->getLat() << ", " <<
    //node->getLon() << " => " << std::endl;
    //for(auto e : node->getEdges()) {
    //    std::cout << ++cunt << " => ";
    //    for(auto o : e->matchObj(terms)) {
    //        std::cout << o->getLat() << ", " << o->getLon() <<
    //        ": ";
    //        for(const uint32_t t : o->getTerms()) {
    //            std::cout << t << ", ";
    //        }
    //        std::cout << std::endl;
    //    }
    //    std::cout << std::endl;
    //}
    
    return candidates;
}

void RoadNetwork::updateCP(CP& cp, oPtr& o, uint32_t qLat, uint32_t qLon, float a, size_t k, float maxDist, float threshold) {
    std::vector<std::pair<std::pair<oPtr, float>, size_t> > v;
    float t1 = 0;
    float t2 = 0;

    //std::cout << "updateCP" << std::endl;
    //std::sort(cp.begin(), cp.end(), [](auto a, auto b){
    //    return a.second >b.second;
    //});
    
    //for(auto p : cp) 
    //    std::cout << p.second << ", ";
    //std::cout << std::endl;

    //float threshold = cp[k-1].second;
    //std::cout << "threshold: " << threshold << ", ";

    for(auto it=cp.begin(); it!=cp.end(); ++it) {
        t1 = computDiversifyDist(qLat, qLon, o, it->first.first, a, maxDist);
        //std::cout << "t1: " << t1 << ", ";
        if(it->first.second != NULL) {
            t2 = computDiversifyDist(qLat, qLon, o, it->first.second, a, maxDist);
            //std::cout << "t2: " << t2 << std::endl;
        } else 
            t2 = 0;

        //if(t1>threshold)
        //    std::cout << "exceed: " << t1 << ", " << it->second << std::endl;
        //if(t2>threshold)
        //    std::cout << "exceed: " << t2 << ", " << it->second << std::endl;

        if(t1 > threshold && t1 > it->second)
            v.push_back(std::make_pair(std::make_pair(it->first.first, t1), it-cp.begin()));

        if(t2 > threshold && t2 > it->second)
            v.push_back(std::make_pair(std::make_pair(it->first.second, t2), it-cp.begin()));
    }
    
    if(v.empty()) {
        std::cout << "o' empty" << std::endl;
        cp.push_back(std::make_pair(std::make_pair(o, oPtr()), 0.0));
        std::cout << "return" << std::endl;
        return;   
    }

    std::cout << "get o': " << v.size() << std::endl;
    //for(auto p : v) 
    //    std::cout << p.first.first->getLat() << ", " << p.first.first->getLon() << std::endl;

    std::pair<std::pair<oPtr, float>, size_t>& o2 = *std::max_element(v.begin(), v.end(),
            //[oPtr& o](auto a, auto b){
            [&o](auto a, auto b){
                return o->dist2Obj(*a.first.first) > o->dist2Obj(*b.first.first);
            });

    std::cout << "get farthest" << std::endl;
    std::cout << "o2.second: " << o2.second << std::endl;
    

    if(o2.second >= k) {
        std::cout << "if not core pair" << std::endl;

        cp.push_back(std::make_pair(std::make_pair(o2.first.first, o), o2.first.second));
        cp.push_back(std::make_pair(std::make_pair(cp[k-1].first.first, oPtr()), 0.0));
        cp.push_back(std::make_pair(std::make_pair(cp[k-1].first.second, oPtr()), 0.0));
        cp.erase(cp.begin()+k-1);
        return;
    }
    else {
        std::cout << "if core pair" << std::endl;

        cp.push_back(std::make_pair(std::make_pair(o2.first.first, o), o2.first.second));
        //if(*cp[o2.second].first.firsti != *o2.first.first) 
        //    cp.push_back(std::make_pair(std::make_pair(cp[o2.second].first.first, NULL), 0));
        //else 
        //    cp.push_back(std::make_pair(std::make_pair(cp[o2.second].first.second, NULL), 0));


        oPtr tmp = (*cp[o2.second].first.first != *o2.first.first)? cp[o2.second].first.first : cp[o2.second].first.second;

        cp.erase(cp.begin()+o2.second);

        std::sort(cp.begin(), cp.end(), [](auto a, auto b){
            return a.second >b.second;
        });

        std::cout << "sort and recursive call" << std::endl;

        updateCP(cp, tmp, qLat, qLon, a, k, maxDist, cp[k-1].second);
        std::cout << "finished recursive call" << std::endl;
        return;
    }
}

void RoadNetwork::Sksearch(uint32_t qLat, uint32_t qLon, float a, size_t k, float maxDist, std::vector<uint32_t> terms) {
    CP cp;
    std::vector<oPtr> candidates = searchCandidates(qLat, qLon,
                                                    terms,
                                                    maxDist);
    float threshold = 0;
    oPtr tmp = NULL;

    std::sort(candidates.begin(), candidates.end(), [&qLat, &qLon](const oPtr& o1, const oPtr& o2) {
        return o1->dist2Obj(qLat, qLon) < o2->dist2Obj(qLat, qLon);
    });

    for(oPtr o : candidates) {
        //std::cout << "iterat candidates" << std::endl;
        if(cp.size() < k) {
            if(tmp != NULL) {
                float ddist = computDiversifyDist(qLat, qLon, tmp, o, a, maxDist);

                cp.push_back(std::make_pair(std::make_pair(tmp, o), ddist));
                //threshold = std::min(threshold, ddist);

                tmp = NULL;
            }
            else
                tmp = o;

            continue;
        } 


        std::cout << std::endl;
        std::cout << "updateCP() start: " << threshold << std::endl;
        updateCP(cp, o, qLat, qLon, a, k, maxDist, threshold);
        std::cout << "updateCP() returned" << std::endl;

        std::sort(cp.begin(), cp.end(), [](auto a, auto b){
            return a.second >b.second;
        });

        std::cout << "core pairs => " << std::endl;
        for(auto it=cp.begin(); it!=cp.begin()+k; ++it) {
            //std::cout << "(" << it->first.first->getLat() << ", "
            //          << it->first.first->getLon() << "), " << "("
            //          << it->first.second->getLat() << ", " 
            //          << it->first.second->getLon() << ") : "
            //          << it->first.first->dist2Obj(*it->first.second) << std::endl;

            std::cout << "(" << it->first.first->getId() << ", "
                      << it->first.second->getId() << ") : "
                      << it->first.first->dist2Obj(*it->first.second) << std::endl;
        }
        std::cout << std::endl;


        threshold = cp[k-1].second;
        float dist2q = o->dist2Obj(qLat, qLon);
        
        if(computDiversifyDist(dist2q, dist2q, 2.0*maxDist, a, maxDist) < threshold) {
            bool terminate = 1;
            for(auto p : cp) {
                float tmp = computDiversifyDist(dist2q, p.first.first->dist2Obj(qLat,qLon), 2.0*dist2q, a, maxDist);
                if(tmp>threshold) {
                    terminate = 0;
                    break;
                }

                if(p.first.second != NULL) {
                    tmp = computDiversifyDist(dist2q, p.first.second->dist2Obj(qLat,qLon), 2.0*dist2q, a, maxDist);
                    if(tmp>threshold) {    
                        terminate = 0;
                        break;
                    }
                }
            } 
            if(terminate) {
                std::cout << "terminate expansion!" << std::endl;
                break;
            }
        }
    }


    std::cout << "core pairs => " << std::endl;
    for(auto it=cp.begin(); it!=cp.begin()+k; ++it) {
        std::cout << "(" << it->first.first->getLat() << ", "
                  << it->first.first->getLon() << "), " << "("
                  << it->first.second->getLat() << ", " 
                  << it->first.second->getLon() << ") : "
                  << it->first.first->dist2Obj(*it->first.second) << std::endl;
    }
}

//void RoadNetwork::query(uint32_t lat, uint32_t lon, std::vector<uint32_t> terms) {
//    //auto comp = [](nPtr a, nPtr b) { return a->score() < b->score(); };
//    //priority_queue<nPtr, vector<nPtr>, decltype(comp)> minqueue(comp);
//    nPtr node = nearestNode(point(lat, lon));
//    size_t cunt = 0;
//    std::cout << "qurey: " << lat << ", " << lon << std::endl;
//    std::cout << "Node: " << node->getLat() << ", " <<
//    node->getLon() << " => " << std::endl;
//    for(auto e : node->getEdges()) {
//        std::cout << ++cunt << " => ";
//        for(auto o : e->matchObj(terms)) {
//            std::cout << o->getLat() << ", " << o->getLon() <<
//            ": ";
//            for(const uint32_t t : o->getTerms()) {
//                std::cout << t << ", ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//    }
//}

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
        uint32_t id = tokens[0];
        uint32_t lat = tokens[len-2];
        uint32_t lon = tokens[len-1];
        //uint64_t zOrder = computZorder(lat, lon);
        uint64_t zOrder = 0;
        tokens.erase(tokens.begin());
        tokens.pop_back();
        tokens.pop_back();

        oPtr o = std::make_shared<Obj>(Obj(id, lat, lon, zOrder, tokens));
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

    //searchCandidates(33025158,114523370, std::vector<uint32_t>{3, 117}, 1000);
    Sksearch(33025158,114523370, 0.1, 3, 2000, std::vector<uint32_t>{3, 117});
    //Sksearch(37439384, 122051350, 0.1, 2, 50, std::vector<uint32_t>{11});
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


float RoadNetwork::computDiversifyDist(uint32_t qLat, uint32_t qLon, oPtr o1, oPtr o2, float a, uint32_t maxDist) const {
    float tmp1 = 2.0 - o1->dist2Obj(qLat, qLon)/maxDist 
                     - o2->dist2Obj(qLat, qLon)/maxDist;

    float tmp2 = (1-a)*(o1->dist2Obj(*o2))/maxDist;
    
    return a*tmp1+tmp2;
}

float RoadNetwork::computDiversifyDist(float dist_q_u, float dist_q_v,  float dist_u_v, float a, uint32_t maxDist) const {
    float tmp1 = 2.0 - (dist_q_u+dist_q_v)/maxDist;

    float tmp2 = (1-a)*dist_u_v/maxDist;
    
    return a*tmp1+tmp2;
}

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
