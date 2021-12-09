#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include <vector>
#include "Face3D.h"
#include "Matrix3D.h"
#include <SDL.h>
#include <string>
#include "MTL.h"
using namespace std;
class FragmentShader
{
    public:
        FragmentShader(SDL_Renderer* render);
        void get_scanline(const vector<MTL>& materials, int Width, int Height, const vector<Face3D>& face, const vector<Vector3D> &vec3d, const float& Spec = 5);
};

#endif // FRAGMENTSHADER_H
