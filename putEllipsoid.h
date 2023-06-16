#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H
#include "geometricfigure.h"

class PutEllipsoid : public GeometricFigure{
    int rx, ry, rz;
public:
    PutEllipsoid(int x0, int y0, int z0, int rx, int ry, int rz, int r, int g, int b, int a);
    void draw(Sculptor &s);
};

#endif // PUTELLIPSOID_H