#ifndef PUTBOX_H
#define PUTBOX_H
#include "geometricfigure.h"

class PutBox : public GeometricFigure{
    int x1, y1, z1;
public:
    PutBox(int x0, int x1, int y0, int y1, int z0, int z1, int r, int g, int b, int a);
    void draw(Sculptor &s);
};

#endif // PUTBOX_H