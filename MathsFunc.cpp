#include "MathsFunc.h"
#include "Vector3D.h"
#include <cmath>
#include <stdlib.h>
#include "Matrix3D.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;


MathsFunc::MathsFunc()
{
}
    Vector3D MathsFunc::minXY(struct Vector3D vec1, struct Vector3D vec2, struct Vector3D vec3, int xTransform, int yTransform, int scaleX)
{
    Vector3D vect;
    if (vec1.getX()*scaleX+xTransform < vec2.getX()*scaleX+xTransform)
                    {
                        if(vec1.getX()*scaleX+xTransform < vec3.getX()*scaleX+xTransform)
                        {
                            vect.setX(vec1.getX()*scaleX+xTransform);
                        }
                        else
                            {
                            vect.setX(vec3.getX()*scaleX+xTransform);
                            }
                    }
                    else
                    {
                        if (vec2.getX()*scaleX+xTransform < vec3.getX()*scaleX+xTransform)
                        {
                            vect.setX(vec2.getX()*scaleX+xTransform);
                        }
                        else
                        {
                            vect.setX(vec3.getX()*scaleX+xTransform);
                        }
                    }



                    if (vec1.getY()*scaleX+yTransform < vec2.getY()*scaleX+yTransform)
                    {
                        if(vec1.getY()*scaleX+yTransform < vec3.getY()*scaleX+yTransform)
                        {
                            vect.setY(vec1.getY()*scaleX+yTransform);
                        }
                        else
                            {
                            vect.setY(vec3.getY()*scaleX+yTransform);
                            }
                    }
                    else
                    {
                        if (vec2.getY()*scaleX+yTransform < vec3.getY()*scaleX+yTransform)
                        {
                            vect.setY(vec2.getY()*scaleX+yTransform);
                        }
                        else
                        {
                            vect.setY(vec3.getY()*scaleX+yTransform);
                        }
                    }
                    vect.setZ(0.0);
        return vect;
}

struct Vector3D MathsFunc::maxXY(struct Vector3D vec1, struct Vector3D vec2, struct Vector3D vec3, int xTransform, int yTransform, int scaleX)
{

    Vector3D vect;
    if (vec1.getX() > vec2.getX())
                    {
                        if(vec1.getX()*scaleX+xTransform > vec3.getX()*scaleX+xTransform)
                        {
                            vect.setX(vec1.getX()*scaleX+xTransform);
                        }
                        else
                            {
                            vect.setX(vec3.getX()*scaleX+xTransform);
                            }
                    }
                    else
                    {
                        if (vec2.getX()*scaleX+xTransform > vec3.getX()*scaleX+xTransform)
                        {
                            vect.setX(vec2.getX()*scaleX+xTransform);
                        }
                        else
                        {
                            vect.setX(vec3.getX()*scaleX+xTransform);
                        }
                    }



                    if (vec1.getY()*scaleX+yTransform > vec2.getY()*scaleX+yTransform)
                    {
                        if(vec1.getY()*scaleX+yTransform > vec3.getY()*scaleX+yTransform)
                        {
                            vect.setY(vec1.getY()*scaleX+yTransform);
                        }
                        else
                            {
                            vect.setY(vec3.getY()*scaleX+yTransform);
                            }
                    }
                    else
                    {
                        if (vec2.getY()*scaleX+yTransform > vec3.getY()*scaleX+yTransform)
                        {
                            vect.setY(vec2.getY()*scaleX+yTransform);
                        }
                        else
                        {
                            vect.setY(vec3.getY()*scaleX+yTransform);
                        }
                    }
        return vect;
}

struct Vector3D MathsFunc::normalise(struct Vector3D vec1)
{
        float mag = sqrt(pow(vec1.getX(),2)+pow(vec1.getY(),2)+pow(vec1.getZ(),2));
        Vector3D normal;
        normal.setX(vec1.x/mag);
        normal.setY(vec1.y/mag);
        normal.setZ(vec1.z/mag);
        return normal;
}

struct Vector3D MathsFunc::rgb_multiply(struct Vector3D vec1, struct Vector3D vec2)
{
        //float rgb_div = 1/255;
        vec1 = (vec1 * 0.00392156862f);
        vec2 = (vec2 * 0.00392156862f);
        return Vector3D(vec1.x*vec2.x,vec1.y*vec2.y,vec1.z*vec2.z);
}
struct vector<vector<Vector3D>> MathsFunc::ReJigVecNorms(struct Vector3D vec1,struct Vector3D vec2,struct Vector3D vec3,struct Vector3D norm1, struct Vector3D norm2, struct Vector3D norm3)
{
        vector<Vector3D> vectors;
        vector<Vector3D> normals;
        vector<vector<Vector3D>> vecnorms;
        vectors.push_back(vec1);
        vectors.push_back(vec2);
        vectors.push_back(vec3);
        normals.push_back(norm1);
        normals.push_back(norm2);
        normals.push_back(norm3);
        for(int i = 0; i<vectors.size(); ++i)
        {
            for(int j = 0; j<vectors.size(); ++j)
            {
                if(vectors[i].y > vectors[j].y)
                {
                    swap(vectors[i], vectors[j]);
                    swap(normals[i], normals[j]);
                }

            }
        }
        if(vectors[2].x < vectors[1].x)
        {
            swap(vectors[2], vectors[1]);
            swap(normals[2], normals[1]);
        }
        vecnorms.push_back(vectors);
        vecnorms.push_back(normals);
       // cout<<vectors[0].y<<","<<vectors[1].y<<","<<vectors[2].y<<endl;
        return vecnorms;
}

struct Vector3D MathsFunc::Substract(struct Vector3D C, struct Vector3D A)
{
    //deducts vector A from vector C;

    Vector3D vect;
    vect.setX(C.getX()-A.getX());
    vect.setY(C.getY()-A.getY());
    vect.setZ(C.getZ()-A.getZ());
    return vect;
}

struct Vector3D MathsFunc::Add(struct Vector3D C, struct Vector3D A)
{
    //deducts vector A from vector C;

    Vector3D vect;
    vect.setX(C.getX()+A.getX());
    vect.setY(C.getY()+A.getY());
    vect.setZ(C.getZ()+A.getZ());
    return vect;
}


float MathsFunc::DotProduct(struct Vector3D vec1, struct Vector3D vec2)
{
    //a · b = ax × bx + ay × by
    return vec1.x*vec2.x+vec1.y*vec2.y+vec1.z*vec2.z;
}
float MathsFunc::Dot2D(struct Vector3D vec1, struct Vector3D vec2)
{
    //a · b = ax × bx + ay × by
    return vec1.x*vec2.x+vec1.y*vec2.y;
}

float MathsFunc::area(int x1, int y1, int x2, int y2, int x3, int y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))*0.5f);
}

float MathsFunc::TriArea(Vector3D& vec1, Vector3D& vec2)
{
    return vec1.Mag(vec1 * vec2) * 0.5;
}

double MathsFunc::doublearea(double x1, double y1, double x2, double y2, double x3, double y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))*0.5);
}

bool MathsFunc::cullingArea(int x1, int y1, int x2, int y2, int x3, int y3)
{
   if (((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0)<0)
   {
       return true;
   }
   else
    {
        return false;
    }

}
struct Vector3D MathsFunc::ScalePos(struct Vector3D vec, int xTransform, int scaleX, int yTransform)
{
    vec.x = vec.x * scaleX+xTransform;
    vec.y = vec.y*scaleX+yTransform;
    return vec;
}

struct Vector3D MathsFunc::matrixMultiply(struct Matrix3D M, struct Vector3D v)
        {
        Vector3D vec((M(0,0) * v.x) + (M(0,1) * v.y) + (M(0,2)* v.z),
                    (M(1,0) * v.x) + (M(1,1) * v.y) + (M(1,2)* v.z),
                     (M(2,0) * v.x)+(M(2,1) * v.y)+(M(2,2) * v.z));
        return vec;
        }


struct Vector3D MathsFunc::VecDoubleMultiply(struct Vector3D vec1, double doub)
        {
        return Vector3D(vec1.x*doub, vec1.y*doub, vec1.z*doub);
        }



Vector3D MathsFunc::VecAverage(const vector<Vector3D>& avg_normals)
{
    double Nx = 0.0;
    double Ny = 0.0;
    double Nz = 0.0;

    for(int i = 0; i<avg_normals.size();++i)
    {

        Nx += avg_normals.at(i).x;
        Ny += avg_normals.at(i).y;
        Nz += avg_normals.at(i).z;
     //   cout<<"x = "<<Nx<<" y = "<<Ny<<" z= "<<Nz<<endl;
    }
   // cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   return Vector3D(Nx/avg_normals.size(),Ny/avg_normals.size(),Nz/avg_normals.size());

}

vector<float> MathsFunc::splitf(string str,char delim)
{
    vector<float> split_data;
    stringstream vertStream(str);
    string point_str;
    while(getline(vertStream, point_str, delim)){split_data.push_back(strtof(point_str.c_str(), NULL));}
    return split_data;
}
//struct Vector3D MathsFunc::matrixMultiply(struct Matrix3D M, struct Vector3D v)
//        {
//        Vector3D vec((M(0,0) * v.getX()) + (M(0,1) * v.getY())+ ((M(0,2) * v.getZ())),
//                    (M(1,0) * v.getX()) + (M(1,1) * v.getY())+ ((M(1,2) * v.getZ())),0);
//        return vec;
//        }

