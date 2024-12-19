#include "raylib.h"
#include "raymath.h"
#include "game.hpp"



int main()
{
    
    InitWindow(WINDOWSIZE,WINDOWSIZE, "agario Ciociaro");
    SetTargetFPS(TFPS);

    Quadtree* Wind =  new Quadtree(1, WINDOWSIZE, 1, WINDOWSIZE);
    Wind->subdivide(4);

     while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
    
        Wind->drawDebug();

        EndDrawing();
    };

     CloseWindow();
    return 0;



}