/*************************************************************************
	> File Name: zOrder.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Apr 2017 11:44:31 AM AEST
 ************************************************************************/

#include<iostream>
#include<bitset>

uint64_t calcZOrder(uint32_t xPos, uint32_t yPos)
{
    static const uint64_t MASKS[] = 
                    {0x5555555555555555, 0x3333333333333333, 
                     0x0F0F0F0F0F0F0F0F, 0x00FF00FF00FF00FF,
                     0x0000FFFF0000FFFF, 0X00000000FFFFFFFF};
    static const uint64_t SHIFTS[] = {1, 2, 4, 8, 16, 32};

    uint64_t x = xPos;  // Interleave lower 16 bits of x and y, so the bits of x
    uint64_t y = yPos;  // are in the even positions and bits from y in the odd;

    std::cout<<std::bitset<64>(x)<<std::endl;

    x = (x | (x << SHIFTS[5])) & MASKS[5];
    x = (x | (x << SHIFTS[4])) & MASKS[4];
    x = (x | (x << SHIFTS[3])) & MASKS[3];
    x = (x | (x << SHIFTS[2])) & MASKS[2];
    x = (x | (x << SHIFTS[1])) & MASKS[1];
    x = (x | (x << SHIFTS[0])) & MASKS[0];

    std::cout<<std::bitset<64>(x)<<std::endl;
    std::cout <<std::endl;
    std::cout<<std::bitset<64>(y)<<std::endl;

    y = (y | (y << SHIFTS[5])) & MASKS[5];
    y = (y | (y << SHIFTS[4])) & MASKS[4];
    y = (y | (y << SHIFTS[3])) & MASKS[3];
    y = (y | (y << SHIFTS[2])) & MASKS[2];
    y = (y | (y << SHIFTS[1])) & MASKS[1];
    y = (y | (y << SHIFTS[0])) & MASKS[0];

    std::cout<<std::bitset<64>(y)<<std::endl;
    std::cout <<std::endl;
    const uint64_t result = x | (y << 1);
    return result;
}

int main() {
    uint32_t x = 122999690;
    uint32_t y = 121675244;

    uint64_t r = calcZOrder(x,y);

    std::cout<<std::bitset<64>(r)<<std::endl;
    
}
