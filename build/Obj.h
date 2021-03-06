/*************************************************************************
	> File Name: Obj.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 12:24:42 PM AEST
 ************************************************************************/

#ifndef _OBJ_H
#define _OBJ_H

#include<vector>
#include<cmath>
#include"stdint.h"
#include<utility>

class Obj {
public:
    Obj(uint32_t oid, uint32_t lat, uint32_t lon, uint64_t zOrder,
        const std::vector<uint32_t>& terms) :
            _oId{oid}, _oLat{lat}, _oLon{lon}, _zOrder{zOrder},
            _oTerms{terms} {};


//    Obj(uint32_t oid, uint32_t lat, uint32_t lon, uint64_t zOrder,
//        const float dist = std::numeric_limits<float>::max(),
//        const std::vector<uint32_t>& terms) :
//            _oId{oid}, _oLat{lat}, _oLon{lon}, _zOrder{zOrder},
//            _dist{dist}, _oTerms{terms} {};

//    Obj(uint32_t lat, uint32_t lon, uint64_t zOrder,
//        const std::pair<float, float>& dist,
//        const std::vector<uint32_t>& terms) :
//            _oLat{lat}, _oLon{lon}, _zOrder{zOrder},
//            _oDist{dist}, _oTerms{terms} {};

    //const std::vector<uint32_t>& getTerms() const;
    const uint32_t getId() const {return _oId;};
    const uint32_t getLat() const {return _oLat;};
    const uint32_t getLon() const {return _oLon;};
    float dist2Obj(const Obj& other) const;
    float dist2Obj(uint32_t lat, uint32_t lon) const;
    const float& getDist() const {return _oDist; };
    void setDist(const float& dist) {_oDist = dist; };

    const std::vector<uint32_t> getTerms() const {return _oTerms;};

    bool operator==(const Obj &other) const;
    bool operator!=(const Obj &other) const {
        return !(*this == other);
    };


private:
    uint32_t _oId;
    uint32_t _oLat;
    uint32_t _oLon;
    uint64_t _zOrder;
    float _oDist;
    std::vector<uint32_t> _oTerms;
};
#endif
