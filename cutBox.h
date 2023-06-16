#ifndef CUTBOX_H
#define CUTBOX_H
#include "geometricfigure.h"

class CutBox : public GeometricFigure{
    int x1, y1, z1;
public:
    CutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void draw(Sculptor &s);
};

#endif // CUTBOX_H