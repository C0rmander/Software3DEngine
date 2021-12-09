#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include <vector>
#include <SDL.h>
#include <string>
#include <unordered_map>
#include "Vector3D.h"
#include "Face3D.h"
using namespace std;
class VertexShader
{
    public:
        VertexShader();
        VertexShader(unordered_map<int, vector<Vector3D> > Normals);

    vector<Vector3D> rotateMesh(vector<Vector3D>& vec3d, struct Matrix3D& mat);

    //Vector3D* getNormals(vector<Vector3D>& vec3d, vector<Face3D>& face);
    Vector3D* updateNormals(Vector3D*& normals, Matrix3D& Mat, size_t  normalsSize);
    void addNormalsToMap(const int facePoint, Vector3D& normal);
    unordered_map<int, vector<Vector3D>> getNormals();
    vector<Vector3D> getNormalsAtPoint(int point);
    void ClearMap();
};

#endif // VERTEXSHADER_H
