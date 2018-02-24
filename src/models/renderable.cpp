//
// Created by Kenneth Halim on 2/24/18.
//
#include <applib>
using namespace std;

vector<Point>& Renderable::getPoints() {
    return points;
}


vector<Renderable *> Renderable::parseFile(string filename) {
    vector<Renderable *> result;
    FILE * pFile;
    pFile = fopen(filename.c_str(),"r");
    fprintf(stderr,"Reading new File: %s\n", filename.c_str());
    int q;
    while(fscanf(pFile, "%d", &q) && q!= -999) {

        int x, y;

        fprintf(stderr,"Reading shape with %d point\n", q);
        Renderable *buffer = new Renderable();
        while(q--) {

            fscanf(pFile, "%d %d\n", &x, &y);
            fprintf(stderr,"Reading point: %d %d\n",x ,y);
            Point pBuff(x,y);
            buffer->getPoints().push_back(pBuff);
        }
        result.push_back(buffer);
    }
    return result;
}