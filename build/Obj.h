/*************************************************************************
	> File Name: Obj.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 12:24:42 PM AEST
 ************************************************************************/

#ifndef _OBJ_H
#define _OBJ_H

#include<vector>
#include<pair>

class Obj {
public:
    Obj(int lat, int lon, const std::pair<long>& dist, const std::vector<long>& terms) :
                _oLat{lat}, _oLon{lon},
                _oDist{dist}, _oTerms{terms} {};
    const std::vector<long>& getTerms() const;
    const std::pair<long>& getDist() const;

private:
    int _oLat;
    int _oLon;
    std::pair<long, long> _oDist;
    std::vector<long> _oTerms
}
#endif
