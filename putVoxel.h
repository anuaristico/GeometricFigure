#ifndef PUTVOXEL_H
#define PUTVOXEL_H
#include "geometricfigure.h"

class PutVoxel : public GeometricFigure{
public:
    PutVoxel(int x0, int y0, int z0, int r, int g, int b, int a);
    void draw(Sculptor &s);
};

#endif // PUTVOXEL_H