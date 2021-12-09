#include "VertexShader.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include<windows.h>
#include <sstream>
#include <string>
#include <vector>
#include "Vector3D.h"
#include <math.h>
#include "Face3D.h"
#include "Matrix3D.h"
#include "MathsFunc.h"
#include <SDL.h>
#include "Texture2D.h"
unordered_map<int, vector<Vector3D>> normals;
using namespace std;
VertexShader::VertexShader(unordered_map<int, vector<Vector3D>> Normals)
{
    normals = Normals;
}
VertexShader::VertexShader()
{
    //ctor
}
vector<Vector3D> VertexShader::rotateMesh(vector<Vector3D>& vec3d, struct Matrix3D& mat)
{
    MathsFunc math;
    for (int i=0; i<vec3d.size(); ++i){vec3d[i] = math.matrixMultiply(mat,vec3d[i]);}
    return vec3d;
}

void VertexShader::addNormalsToMap(const int facePoint, Vector3D& normal)
{
 if(normals.find(facePoint) != normals.end()){normals.emplace(facePoint, vector<Vector3D>{normal});}
 else{normals[facePoint].push_back(normal);}
}
void VertexShader::ClearMap(){normals.clear();}
unordered_map<int, vector<Vector3D>> VertexShader::getNormals(){return normals;}
vector<Vector3D> VertexShader::getNormalsAtPoint(int point){return normals[point];}

//Vector3D* VertexShader::getNormals(vector<Vector3D>& vec3d, vector<Face3D>& face)
//{
//
//   int i = 0;
//   int j = 0;
//   int k = 0;
//   int vertex1;
//   int vertex2;
//   int vertex3;
//   MathsFunc math;
//
//   //vector<Vector3D> vertex_normals;
//   //vector<vector<Vector3D>> normals;
//   Vector3D* normals = new Vector3D [vec3d.size()+1];
//   vector<Face3D> A;
//   vector<Face3D> B;
//   vector<Face3D> C;
//   for (i=0; i<face.size(); ++i)
//   {
//       // the A vector will have only vertex1 data
//       // the B vector will have only vertex2 data
//       // the C vector will have only vertex3 data
//       vertex1= face.at(i).f1-1;
//       vertex2= face.at(i).f2-1;
//       vertex3= face.at(i).f3-1;
//       for (j=0; j<face.size(); ++j)
//        {
//
//
//           if (vertex1 == face[j].f1-1)
//           {
//            A.push_back(face[j]);
//           }
//           if (vertex1 == face[j].f2-1)
//           {
//            A.push_back(face[j]);
//           }
//           if (vertex1 == face[j].f3-1)
//           {
//            A.push_back(face[j]);
//           }
//           if (vertex2 == face[j].f1-1)
//           {
//            B.push_back(face[j]);
//           }
//           if (vertex2 == face[j].f2-1)
//           {
//            B.push_back(face[j]);
//           }
//           if (vertex2 == face[j].f3-1)
//           {
//            B.push_back(face[j]);
//           }
//           if (vertex3 == face[j].f1-1)
//           {
//            C.push_back(face[j]);
//           }
//           if (vertex3 == face[j].f2-1)
//           {
//            C.push_back(face[j]);
//           }
//           if (vertex3 == face[j].f3-1)
//           {
//            C.push_back(face[j]);
//           }
//
//        }
//   if (A.size() > 0)
//   {
//       vector<Vector3D> face_normals;
//       Vector3D n,vec1,vec2,vec3;
//      for (k=0; k<A.size(); ++k)
//    {
//     vec1 =vec3d[A[k].f1-1];
//     vec2 =vec3d[A[k].f2-1];
//     vec3 =vec3d[A[k].f3-1];
//     n = n.Cross(vec2 - vec1,vec3 - vec1);
//
//   //  cout<<"n.z = "<<vec1.z<<endl;
//  // normals.push_back(n);
//   face_normals.push_back(n);
//   }
//    A.clear();
//    normals[vertex1] =  math.VecAverage(face_normals);
//    //vertex_normals.push_back(math.VecAverage(face_normals));
//   }
//   if (B.size() > 0)
//   {
//    vector<Vector3D> face_normals;
//    Vector3D n,vec1,vec2,vec3;
//   for (k=0; k<B.size(); ++k)
//   {
//    vec1 =vec3d[B[k].f1-1];
//    vec2 =vec3d[B[k].f2-1];
//    vec3 =vec3d[B[k].f3-1];
//    n = n.Cross(vec2 - vec1,vec3 - vec1);
//    //normals.push_back(n);
//    face_normals.push_back(n);
//   }
//   B.clear();
//    normals[vertex2] = math.VecAverage(face_normals);
//   //vertex_normals.push_back(math.VecAverage(face_normals));
//   }
//   if (C.size() > 0)
//   {
//    vector<Vector3D> face_normals;
//    Vector3D n,vec1,vec2,vec3;
//   for (k=0; k<C.size(); ++k)
//   {
//    vec1 =vec3d[C[k].f1-1];
//    vec2 =vec3d[C[k].f2-1];
//    vec3 =vec3d[C[k].f3-1];
//    n = n.Cross(vec2 - vec1,vec3 - vec1);
//   // normals.push_back(n);
//    face_normals.push_back(n);
//   }
//   C.clear();
//    normals[vertex3] = math.VecAverage(face_normals);
//   //vertex_normals.push_back(math.VecAverage(face_normals));
//   }
//   //normals.push_back(vertex_normals);
//   //vertex_normals.clear();
//   }
//   //Vector3D normal(0,0,0);
//   //vertex_normals.resize(vertex_normals.size());
//
////   for (int x = 0; x<vertex_normals.size()-1; x++)
////   {
////       if (x!= 0 && (x+1)%3 == 0)
////       {
////        normal = normal.Cross(math.Substract(vertex_normals.at(x-1), vertex_normals.at(x)),math.Substract (vertex_normals.at(x-2), vertex_normals.at(x)));
////        normals.push_back(normal);
////       }
////   }
//
//   //cout<<"normals size is: "<<normals.size()<<endl;
//   return normals;
//
//
//}

Vector3D* VertexShader::updateNormals(Vector3D*& normals, Matrix3D& Mat, size_t  normalsSize)
{
    MathsFunc math;
    for(int i = 0; i< normalsSize; ++i)
    {
       normals[i] = math.matrixMultiply(Mat.Inverse(Mat),normals[i]);
    }
    return normals;
}
