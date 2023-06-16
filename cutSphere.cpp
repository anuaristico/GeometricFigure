#include "cutSphere.h"

CutSphere::CutSphere(int x0, int y0, int z0, int raio){
    this->x0 = x0; this->y0 = y0; this->z0 = z0;
    this->raio = raio;
}

void CutSphere::draw(Sculptor &s){
    s.cutSphere(x0, y0, z0, raio);
}
