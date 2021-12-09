#ifndef DRAW_H
#define DRAW_H
#include "Draw.h"
#include "Vector3D.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include<windows.h>
#include <sstream>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;




class Draw
{
    public:
        Draw();
        int startEngine();
        void Triangle(struct Vector3D vec1,struct Vector3D vec2, struct Vector3D vec3);
        void Pixel(struct Vector3D vec1);
        void line(double x1, double y1, double x2, double y2);
        //float area(int x1, int y1, int x2, int y2, int x3, int y3);
       // bool cullingArea(int x1, int y1, int x2, int y2, int x3, int y3);
       Vector3D normalise(struct Vector3D vec1);
        Vector3D ScalePos(struct Vector3D vec);
        struct Matrix3D RotateRight(float timeStep);
        struct Matrix3D RotateLeft(float timeStep);
        struct Matrix3D RotateUp(float timeStep);
        struct Matrix3D RotateDown(float timeStep);

};
#endif // DRAW_H

