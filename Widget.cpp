#include "Widget.h"
#include "Vector3D.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
Widget::Widget()
{
    //ctor
}

void DrawArrow(float x, float y, Uint32 colour)
{
 cout<<"the arrows position is: "<<x<<","<<y<<endl;
 cout<<"the RGB colour is: "<< (int)(colour >> 8) << (int) (colour >> 16) << (int) (colour >> 32)<<endl;
}
