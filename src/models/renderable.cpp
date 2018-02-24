//
// Created by Kenneth Halim on 2/24/18.
//
#include <applib>
using namespace std;
vector<Renderable> Renderable::parseFile(string filename) {
    vector<Renderable> result;
    FILE * pFile;

    pFile = fopen (filename,"r");
    int q;
    int x,y;
    fscanf(pFile, "%d",&q);
    printf("%d\n",q);
    return result;
}

void Renderable::createBorder(){
	vector<int>::iterator itr;
	int steep;
	int x1,x2,y1,y2;
	int dx,dy;
	int derr,err;
	int x,y;
	for (int i = 0; i < points.size(); i++)
	{
		Point t1 = points[i];
		Point t2 = points[i+1% points.size()];
		x1 = t1.getX();
		x2 = t2.getX();
		y1 = t1.getY();
		y2 = t2.getY();

		//cout << *itr << endl;
		steep = 0;
		if(abs(x1-x2) < abs(y1-y2)){
	        swap(x1, y1);
	        swap(x2, y2);
	        steep = 1;
	    }
	    if(x1 > x2){
	        swap(x1,x2);
	        swap(y1,y2);
	    }
	    dx = x2-x1;
	    dy = y2-y1;
	    derr = 2 * abs(dy);
	    err = 0;
	    y = y1;
	    for(x = x1; x <= x2; x++){
	        if(steep){
	            //printPixel(y,x,colorR,colorG,colorB);
	            pixels[y][x] = true;
	        }else{
	            //printPixel(x,y,colorR,colorG,colorB);
	            pixels[x][y] = true;
	        }
	        err+=derr;
	        if(err > dx){
	            y += (y2>y1)?1:-1;
	            err -= 2 * dx;
	        }
	    }
	}
}

/*void drawLine(point p1, point p2, int thickness, int colorR, int colorG, int colorB){//Bresenham
    int x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
    int steep = 0;
    if(abs(x1-x2) < abs(y1-y2)){
        swap(&x1, &y1);
        swap(&x2, &y2);
        steep = 1;
    }
    if(x1 > x2){
        swap(&x1,&x2);
        swap(&y1,&y2);
    }
    int dx = x2-x1;
    int dy = y2-y1;
    int derr = 2 * abs(dy);
    int err = 0;
    int y = y1;
    for(int x = x1; x <= x2; x++){
        if(steep){
            printPixel(y,x,colorR,colorG,colorB);
        }else{
            printPixel(x,y,colorR,colorG,colorB);
        }
        err+=derr;
        if(err > dx){
            y += (y2>y1)?1:-1;
            err -= 2 * dx;
        }
    }
}*/