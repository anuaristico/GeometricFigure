#include "putSphere.h"

PutSphere::PutSphere(int x0, int y0, int z0, int raio, int r, int g, int b, int a){
    this->x0 = x0; this->y0 = y0; this->z0 = z0;
    this->raio = raio; this->r = r; this->g = g; this->b = b; this->a = a;
}

void PutSphere::draw(Sculptor &s){
    s.setColor(r, g, b, a);
    s.putSphere(x0, y0, z0, raio);
}
