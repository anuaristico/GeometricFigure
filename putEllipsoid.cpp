#include "putEllipsoid.h"

PutEllipsoid::PutEllipsoid(int x0, int y0, int z0, int rx, int ry, int rz, int r, int g, int b, int a){
    this->x0=x0; this->y0=y0; this->z0=z0;
    this->rx=rx; this->ry=ry; this->rz=rz;
    this->r=r; this->g=g; this->b=b; this->a=a;
}

void PutEllipsoid::draw(Sculptor &s){
    s.setColor(r, g, b, a);
    s.putEllipsoid(x0, y0, z0, rx, ry, rz);
}
