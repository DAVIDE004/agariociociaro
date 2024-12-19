#include "game.hpp"

#define POINTSRADIUS 1

void point::Drawpoint() {
	DrawCircle(cordXp,cordYp,POINTSRADIUS,RED);
}

Quadtree::Quadtree(int X1 , int X2 , int Y1, int Y2) {
	CordXMin = X1;
	CordXMax = X2;
	CordYMin = Y1;
	CordYMax = Y2;
}

void Quadtree::activate() {
	if((CordXMax - CordXMin) == 256) IsLeaf = true;

	if (IsLeaf== true){
		point *pt=  new point(CordXMax,CordYMax);
		pt->Drawpoint();
	}
	else {
        int diffX = (CordXMax - CordXMin)/2;
        int diffY = (CordYMax - CordYMin)/2;
        
		ul = new Quadtree(CordXMin, CordXMin + diffX, CordYMin, CordYMin + diffY);
		ur = new Quadtree(CordXMin + diffX, CordXMax, CordYMin, CordYMin + diffY);
		ll = new Quadtree(CordXMin, CordXMin + diffX, CordYMin + diffY, CordYMax);
		lr = new Quadtree(CordXMin + diffX, CordXMax, CordYMin + diffY, CordYMax);
		ul->activate();
		ur->activate();
		ll->activate();
		lr->activate();
	}
}

void Quadtree::subdivide(int n)
{
    if (n == 0) IsLeaf = true;
    else {
        int diffX = (CordXMax - CordXMin)/2;
        int diffY = (CordYMax - CordYMin)/2;
        
		ul = new Quadtree(CordXMin, CordXMin + diffX, CordYMin, CordYMin + diffY);
		ur = new Quadtree(CordXMin + diffX, CordXMax, CordYMin, CordYMin + diffY);
		ll = new Quadtree(CordXMin, CordXMin + diffX, CordYMin + diffY, CordYMax);
		lr = new Quadtree(CordXMin + diffX, CordXMax, CordYMin + diffY, CordYMax);

		ul->subdivide(n-1);
		ur->subdivide(n-1);
		ll->subdivide(n-1);
		lr->subdivide(n-1);
    }
}

void Quadtree::drawDebug(float alpha)
{
    Color color = ColorAlpha(GOLD, alpha);

    DrawLine(CordXMin, CordYMin, CordXMax, CordYMin, color);
    DrawLine(CordXMin, CordYMax, CordXMax, CordYMax, color);
    DrawLine(CordXMin, CordYMin, CordXMin, CordYMax, color);
    DrawLine(CordXMax, CordYMin, CordXMax, CordYMax, color);

    if (IsLeaf) return;

    float p = 0.15;
    ul->drawDebug(alpha - p);
    ur->drawDebug(alpha - p);
    ll->drawDebug(alpha - p);
    lr->drawDebug(alpha - p);
}
