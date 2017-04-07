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

#include<map>
#include<vector>
#include<utility>


void readCo() {
    int cunt = 0;
    std::string line;
    std::ifstream input( "../USA-road-d.BAY.co");

    std::map<int, std::pair<int, int> > m;
    std::vector<int> tokens;
    int number;

    while (std::getline(input, line)) {
        if(line.find("v") != 0) continue;
        ++cunt;
        tokens.clear();
        line.erase(0,2);
        std::istringstream ss(line);
        //std::cout << cunt << ": " << line << std::endl;
        //std::cout << cunt << ": ";
        while ( ss >> number )
            tokens.push_back( number ); 
        m[tokens[0]] = std::make_pair(tokens[1], tokens[2]);
        //for (int i : tokens) {
        //    std::cout << i << " ";
        //}
        //std::cout << std::endl;
        if(cunt == 10) break;
    }

    for (auto it=m.begin(); it!=m.end(); ++it)
        std::cout << it->first << " => " << it->second.first << ", " << it->second.second << '\n';
}

int main() {
    readCo();
}
