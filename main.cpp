#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "geometricfigure.h"
#include "sculptor.h"
#include "putVoxel.h"
#include "cutVoxel.h"
#include "putBox.h"
#include "cutBox.h"
#include "putSphere.h"
#include "cutSphere.h"
#include "putEllipsoid.h"
#include "cutEllipsoid.h"

int main(){
    GeometricFigure *pf;
    std::vector<GeometricFigure*> figs;

    std::ifstream fin;
    std::ofstream fout;
    std::string s;

    fin.open("figura.txt");

    int nx, ny, nz;
    fin >> s;
    if(s.compare("dim")==0){
    fin >> nx >> ny >> nz;
    }
    Sculptor sc(nx, ny, nz);

    while(fin.good()){
        fin >> s;
        if(fin.good()){
            if(s.compare("putVoxel")==0){
                int x, y, z, r, g, b, a;
                fin >> x >> y >> z >> r >> g >> b >> a;
                figs.push_back(new PutVoxel(x,y,z,r,g,b,a));
            }
            if(s.compare("putBox")==0){
                int x0, y0, z0, x1, y1, z1, r, g, b, a;
                fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
                figs.push_back(new PutBox(x0, y1, y0, y1, z0, z1, r, g, b, a));
            }
            if(s.compare("putEllipsoid")==0){
                int x, y, z, rx, ry, rz, r, g, b, a;
                fin >> x >> y >> rx >> ry >> rz >> r >> g >> b >> a;
                figs.push_back(new PutEllipsoid(x, y, z, rx, ry, rz, r, g, b, a));
            }
            if(s.compare("putSphere")==0){
                int x, y, z, raio, r, g, b, a;
                fin >> x >> y >> z >> raio >> r >> g >> b >> a;
                figs.push_back(new PutSphere(x,y,z,raio,r,g,b,a));
            }
            if(s.compare("cutVoxel")==0){
                int x, y, z;
                fin >> x >> y >> z;
                figs.push_back(new CutVoxel(x,y,z));
            }
            if(s.compare("cutBox")==0){
                int x0, y0, z0, x1, y1, z1;
                fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
                figs.push_back(new CutBox(x0, x1, y0, y1, z0, z1));
            }
            if(s.compare("cutEllipsoid")==0){
                int x, y, z, rx, ry, rz;
                fin >> x >> y >> rx >> ry >> rz;
                figs.push_back(new CutEllipsoid(x, y, z, rx, ry, rz));
            }
            if(s.compare("cutSphere")==0){
                int x, y, z, raio;
                fin >> x >> y >> z >> raio;
                figs.push_back(new CutSphere(x,y,z,raio));
            }
        }
    }

    for(auto fig:figs){
        fig->draw(sc);
    }

    sc.writeOFF("saida2.off");

    for(auto fig:figs){
        delete fig;
    }

    return 0;
}