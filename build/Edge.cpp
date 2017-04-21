/*************************************************************************
	> File Name: Edge.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 01:29:21 PM AEST
 ************************************************************************/

#include "Edge.h"
#include "Node.h"


Edge::Edge(sPtr n1, sPtr n2, const float dist) {
//Edge::Edge(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, const uint32_t dist) {
    _eWeight = dist;
    _endNode = std::make_pair<wPtr, wPtr> (n1, n2);
    _midPoint = std::make_pair<uint32_t, uint32_t>((n1->getLat()+n2->getLat())/2, (n1->getLon()+n2->getLon())/2);
}

void Edge::addObj(oPtr obj) {
    _obj.push_back(obj);
}

float Edge::dist2Edge(oPtr obj) const {
    return dist2Edge(obj->getLat(), obj->getLon());
}

float Edge::dist2Edge(uint32_t lat, uint32_t lon) const {
    double lat1 = _midPoint.first/1000000.0;
    double lon1 = _midPoint.second/1000000.0;
    double lat2 = lat/1000000.0;
    double lon2 = lon/1000000.0;

    double R = 6371;
    double dLat = (lat2-lat1)*(std::acos(-1)/180.0);
    double dLon = (lon2-lon1)*(std::acos(-1)/180.0);
    double a = std::sin(dLat/2) * std::sin(dLat/2) +
                std::cos(lat1*(std::acos(-1)/180.0)) * std::cos(lat2*(std::acos(-1)/180.0)) * std::sin(dLon/2) * std::sin(dLon/2);

    return R * 2 * std::atan2(std::sqrt(a), std::sqrt(1-a)); 
}

std::vector<Edge::oPtr>& Edge::getObj(const std::vector<uint32_t>& terms) {
    return _obj;
}

std::vector<Edge::oPtr> Edge::matchObj(const std::vector<uint32_t>& terms) {
    std::vector<oPtr> result;
    std::vector<std::pair<iter, iter> > candidates;
    uint32_t curMax = 0;
    size_t index = 0;
    size_t len = 0;
    
    if(_if.size() == 0) buildIF();

    for(const uint32_t t : terms) {
        if(_if.find(t) == _if.end()) return result;    
        candidates.push_back(std::make_pair(_if[t].begin(),
                                            _if[t].end()));
        ++len;
    }
    //std::cout << "after push candidates" << std::endl;
    //std::cout << "len = " << len << std::endl;

    if(len == 1) {
        result.assign(candidates[0].first, candidates[0].second);
       return result; 
    }
        


    while(true) {
        if(curMax < (*candidates[index].first)->getId()) {
            curMax = (*candidates[index].first)->getId();
            index = 0;
            //std::cout << "< brunch" << std::endl;
        }
        else if(curMax > (*candidates[index].first)->getId()) {
            if(++candidates[index].first ==
               candidates[index].second) break;
            //std::cout << "> brunch" << std::endl;
        }
        else {
            if(++index == len) {
                index = 0;
                result.push_back(*candidates[index].first);
                if(++candidates[index].first == 
                        candidates[index].second) break;
            }
            //std::cout << "= brunch" << std::endl;
        }
    }

    return result;
}

void Edge::buildIF() {
    for(auto o : _obj) {
        for(const uint32_t t : o->getTerms()) {
            if(_if.find(t) == _if.end())
                _if[t] = std::vector<oPtr>(); 
            _if[t].push_back(o);
        }
    }

    //if(_if.size() == 0) {
    //    _if[NULL] = std::vector<oPtr>();
    //    return;
    //}
    
    for(auto key : _if) {
        std::sort(key.second.begin(), key.second.end(),
                 [&](oPtr o1, oPtr o2){return o1->getId() < o2->getId();});

        //for(auto it : key.second) std::cout << it->getId() << " ";
        //std::cout << std::endl;
    }
    //std::cout << "**** end ****" << std::endl;
}

//double Edge::deg2rad(double deg) const {
//    return deg * (std::acos(-1)/180.0);
//}

