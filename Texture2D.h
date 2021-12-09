#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include <vector>

struct Texture2D
{

double Tx,Ty;

Texture2D()
{
}

Texture2D(double a, double b)
{
    Tx=a;
    Ty=b;
}

Texture2D(const std::vector <float> &tex)
{
   // if(tex.size() == 2)
   // {
      Tx = tex[0];
      Ty = tex[1];
  //  }

};

double getTx()
{
    return Tx;
}

double getTy()
{
    return Ty;
}
void setTx(double a)
{
    Tx=a;
}
void setTy(double b)
{
    Ty=b;
}
};

#endif // FACE3D_H
