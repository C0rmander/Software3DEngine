#include "FragmentShader.h"
#include <vector>
#include "MathsFunc.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Vector3D.h"
#include "Texture2D.h"
#include "Tex_Loader.h"
#include "MTL_Loader.h"
#include <time.h>
#include "VertexShader.h"
#include "Obj_Loader.h"
#include <array>
#include <map>
#include "Pixel.h"
using namespace std;
extern SDL_Renderer* mRenderer;
SDL_Surface* Texture;
FragmentShader::FragmentShader(SDL_Renderer* render)
{
    mRenderer = render;
}
//Vector3D get_Z_value(float V, float W, float U, Vector3D vec1, Vector3D vec2, Vector3D vec3)
//{
//    return Vector3D (U * vec1.x + W * vec2.x + V * vec3.x,U * vec1.y + W * vec2.y + V * vec3.y, U* vec1.z+ W* vec2.z+ V* vec3.z);
//}

Vector3D get_Z_value(float V, float W, float U, Vector3D vec1, Vector3D vec2, Vector3D vec3)
{
    return Vector3D ((vec1 * U) + (vec2 * W) + (vec3 * V));
}

Vector3D get_light_vector(float V, float W, float U, Vector3D vec1, Vector3D vec2, Vector3D vec3, Vector3D light)
{
    return light - Vector3D(U * vec1.x + W * vec2.x + V * vec3.x,U * vec1.y + W * vec2.y + V * vec3.y, U* vec1.z+ W* vec2.z+ V* vec3.z);
}

Texture2D get_UVCoordinates(float V, float W, float U, Texture2D tex1, Texture2D tex2, Texture2D tex3)
{
   // cout<<"getting uv coordinates"<<endl;

    return Texture2D (U * tex1.Tx + W * tex2.Tx + V * tex3.Tx,U * tex1.Ty + W * tex2.Ty + V * tex3.Ty);
}

//Uint32 get_pixel32(SDL_Surface* surface, Texture2D pixTex)
//{
//Uint32 *pixels = (Uint32 *)surface->pixels;
//int x = pixTex.Tx *surface->w;
//int y = pixTex.Ty *surface->h;
//return pixels[ ( y*surface->w ) + x];
//}
Uint8 getR(Uint32 c) {
    return (c >> 16);
}

Uint8 getG(Uint32 c) {
    return (c >> 8);
}

Uint8 getB(Uint32 c) {
    return c;
}
//SDL_Color get_pixel32( SDL_Surface *surface, Texture2D pixTex )
//{
//    Uint32 *pixels = (Uint32 *)surface->pixels;
//    int x = pixTex.Ty *surface->w, y = pixTex.Tx *surface->h;
//    Uint32 pix = pixels[ abs(( x * surface->w ) + y) ];
//    SDL_Color Color = {getR(pix),getG(pix), getB(pix), SDL_ALPHA_OPAQUE};
//    return Color;
//
//}
SDL_Color get_pixel32(SDL_Surface* surface, Texture2D pixTex)
{
    SDL_LockSurface(surface);
    const Uint8 Bpp = surface->format->BytesPerPixel;

	/*
	Retrieve the address to a specific pixel
	pSurface->pixels	= an array containing the SDL_Surface' pixels
	pSurface->pitch		= the length of a row of pixels (in bytes)
	X and Y				= the offset on where on the image to retrieve the pixel, (0, 0) is in the upper left corner of the image
	*/

	int x = abs(pixTex.Tx *surface->w);
    int y = abs(pixTex.Ty *surface->h);

	Uint8* pPixel = (Uint8*)surface->pixels + y * surface->pitch + x * Bpp;
   // cout<<x<<","<<y<<endl;
  //  cout<<surface->w<<","<<surface->h<<endl;
	Uint32 PixelData = *(Uint32*)pPixel;
	SDL_Color Color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
    //cout<<Color.r<<","<<Color.g<<","<<Color.b<<endl;
	// Retrieve the RGB values of the specific pixel
	SDL_GetRGB(PixelData, surface->format, &Color.r, &Color.g, &Color.b);
	return Color;
}


bool Barycentric(Vector3D& a, Vector3D& b, Vector3D& c, Vector3D p, float&v, float &w, float &u)
{
    MathsFunc math;
    float area, subArea1, subArea2,subArea3, areaDiv;
    area = math.area(a.x, a.y, b.x, b.y, c.x, c.y);
    areaDiv = 1/area;
    subArea1 = math.area(p.x, p.y, a.x, a.y, b.x, b.y);
    subArea2 = math.area(p.x, p.y, a.x, a.y, c.x, c.y);
    subArea3 = math.area(p.x, p.y, b.x, b.y, c.x, c.y);
    v = subArea1 * areaDiv;
    w = subArea2 * areaDiv;
    u = 1-v-w;
    return (subArea1 + subArea2 + subArea3 == area && v + w <= 1 && v + w >= 0);
}

//bool Barycentric(Vector3D& a, Vector3D& b, Vector3D& c, Vector3D p, float&v, float &w, float &u)
//{
//    MathsFunc math;
//    Vector3D v0 = b - a, v1 = c - a, v2 = p - a;
//    float d00 = math.DotProduct(v0, v0);
//    float d01 = math.DotProduct(v0, v1);
//    float d11 = math.DotProduct(v1, v1);
//    float d20 = math.DotProduct(v2, v0);
//    float d21 = math.DotProduct(v2, v1);
//    float denom = d00 * d11 - d01 * d01;
//    v = (d11 * d20 - d01 * d21) / denom;
//    w = (d00 * d21 - d01 * d20) / denom;
//    u = 1.0f - v - w;
//    return v >= 0.0f && w >= 0.0f && u >= 0.0f && v <= 1.0f && w <= 1.0f && u <= 1.0f && v+w+u <= 1 && v+w+u >= 0;
//}
//bool Barycentric(Vector3D& a, Vector3D& b, Vector3D& c, Vector3D p, float&v, float &w, float &u, Vector3D n)
//{
//    MathsFunc math;
//    n = math.normalise(n);
//    float u1, u2, u3, u4;
//    float v1, v2, v3, v4;
//    if((fabs(n.x) >= fabs(n.y)) && (fabs(n.x) >= fabs(n.z)))
//    {
//        u1 = a.y - c.y;
//        u2 = b.y - c.y;
//        u3 = p.y - a.y;
//        u4 = p.y - c.y;
//
//        v1 = a.z - c.z;
//        v2 = b.z - c.z;
//        v3 = p.z - a.z;
//        v4 = p.z - c.z;
//    }
//    else if((fabs(n.y) >= fabs(n.z)))
//    {
//        u1 = a.z - c.z;
//        u2 = b.z - c.z;
//        u3 = p.z - a.z;
//        u4 = p.z - c.z;
//
//        v1 = a.x - c.x;
//        v2 = b.x - c.x;
//        v3 = p.x - a.x;
//        v4 = p.x - c.x;
//    }
//    else
//    {
//        u1 = a.x - c.x;
//        u2 = b.x - c.x;
//        u3 = p.x - a.x;
//        u4 = p.x - c.x;
//
//        v1 = a.y - c.y;
//        v2 = b.y - c.y;
//        v3 = p.y - a.y;
//        v4 = p.y - c.y;
//
//    }
//    float denom = v1 * u2 - v2*u1;
//    if (denom == 0.0f)
//    {
//        return false;
//    }
//    else
//    {
//        float oneOverDenom = 1.0f/ denom;
//        v = (v4*u2 - v2*u4) * oneOverDenom;
//        w = (v1*u3 - v3*u1) * oneOverDenom;
//        u = 1.0f - v - w;
//        return true;
//    }
//
//}

Vector3D get_fragmentNormals(float V, float W, float U, Face3D const &face)
{
    MathsFunc math;
    VertexShader vertexShader;
    Vector3D vec1 = math.VecAverage(vertexShader.getNormalsAtPoint(max(face.f1-1,0)));
    Vector3D vec2 = math.VecAverage(vertexShader.getNormalsAtPoint(max(face.f2-1,0)));
    Vector3D vec3 = math.VecAverage(vertexShader.getNormalsAtPoint(max(face.f3-1,0)));
    return Vector3D (U * vec1.x + W * vec2.x + V * vec3.x, U * vec1.y + W * vec2.y + V * vec3.y, U * vec1.z + W * vec2.z + V * vec3.z);
}


Vector3D get_Specular(Vector3D light_vec, Vector3D normal, Vector3D h, float alpha, Vector3D light_colour, Vector3D spec_colour)
{
    MathsFunc math;
    float highlight = pow(max(h.Dot(math.normalise(normal),math.normalise(h)),0.0f),alpha);// * float(nl > 0.0);
    return (math.rgb_multiply(light_colour , spec_colour)*255) * highlight;

}

Vector3D get_Diffuse(Vector3D light_vec, Vector3D normal,Vector3D light_colour, Vector3D mat_colour)
{
    MathsFunc math;
    float direct_light = max(math.DotProduct(light_vec,math.normalise(normal)),0.0f);
    return (math.rgb_multiply(light_colour, mat_colour)*(direct_light))*255;

}

Vector3D get_Ambient(Vector3D light_colour, Vector3D mat_colour)
{
    MathsFunc math;
    return (math.rgb_multiply(mat_colour,light_colour))*255;

}

Vector3D get_Halfway_Vector(Vector3D v, Vector3D l)
{
  return (v+l)*(1/((l.Mag(v+l))));
}

Vector3D get_Reflection_Vector(Vector3D v, Vector3D l)
{
  return ((v-l)*(v.Dot(l,v)))* 2.0;
}

string materialChanged(map<int,string>& mp, int faceNum, string& currMatName)
{
    int num = 0;
    for (auto itr = mp.begin(); itr != mp.end(); ++itr)
    {
        if(faceNum > itr->first)
        {
            num = itr->first;
        }
    }
    if(mp[num] != currMatName)
    {
        return mp[num];
    }
    else
    {
        return "";
    }
}

MTL findMaterialWithName(string& materialName, vector<MTL> const& materials)
{
   for(int i =0; i < materials.size(); i++)
   {
       if(materials[i].newMTL == materialName)
       {
           return materials[i];
       }
   }
   return materials[0];
}

Vector3D getPixelAsVector3D(float V,float W,float U,Texture2D tex1,Texture2D tex2,Texture2D tex3, SDL_Surface* temp, Vector3D& diffuse)
{
    if(temp != nullptr)
    {
    Texture2D tex = get_UVCoordinates(V,W,U, tex1, tex2,tex3);
    SDL_Color Color = get_pixel32(temp,tex);
    return Vector3D(Color.r,Color.g,Color.b);
    }
    else
    {
      return diffuse * 255;
    }
}

int paint_scanline(vector<Pixel> const& pixels, const float Spec)
{
    MathsFunc math;
    for(int i =0; i < pixels.size(); i++)
    {
        if (pixels[i].Coordinates != Vector3D(-1,-1,-1))
        {
            Vector3D xyz = pixels[i].Coordinates;
            Vector3D light_vec = math.normalise(Vector3D(1, 1, -410) - xyz);
            Vector3D Diffuse = get_Diffuse(light_vec,pixels[i].Normal,Vector3D(155,155,155),pixels[i].Colour);
            Vector3D h = get_Halfway_Vector(Vector3D(-40,-200,-200), light_vec);
            Vector3D Specular = get_Specular(light_vec, pixels[i].Normal, h, Spec, Vector3D(155,155,155),Vector3D(230, 220, 220));
            Vector3D Ambient = get_Ambient(Vector3D(155,155,155), pixels[i].Colour);
            if(Specular != Vector3D(0,0,0))
            {
                Specular = Vector3D(255,255,255);
            }
            Vector3D blinn_phong = Specular;
            SDL_SetRenderDrawColor(mRenderer, min(blinn_phong.x,(float)255), min(blinn_phong.y,(float)255), min(blinn_phong.z,(float)255), 255);
            SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
            SDL_RenderDrawPoint(mRenderer, pixels[i].Coordinates.x,pixels[i].Coordinates.y);
        }
    }
    return 0;
}

void FragmentShader::get_scanline(const vector<MTL>& materials,int Width, int Height, vector<Face3D> const& face, vector<Vector3D> const& vec3d, const float& Spec)
{
    MathsFunc math;
    Obj_Loader objloader;
    Tex_Loader texture;
    map<int,string> matNames = objloader.getMaterialNames();
    MTL material;
    material.Kd = Vector3D(0,255,90);
    float V, U, W;
    SDL_Surface* temp;
    vector<Texture2D> texCoords = texture.getTexCoords();
    vector<Face3D> texFaces = texture.getTexFaces();
    for (int j = 0; j < Height; ++j)
    {
        vector<Pixel> pixels (Width,Pixel(Vector3D(-1,-1,-1), Vector3D(-1,-1,-1), Vector3D(-1,-1,-1)));
        bool paintScanline = false;
        for (int f=0; f<face.size(); ++f)
        {
            Vector3D v1 = math.ScalePos(vec3d[(max(face[f].f1-1,0))],600,200,400);
            Vector3D v2 = math.ScalePos(vec3d[(max(face[f].f2-1,0))],600,200,400);
            Vector3D v3 = math.ScalePos(vec3d[(max(face[f].f3-1,0))],600,200,400);
            float maxY = max(v1.y,max(v2.y, v3.y));
            float maxX = max(v1.x,max(v2.x, v3.x));
            float minY = min(v1.y,min(v2.y, v3.y));
            float minX = min(v1.x,min(v2.x, v3.x));
            Texture2D tex1 = texCoords[max(texFaces[f].f1-1,0)];
            Texture2D tex2 = texCoords[max(texFaces[f].f2-1,0)];
            Texture2D tex3 = texCoords[max(texFaces[f].f3-1,0)];
            if(j > minY && j < maxY)
            {
                for (int i = minX; i < maxX; ++i)
                {
                    if(Barycentric(v1, v2, v3, Vector3D(i,j,v1.z), V, W, U) == true)
                    {

                        if(materials.size() > 0)
                        {
                        string newMaterial = materialChanged(matNames, f, material.newMTL);
                        if(newMaterial != "")
                        {
                            material = findMaterialWithName(newMaterial, materials);
                            temp = material.map_Kd;
                        }
                        }
                        Vector3D z_val = get_Z_value(V,W,U,v1,v2,v3);
                        if(pixels[i].Coordinates == Vector3D(-1,-1,-1) || pixels[i].Coordinates.z > z_val.z)
                        {
                            Vector3D fragn = get_fragmentNormals(V,W,U, face[f]);
                            paintScanline = true;
                            Vector3D pix = getPixelAsVector3D(V, W, U, tex1, tex2, tex3, temp, material.Kd);
                            pixels[i] = Pixel(z_val, pix, fragn);
                        }
                    }
                }
            }
        }

        if(paintScanline == true)
        {
          paint_scanline(pixels,Spec);
        }

     }

}




