#include "cutEllipsoid.h"

CutEllipsoid::CutEllipsoid(int x0, int y0, int z0, int rx, int ry, int rz)
{
    this->x0 = x0; this->y0 = y0; this->z0 = z0;
    this->rx = rx; this->ry = ry; this->rz = rz;
}

void CutEllipsoid::draw(Sculptor &s)
{
    s.cutEllipsoid(x0, y0, z0, rx, ry, rz);
}
