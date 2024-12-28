#include "raylib.h"
#include "raymath.h"
#include "game.hpp"



int main()
{
    
    InitWindow(WINDOWSIZE,WINDOWSIZE, "agario Ciociaro");
    SetTargetFPS(TFPS);

    Quadtree* Wind =  new Quadtree(1, WINDOWSIZE, 1, WINDOWSIZE);
    Wind->subdivide(TREELAYERS);
    Wind->palline();
    player* pl1 = new player();

    Camera2D camera = { 0 };
    camera.target = (Vector2){ (float)pl1->X , (float)pl1->Y};
    camera.offset = (Vector2){ WINDOWSIZE/2.0f, WINDOWSIZE/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while(!WindowShouldClose()){
        //Events
        Wind->playercollision(pl1);

        
        if (IsKeyDown(KEY_RIGHT)) pl1->X += 2;
        else if (IsKeyDown(KEY_LEFT)) pl1->X -= 2;
        else if (IsKeyDown(KEY_UP)) pl1->Y -=2;
        else if (IsKeyDown(KEY_DOWN)) pl1->Y +=2;

        // Camera target follows player
        camera.target = (Vector2){ (float)pl1->X, (float)pl1->Y};
        
        //Drawing
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(camera);
                Wind->Drawpalline();
                Wind->drawDebug();
                
                pl1->DrawPlayer();

            EndMode2D();

        EndDrawing();
    };

    CloseWindow();
    return 0;



}