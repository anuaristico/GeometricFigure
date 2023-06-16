#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H
#include "geometricfigure.h"

class CutEllipsoid : public GeometricFigure{
    int rx, ry, rz;
public:
    CutEllipsoid(int x0, int y0, int z0, int rx, int ry, int rz);
    void draw(Sculptor &s);
};

#endif // CUTELLIPSOID_H