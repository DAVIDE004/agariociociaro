#include "game.hpp"

#define POINTSRADIUS 3


point::point(){
	cordXp=0;
	cordYp=0;
}
void point::Drawpoint() {
	DrawCircle(cordXp,cordYp,POINTSRADIUS,RED);
}


Quadtree::Quadtree(int X1 , int X2 , int Y1, int Y2) {
	CordXMin = X1;
	CordXMax = X2;
	CordYMin = Y1;
	CordYMax = Y2;
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

void Quadtree::palline()
{
    if (IsLeaf) {
		
		
		for(int i = 0;i < POINTFORSQUARE; i++){
			this->pointarr[i] = *new point((rand() %(CordXMax -CordXMin+1)) +CordXMin ,(rand() %(CordYMax -CordYMin+1)) +CordYMin);
		}
		
    }
    else {
		ul->palline();
		ur->palline();
		ll->palline();
		lr->palline();
    }
}

void Quadtree:: Drawpalline()
{
	if (IsLeaf){
		for (int i = 0;i < POINTFORSQUARE; i++) this-> pointarr[i].Drawpoint();
	}
	else {
		ul->Drawpalline();
		ur->Drawpalline();
		ll->Drawpalline();
		lr->Drawpalline();
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

void Quadtree::leafcollision(player* A){
	
	for (int i = 0;i < POINTFORSQUARE; i++){
		if (CheckCollisionCircles((Vector2) {(float) pointarr[i].cordXp, (float) pointarr[i].cordYp },POINTSRADIUS, (Vector2) { (float) A->X,(float) A->Y}, A->radius)){
			A->radius +=1;
			pointarr[i].cordXp=(rand() %(CordXMax -CordXMin+1)) +CordXMin;
			pointarr[i].cordYp=(rand() %(CordYMax -CordYMin+1)) +CordYMin;
		}
	}
	
}

void Quadtree::playercollision(player* A)
{
	int diffX = (CordXMax - CordXMin)/2;
    int diffY = (CordYMax - CordYMin)/2;

	if(IsLeaf){
		leafcollision(A);
	}
	else{
		if (abs(CordXMin+diffX-A->X) <= A->radius || abs(CordYMin + diffY-A->Y) <=A->radius){
			ul->playercollision(A);
			ur->playercollision(A);
			ll->playercollision(A);
			lr->playercollision(A);
		}
		else if (abs(CordXMin + diffX-A->X) <= A->radius || A->Y <= CordYMin + diffY){
			ul->playercollision(A);
			ur->playercollision(A);
		}
		else if (abs(CordXMin+diffX-A->X) <= A->radius || A->Y > CordYMin+diffY){
			ll->playercollision(A);
			lr->playercollision(A);
		}

		else if (abs(CordYMin+diffY-A->Y) <= A->radius || A->X <= CordXMin+diffX){
			ul->playercollision(A);
			ll->playercollision(A);
		}
		else if (abs(CordYMin+diffY-A->Y) <= A->radius || A->X > CordXMin+diffX){
			ur->playercollision(A);
			lr->playercollision(A);
		}
		else if(A->X <= CordXMin+diffX || A->Y <= CordYMin+diffY) ul->playercollision(A);
		else if (A->X > CordXMin+diffX || A->Y > CordYMin+diffY) lr->playercollision(A);
		else if (A->X <= CordXMin+diffX || A->Y > CordYMin+diffY) ur->playercollision(A);
		else if (A->X > CordXMin+diffX || A->Y <= CordYMin+diffY) ll->playercollision(A);
	}
}

void player::DrawPlayer()
{
	DrawCircle(X,Y,radius,WHITE);
}