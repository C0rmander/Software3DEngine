#ifndef PIXEL_H
#define PIXEL_H
#include "Vector3D.h"
#include "SDL.h"
struct Pixel
{
Vector3D Coordinates, Colour, Normal;
Pixel();
Pixel(Vector3D coordinates, Vector3D colour, Vector3D normal)
{
    Coordinates = coordinates;
    Colour = colour;
    Normal = normal;
}
};

#endif // PIXEL_H
