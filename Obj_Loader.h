#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "Vector3D.h"
#include "Face3D.h"
#include <vector>
#include "Tex_Loader.h"
#include <map>
using namespace std;
class Obj_Loader
{
    public:
        Obj_Loader();
        vector<struct Vector3D> verts(string OBJfile);
        vector<struct Face3D> faces();
        vector<struct Vector3D> normals();
        map<int,string> getMaterialNames();
};

#endif // OBJ_LOADER_H
