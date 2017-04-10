/*************************************************************************
	> File Name: rTreetest2.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Apr 2017 09:11:40 AM AEST
 ************************************************************************/

#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
//#include <boost/geometry/geometries/box.hpp>
#include <vector>
#include <memory>
#include <iostream>

namespace bg = boost::geometry;
namespace bgi = bg::index;
//using  point  = bg::model::point <int, 2, bg::cs::cartesian>;
//using  pointI = std::pair<point, std::size_t>;

typedef bg::model::point <float, 2, bg::cs::cartesian> point;
typedef std::shared_ptr<point> sp;
typedef std::pair<point, sp> pointI;


pointI mp(point p, sp ptr) {
    return std::make_pair(p, ptr);
}

int main()
{
    std::vector<pointI> cloud;

    for(int i=0; i<10; ++i) {
        sp p = std::make_shared<point>(point(i+0.0f, i+0.0f));
        cloud.push_back(mp(point(i+0.1f,i+0.1f), p));
    }

    //std::cout << "begin" << std::endl;
    //std::transform(
    //        contourCenters.begin(), contourCenters.end(),
    //        back_inserter(cloud), 
    //        [&](pp p) { return std::make_pair(pp); }
    //    );

    for(pointI& pi : cloud) {
        std::cout << "Contour Centers: (" << bg::get<0>(pi.first) << "," << bg::get<1>(pi.first) << ")" << std::endl;
        std::cout << "Pointers: (" << bg::get<0>(*pi.second) << "," << bg::get<1>(*pi.second) << ")" << std::endl;
    }

    bgi::rtree<pointI, bgi::quadratic<16> > rtree(cloud);
}
