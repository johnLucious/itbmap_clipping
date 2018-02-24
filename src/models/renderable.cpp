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