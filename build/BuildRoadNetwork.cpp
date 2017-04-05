/*************************************************************************
	> File Name: BuildRoadNetwork.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2017 09:51:12 AM AEST
 ************************************************************************/

//#include "BuildRoadNetwork.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


void readCo() {
    int cunt = 0;
    std::string line;
    std::ifstream input( "../USA-road-d.BAY.co");

    while (std::getline(input, line)) {
        if(line.find("v") != 0) continue;
        ++cunt;
        line.erase(0,2);
        std::istringstream ss(line);
        //std::cout << cunt << ": " << line << std::endl;
        //std::cout << cunt << ": " << ss[1] << " " << ss[2] << ", " << ss[3] << std::endl;
        std::cout << cunt << ": ";
        for (int n=0; n<3; n++) {
            int val;
            ss >> val;
            std::cout << val << " ";
        }
        std::cout << std::endl;
        if(cunt == 10) break;
    }
}

int main() {
    readCo();
}
