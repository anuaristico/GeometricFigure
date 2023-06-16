#ifndef CUTSPHERE_H
#define CUTSPHERE_H
#include "geometricfigure.h"

class CutSphere : public GeometricFigure{
    int raio;
public:
    CutSphere(int x0, int y0, int z0, int raio);
    void draw(Sculptor &s);
};

#endif // CUTSPHERE_H