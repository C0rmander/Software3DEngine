#ifndef MTL_H
#define MTL_H
#include <string>
#include "SDL.h"
#include "Vector3D.h"
struct MTL
{
Vector3D Ka,Kd,Ks;
std::string newMTL;
SDL_Surface* map_Kd = nullptr;
MTL()
{

}
MTL(std::string newmtl, Vector3D ka, Vector3D kd, Vector3D ks, SDL_Surface* map_kd)
{
    newMTL = newmtl;
    Ka = ka;
    Kd = kd;
    Ks = ks;
    map_Kd = map_kd;
}
};

#endif // MTL_H
