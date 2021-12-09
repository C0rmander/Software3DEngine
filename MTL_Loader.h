#ifndef MTL_LOADER_H
#define MTL_LOADER_H
#include <vector>
#include "Vector3D.h"
#include "SDL.h"
#include <string>
#include <unordered_map>
#include "MTL.h"
class MTL_Loader
{
    public:
        MTL_Loader();
        std::vector<MTL> getMaterials();
        std::vector<Vector3D> getAmbientColour();
        std::vector<Vector3D> getDiffuseColour();
        std::vector<Vector3D> getSpecularColour();
        std::vector<SDL_Surface*> getSurfaces();
        std::vector<std::string> getUrls();
        std::vector<std::string> getMatNames();
        std::vector <MTL> readFile(std::string MTLfile);
};

#endif // MTL_LOADER_H
