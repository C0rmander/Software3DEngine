#ifndef MATHSFUNC_H
#define MATHSFUNC_H
#include <vector>
#include "Vector3D.h"
#include "Face3D.h"
#include <string>
using namespace std;
class MathsFunc
{
    public:
        MathsFunc();

    struct Vector3D minXY(struct Vector3D vec1,struct Vector3D vec2,struct Vector3D vec3, int xTransform, int yTransform, int scaleX);
    struct Vector3D maxXY(struct Vector3D vec1,struct Vector3D vec2,struct Vector3D vec3, int xTransform, int yTransform, int scaleX);
    struct Vector3D normalise(struct Vector3D vec1);
    struct Vector3D Substract(struct Vector3D C, struct Vector3D A);
    struct Vector3D Add(struct Vector3D C, struct Vector3D A);
    float DotProduct(struct Vector3D vec1, struct Vector3D vec2);
    float Dot2D(struct Vector3D vec1, struct Vector3D vec2);
    float area(int x1, int y1, int x2, int y2, int x3, int y3);
    bool cullingArea(int x1, int y1, int x2, int y2, int x3, int y3);
    struct Vector3D ScalePos(struct Vector3D vec, int xTransform, int scaleX, int yTransform);
    struct Vector3D matrixMultiply(const struct Matrix3D mat, struct Vector3D vec);
    double doublearea(double x1, double y1, double x2, double y2, double x3, double y3);
    struct Vector3D VecDoubleMultiply(struct Vector3D vec1, double doub);
    struct vector<vector<Vector3D>> ReJigVecNorms(struct Vector3D vec1,struct Vector3D vec2,struct Vector3D vec3,struct Vector3D norm1, struct Vector3D norm2, struct Vector3D norm3);
    struct Vector3D VecAverage(const vector<Vector3D>& avg_normals);
    struct Vector3D rgb_multiply(struct Vector3D vec1, struct Vector3D vec2);
    float TriArea(Vector3D& vec1,Vector3D& vec2);
    vector<float> splitf(string str,char delim);
};

#endif // MATHSFUNC_H
