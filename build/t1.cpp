/*************************************************************************
	> File Name: t1.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 07 Apr 2017 12:11:40 PM AEST
 ************************************************************************/

#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include <sstream>
#include "stdlib.h"


void printE(uint32_t n1, uint32_t n2, const float w) {
    std::cout << n1 << ", " << n2 << " : " << w << std::endl;
}


int main() {
    uint32_t cunt = 0;
    std::string line;
    std::ifstream input("../dataset/Ca/CaRoadNetWork.gr");
    std::string tmp;
    std::vector<std::string> tokens;

    while (std::getline(input, line)) {
        ++cunt;
        tokens.clear();
        std::istringstream ss(line);
        
        while(ss >> tmp) tokens.push_back(tmp); 
        std::cout << "w: " << tokens[2] << std::endl;
        printE(abs(std::atoi(tokens[0].c_str())),
               abs(std::atoi(tokens[1].c_str())),
               std::atof(tokens[2].c_str()));

        //ePtr e = std::make_shared<Edge>(Edge(nodes[tokens[0]], nodes[tokens[1]], tokens[2]));
        //nodes[tokens[0]]->addEdge(e);
        //nodes[tokens[1]]->addEdge(e);

        if(cunt == 10) break;
    }

}


