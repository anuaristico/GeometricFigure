#ifndef PUTSPHERE_H
#define PUTSPHERE_H
#include "geometricfigure.h"

class PutSphere : public GeometricFigure{
    int raio;
public:
    PutSphere(int x0, int y0, int z0, int raio, int r, int g, int b, int a);
    void draw(Sculptor &s);
};

#endif // PUTSPHERE_H