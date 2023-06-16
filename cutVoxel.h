#ifndef CUTVOXEL_H
#define CUTVOXEL_H
#include "geometricfigure.h"

class CutVoxel : public GeometricFigure{
public:
    CutVoxel(int x0, int y0, int z0);
    void draw(Sculptor &s);
};

#endif // CUTVOXEL_H