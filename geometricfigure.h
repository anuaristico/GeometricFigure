#ifndef GEOMETRICFIGURE_H
#define GEOMETRICFIGURE_H
//#pragma once
#include <fstream>
#include <iostream>
#include "sculptor.h"

class GeometricFigure{
protected:
    int x0, y0, z0, r, g ,b, a;
public:
    GeometricFigure();
    virtual ~GeometricFigure();
    virtual void draw(Sculptor &s)=0;
};
#endif // GEOMETRICFIGURE_H