#include "raylib.h"
#include "raymath.h"
#define POINTSRADIUS 1
#define LEEFDIM 1
#define WINDOWSIZE 1024
#define TFPS 30






class point{
    public:
        int cordXp,cordYp;
        point(int X, int Y){
            cordXp = X;
            cordYp = Y;
    }
    
    void Drawpoint(){
        DrawCircle(cordXp,cordYp,POINTSRADIUS,RED);
    }
};

class Quadtree{
    public:
        Quadtree *ul  = NULL;
        Quadtree *ur  = NULL;
        Quadtree *ll  = NULL;
        Quadtree *lr  = NULL;

        bool IsLeaf ;
       


        int CordXMin;
        int CordXMax;
        int CordYMin;
        int CordYMax;

        Quadtree(int X1 , int X2 , int Y1, int Y2){
            CordXMin = X1;
            CordXMax = X2;
            CordYMin = Y1;
            CordYMax = Y2;
        }
            

        void checkleef(){
            if((CordXMax - CordXMin) == 0) IsLeaf = true;
            
        }

        void activate(){
            this->checkleef();
            
            if (IsLeaf== true){
                point *pt=  new point(CordXMax,CordYMax);
                pt->Drawpoint();
            }
            else {
            ul = new Quadtree(CordXMin, CordXMax/2, CordYMin, CordYMin/2);
            ur = new Quadtree(CordXMax/2, CordXMax, CordYMin, CordYMin/2);
            ll = new Quadtree(CordXMin, CordXMax/2, CordYMax/2, CordYMax);
            lr = new Quadtree(CordXMax/2, CordXMax, CordYMax/2, CordYMax);
            ul->activate();
            ur->activate();
            ll->activate();
            lr->activate();

            }
        }
        

        



};



int main()
{
    Quadtree* Wind =  new Quadtree(1, WINDOWSIZE, 1, WINDOWSIZE);
    InitWindow(WINDOWSIZE,WINDOWSIZE, "agario Ciociaro");
    SetTargetFPS(TFPS);


    

    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);
        Wind->activate();



        

        EndDrawing();
    };


    CloseWindow();
    return 0;



}