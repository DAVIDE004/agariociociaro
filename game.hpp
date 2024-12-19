#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"

#define LEEFDIM 1
#define WINDOWSIZE 1024
#define TFPS 30


class point{
    public:
        int cordXp,cordYp;

    point(int X, int Y) : cordXp( X ), cordYp( Y ) {}

    void Drawpoint();
};

class Quadtree{
    public:
        Quadtree *ul  = nullptr;
        Quadtree *ur  = nullptr;
        Quadtree *ll  = nullptr;
        Quadtree *lr  = nullptr;

        bool IsLeaf = false;
       
            int CordXMin;
            int CordXMax;
            int CordYMin;
            int CordYMax;

        Quadtree(int X1 , int X2 , int Y1, int Y2);
           
        void activate();

        void subdivide(int n);
            
        void drawDebug(float alpha = 1.0);
};

#endif