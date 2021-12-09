#include "Obj_Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Texture2D.h"
#include "MathsFunc.h"
using namespace std;
vector <Face3D> face3d;
vector <Vector3D> norm3d;
map <int, string> materialNames;
Obj_Loader::Obj_Loader()
{
}

vector<string> split(string str,char delim)
{
    vector<string> split_data;
    stringstream vertStream(str);
    string point_str;
    while(getline(vertStream, point_str, delim)){split_data.push_back(point_str);}
    return split_data;
}
Face3D getFace(string faces, int pos)
{
MathsFunc math;
vector<float> facelist;
vector<string> split_data = split(faces,' ');
for (int i = 0; i< split_data.size(); i++){facelist.push_back(math.splitf(split_data[i],'/')[pos]);}
return Face3D(facelist);
}
vector<Vector3D> Obj_Loader::verts(string OBJfile)
{
    MathsFunc math;
    string data;
    Tex_Loader texloader;
    vector<Face3D> texFaces;
    vector <Vector3D> vec3d;
    vector<Texture2D> tex2d;
    ifstream infile;
    int f = 0;
    infile.open(OBJfile.c_str());
    while(getline(infile, data))
    {
        if(data.substr(0,2) == "v "){vec3d.push_back(Vector3D(math.splitf(data.erase(0,2),' ')));continue;}
        if(data.substr(0,2) == "vt"){tex2d.push_back(math.splitf(data.erase(0,3),' '));continue;}
        if(data.substr(0,2) == "vn"){norm3d.push_back(math.splitf(data.erase(0,3),' '));continue;}
        if(data.substr(0,7) == "usemtl ")
        {
                materialNames.insert({f,data.erase(0,7)});
                continue;
        }
        if(data.substr(0,2) == "f ")
        {
            f+=1;
            face3d.push_back(getFace(data.erase(0,2),0));
            texFaces.push_back(getFace(data.erase(0,2),1));
            continue;
        }
    }
    texloader.setTexCoords(tex2d);
    texloader.setTexFaces(texFaces);
    return vec3d;
}
vector<Vector3D> Obj_Loader::normals(){return norm3d;}
vector<Face3D> Obj_Loader::faces(){return face3d;}
map<int,string> Obj_Loader::getMaterialNames(){return materialNames;}
