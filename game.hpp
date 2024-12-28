#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include <stdlib.h>
#include <cmath>

#define LEEFDIM 1
#define WINDOWSIZE 1024
#define TFPS 30
#define POINTFORSQUARE 2
#define DEFAULTRADIUS 6
#define TREELAYERS 4

class player{
    public:
    int X=512;
    int Y=512;
    
    int radius = DEFAULTRADIUS;
    
    Vector2 speed;
    
    

    void DrawPlayer();
};


class point{
    public:
        int cordXp,cordYp;

    point();
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
        point pointarr[POINTFORSQUARE];
       
            int CordXMin;
            int CordXMax;
            int CordYMin;
            int CordYMax;

        Quadtree(int X1 , int X2 , int Y1, int Y2);
           
        

        void subdivide(int n);
            
        void drawDebug(float alpha = 1.0);

        void palline();

        void Drawpalline();

        void playercollision(player* A);

        void leafcollision(player* A);
};

#endif