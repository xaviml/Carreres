#include "roda.h"

Roda::Roda(vector<point4> vertexs, vector<Cara*> cares) : Objecte(vertexs, cares) {
    m = new Material();

    m->ka = vec3(0.05f);
    m->ks = vec3(0.5f);
    m->kd = vec3(0.05f);

    m->shineness = 0.25f*64;

}
