#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include<windows.h>
#include <sstream>
#include <string>
#include "Draw.h"
using namespace std;

//Screen dimension constants



int main( int argc, char* args[] )
{
cout<<"starting engine"<<endl;
try{
    Draw engine;
    engine.startEngine();
    //engine.line(12.45,16.52,17.32,18.92);

} catch (const std::exception& ex) {
    cout<<"exception!"<<endl;
    cout<<ex.what()<<endl;
    cin.get();
}
cin.get();
    return 0;
}


