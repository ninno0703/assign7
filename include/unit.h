#ifndef UNIT_H
#define UNIT_H
#include <iostream>
struct Vec2{
    int e1;
    int e2;
    int& x(){ return e1;}
    int& y(){ return e2;}
    int& width(){return e1;}
    int& height(){return e2;}
    void move(int dx, int dy){

        if(e1+dx>=0&&e1+dx<20) e1+=dx;
        if(e2+dy>=0&&e2+dy<20) e2+=dy;
        //std::cout<<"move to "<<e1<<","<<e2<<std::endl;
    }
    int distance(const Vec2& other) const {
        return std::abs(e1 - other.e1) + std::abs(e2 - other.e2);
    }
    bool operator==(const Vec2& other) const {
        return e1 == other.e1 && e2 == other.e2;
    }
};

using Position = Vec2;

enum Color {BLACK=0, RED, GREEN, YELLOW, BLUE, PINK, CYAN, WHITE, NOCHANGE};

#endif
