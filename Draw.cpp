#include "Draw.h"
#include "MathsFunc.h"
#include "Vector3D.h"
#include "Face3D.h"
#include <vector>
#include <cmath>
#include "Obj_Loader.h"
#include "Matrix3D.h"
#include <SDL_image.h>
#include "kiss_sdl.h"
#include "kiss_events_system.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Tex_Loader.h"
#include "MTL_Loader.h"
#include<time.h>
#include <thread>
#define TICKS_FOR_NEXT_FRAME (1000 / 60)
using namespace std;
SDL_Window* mWindow;
SDL_Renderer* mRenderer;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screenSurface;
string OBJfile;
int xTransform = 600;
int yTransform = 400;
int scaleX = 300;
int scaleY = 300;

Draw::Draw()
{
    //ctor
}




void Draw::line(double x1, double y1, double x2, double y2)
{
    //cout<<"running!"<<endl;
    SDL_RenderDrawLine(mRenderer, x1, y1, x2, y2);
    if (mRenderer) {
    SDL_RenderPresent( mRenderer );
    }
}


void Draw::Triangle(struct Vector3D vec1, struct Vector3D vec2, struct Vector3D vec3)
{
    //cout<<"running!"<<endl;
    SDL_RenderDrawLine(mRenderer, vec1.getX()*scaleX+xTransform, vec1.getY()*scaleX+yTransform, vec2.getX()*scaleX+xTransform, vec2.getY()*scaleX+yTransform);
    SDL_RenderDrawLine(mRenderer, vec2.getX()*scaleX+xTransform, vec2.getY()*scaleX+yTransform, vec3.getX()*scaleX+xTransform, vec3.getY()*scaleX+yTransform);
    SDL_RenderDrawLine(mRenderer, vec3.getX()*scaleX+xTransform, vec3.getY()*scaleX+yTransform, vec1.getX()*scaleX+xTransform, vec1.getY()*scaleX+yTransform);
    if (mRenderer) {
    SDL_RenderPresent( mRenderer );
    }
}

void Draw::Pixel(struct Vector3D vec1)
{
    //cout<<"running!"<<endl;
    SDL_RenderDrawPoint(mRenderer, vec1.getX(),vec1.getY());

}

Matrix3D MoveLeft(float timeStep)
{
 return Matrix3D (1,0,-timeStep,
                  0,1,1,
                  0,0,1);
}

Matrix3D MoveRight(float timeStep)
{
     return Matrix3D (1,0,timeStep,
                      0,1,1,
                      0,0,1);
}

Matrix3D MoveUp(float timeStep)
{
  return Matrix3D (1,0,1,
                   0,1,-timeStep,
                   0,0,1);
}

Matrix3D MoveBack(float timeStep)
{
return Matrix3D (1,0,1,
                 0,1,1,
                 0,0,timeStep);
}
Matrix3D MoveForward(float timeStep)
{
return Matrix3D (1,0,1,
                 0,1,1,
                 0,0,-timeStep);
}

Matrix3D MoveToPos(float timeStep, float x, float y)
{
return Matrix3D (1,0,x,
                 0,1,y,
                 0,0,0);
}

Matrix3D Draw::RotateLeft(float timeStep)
{
return Matrix3D (cos(timeStep),-sin(timeStep),0,sin(timeStep),cos(timeStep),0,0,0,1);
}

Matrix3D Draw::RotateRight(float timeStep)
{
    //cout<<"running!"<<endl;

 // Z matrix >   Matrix3D mat(cos(rotation),-sin(rotation),0,sin(rotation),cos(rotation),0,0,0,1);
    return Matrix3D (cos(timeStep),-sin(timeStep),0,sin(timeStep),cos(timeStep),0,0,0,1);


}

Matrix3D Draw::RotateUp(float timeStep)
{
    //cout<<"running!"<<endl;

 // Z matrix >   Matrix3D mat(cos(rotation),-sin(rotation),0,sin(rotation),cos(rotation),0,0,0,1);

    return Matrix3D (1,0,0,0,cos(timeStep),-sin(timeStep),0,sin(timeStep),cos(timeStep));


}

Matrix3D Draw::RotateDown(float timeStep)
{
    //cout<<"running!"<<endl;

 // Z matrix >   Matrix3D mat(cos(rotation),-sin(rotation),0,sin(rotation),cos(rotation),0,0,0,1);

    return Matrix3D (1,0,0,0,cos(timeStep*1.5),-sin(timeStep*1.5),0,sin(timeStep*1.5),cos(timeStep*1.5));


}





int Draw::startEngine()
{
    FragmentShader fragShader(mRenderer);
    Obj_Loader objloader;
    MTL_Loader MTLloader;
    unordered_map<int, vector<Vector3D>> normals;
    VertexShader vertexShader = VertexShader(normals);
    MathsFunc math();
    float ROLL_LEFT = 0;
    float ROLL_RIGHT = 0;
    float PITCH_UP = 0;
    float PITCH_DOWN = 0;
    vector<Vector3D> verts;
    vector<Face3D> face;
    //Vector3D* normals;

    kiss_events_system kiss_events;
    kiss_array objects, a1, a2;
	kiss_window window1, pane1, pane2, pane3, renderPane;

	kiss_label label1 = {0}, label2 = {0}, label3 = {0}, speclabel = {0}, difflabel={0}, amblabel = {0};
	kiss_button button_ok1 = {0}, button_ok2 = {0}, button_cancel = {0};
	kiss_textbox textbox1 = {0}, textbox2 = {0}, diffbox = {0}, specbox = {0};
	kiss_vscrollbar vscrollbar1 = {0}, vscrollbar2 = {0};
	kiss_hscrollbar hscrollbar1 = {0}, diffScrollbar = {0} ,specScrollbar = {0};
	kiss_progressbar progressbar = {0};
	kiss_entry entry = {0};
	int textbox_width, textbox_height, pane1_width, pane1_height, pane2_height, pane2_width, pane3_width, pane3_height, draw, quit;

	quit = 0;
	draw = 1;
	textbox_width = 40;
	textbox_height = 30;
	pane1_width = 400;
	pane1_height = kiss_screen_height;
	pane2_width = 400;
	pane2_height = kiss_screen_height;
	pane3_width = kiss_screen_width - (pane1_width + pane2_width);
	pane3_height = 300;
    renderer = kiss_init("Cpu-Ngine", &objects, 1920, 1030);
	if (!renderer)
    {
        return 1;
    }
	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);
	kiss_array_new(&a2);
	kiss_array_append(&objects, ARRAY_TYPE, &a2);

	/* Arrange the widgets nicely relative to each other */
//    kiss_pane_new(&pane2, NULL, 1, 0, 0, pane2_width, pane2_height);
    kiss_window_new(&window1, NULL, 1, 0, 0, kiss_screen_width,kiss_screen_height);
    //renderPane.wdw =
    kiss_window_new(&pane1, NULL, 1, kiss_screen_width-pane1_width,1, pane1_width, kiss_screen_height);
	kiss_window_new(&pane2, NULL, 1, 1,1, pane2_width, kiss_screen_height);
	kiss_window_new(&pane3, NULL, 1, pane2_width,kiss_screen_height - pane3_height, kiss_screen_width - (pane1_width + pane2_width), pane3_height);


    HWND handle;
    handle=FindWindowA(NULL, "Cpu-Ngine");

	//mWindow = SDL_CreateWindowFrom(handle);
	mWindow = SDL_CreateWindow( "Render", pane1_width, 0, kiss_screen_width - (pane1_width + pane2_width),kiss_screen_height - pane3_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );
	SDL_SetWindowTitle(mWindow, "SDL Window - Set by SDL");
    HWND hwnd;
    hwnd = FindWindowA(NULL, "SDL Window - Set by SDL");
	SetParent(hwnd,handle);
	//SDL_SetWindowSize(mWindow,kiss_screen_width - (pane1_width + pane2_width),kiss_screen_height - pane3_height);
    SDL_Surface* s = SDL_GetWindowSurface(mWindow);
    mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_SOFTWARE);
    //SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    //SDL_FillRect(s, &s->clip_rect, 0xffff00ff);
    //SDL_UpdateWindowSurface(mWindow);
    //kiss_window_new(&renderPane, NULL, 1, pane1_width,1, kiss_screen_width - (pane1_width + pane2_width), kiss_screen_height - pane3_height);
	//SDL_SetWindowModalFor(mWindow, &handle);
//	SDL_SysWMinfo wmInfo;
//    SDL_VERSION(&wmInfo.version);
//    SDL_GetWindowWMInfo(window, &wmInfo);
//    HWND hwnd = wmInfo.info.win.window;;
//	SetParent(handle, hwnd);
    //mWindow = SDL_CreateWindow( "Render", pane1_width, 25, kiss_screen_width - (pane1_width + pane2_width),kiss_screen_height - pane3_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );


	kiss_textbox_new(&textbox1, &pane1, 1, &a1, kiss_screen_width + 10 - pane1.rect.w,
		3 * kiss_normal.h, pane1.rect.w-30, textbox_height);

	kiss_vscrollbar_new(&vscrollbar1, &pane1, textbox1.rect.x +
		textbox1.rect.w, textbox1.rect.y, textbox_height);


    kiss_hscrollbar_new(&hscrollbar1, &pane2,pane1.rect.x+100, pane1.rect.y+(pane1.rect.h/2), pane1.rect.w-100);
    kiss_hscrollbar_new(&diffScrollbar, &pane2,hscrollbar1.leftrect.x, hscrollbar1.leftrect.y+60, pane1.rect.w-100);
    kiss_hscrollbar_new(&specScrollbar, &pane2,diffScrollbar.leftrect.x,diffScrollbar.leftrect.y+60, pane1.rect.w-100);

	kiss_label_new(&amblabel, &pane1, "0", pane1.rect.x+5, hscrollbar1.leftrect.y-5);
    kiss_label_new(&difflabel, &pane1, "0", amblabel.rect.x, amblabel.rect.y + 60);
    kiss_label_new(&speclabel, &pane1, "0",difflabel.rect.x, difflabel.rect.y+60);
    amblabel.textcolor = kiss_white;
    difflabel.textcolor = kiss_white;
    speclabel.textcolor = kiss_white;

	kiss_label_new(&label1, &pane1, "Ambient", speclabel.rect.x +
		kiss_edge, speclabel.rect.y - kiss_textfont.lineheight);

    label1.textcolor = kiss_white;

	kiss_label_new(&label2, &pane1, "Diffuse", difflabel.rect.x +
		kiss_edge, difflabel.rect.y - kiss_textfont.lineheight);

    label2.textcolor = kiss_white;

	kiss_label_new(&label3, &pane1, "Specular", amblabel.rect.x +
		kiss_edge, amblabel.rect.y - kiss_textfont.lineheight);

    label3.textcolor = kiss_white;

	kiss_button_new(&button_cancel, &window1, "Cancel",
		entry.rect.x + entry.rect.w - kiss_edge - kiss_normal.w,
		entry.rect.y + entry.rect.h + kiss_normal.h);

	kiss_button_new(&button_ok1, &window1, "OK", button_cancel.rect.x -
		2 * kiss_normal.w, button_cancel.rect.y);

	kiss_progressbar_new(&progressbar, &pane2, pane2.rect.x +
		kiss_up.w - kiss_edge, pane2.rect.y + pane2.rect.h / 2 -
		kiss_bar.h / 2 - kiss_border,
		pane2.rect.w - 2 * kiss_up.w + 2 * kiss_edge);

	kiss_button_new(&button_ok2, &pane2, "OK", pane2.rect.x +
		pane2.rect.w / 2 - kiss_normal.w / 2,
		progressbar.rect.y + progressbar.rect.h +
		2 * kiss_vslider.h);

    kiss_button_new(&button_ok2, &pane2, "OK", pane2.rect.x +
		pane2.rect.w / 2 - kiss_normal.w / 2,
		progressbar.rect.y + progressbar.rect.h +
		2 * kiss_vslider.h);

	pane1.visible = 1;
    pane2.visible = 1;
    pane3.visible = 1;
    renderPane.visible = 1;
	window1.visible = 1;
	SDL_bool done = SDL_FALSE;
    Tex_Loader texture;
    SDL_Surface *sky = IMG_Load("textures/sky.bmp");
    SDL_Texture *skytexture = SDL_CreateTextureFromSurface(mRenderer, sky);
    SDL_RenderCopy(mRenderer, skytexture, NULL, NULL);
    Matrix3D mat;
    verts = objloader.verts("Objs/motorbike.obj");
    string material_file = "materials/motorbike.mtl";
    vector<MTL> materials = MTLloader.readFile(material_file);



//    mat = Matrix3D (cos(3.2),-sin(3.2),0,sin(3.2),cos(3.2),0,0,0,1);
//    vertexShader.rotateMesh(verts, mat);
//    mat = Matrix3D (cos(1.2),0,sin(1.2),0,1,0,-sin(1.2),0,cos(1.2));
//    vertexShader.rotateMesh(verts, mat);




    face = objloader.faces();
    for(int i = 0; i < face.size(); i++)
    {
    Vector3D normal = face[i].FaceNormal(verts[max(face[i].f1-1,0)],verts[max(face[i].f2-1,0)],verts[max(face[i].f3-1,0)]);
    vertexShader.addNormalsToMap(max(face[i].f1-1,0),normal);
    vertexShader.addNormalsToMap(max(face[i].f2-1,0),normal);
    vertexShader.addNormalsToMap(max(face[i].f3-1,0),normal);
    }
    cout<<"faces and verts read"<<endl;
    cout<<"normals read"<<endl;
    fragShader.get_scanline(materials,s->w, s->h,face,verts);
    SDL_RenderPresent(mRenderer);
    float orig_Spec = 0;
    float Spec = 5;
	double m_last, m_current, deltaTime;
	while (!quit == 1)
    {
       // m_last = m_current;
       // m_current = SDL_GetPerformanceCounter();
        //deltaTime = (double)((m_current - m_last) * 1000 / SDL_GetPerformanceFrequency());
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            const Uint8* keystate = SDL_GetKeyboardState(NULL);
            if (keystate[SDL_SCANCODE_A])
            {
                vertexShader.ClearMap();
                for(int i = 0; i < face.size(); i++)
                {
                    Vector3D normal = face[i].FaceNormal(verts[max(face[i].f1-1,0)],verts[max(face[i].f2-1,0)],verts[max(face[i].f3-1,0)]);
                    vertexShader.addNormalsToMap(max(face[i].f1-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f2-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f3-1,0),normal);
                }
                SDL_RenderClear(mRenderer);
                SDL_RenderCopy(mRenderer, skytexture, NULL, NULL);
                mat = RotateLeft(-0.5);
                verts = vertexShader.rotateMesh(verts, mat);
                fragShader.get_scanline(materials,s->w, s->h,face,verts, Spec);
               // SDL_RenderPresent(mRenderer);
            }
            if (keystate[SDL_SCANCODE_D])
            {
                vertexShader.ClearMap();
                for(int i = 0; i < face.size(); i++)
                {
                    Vector3D normal = face[i].FaceNormal(verts[max(face[i].f1-1,0)],verts[max(face[i].f2-1,0)],verts[max(face[i].f3-1,0)]);
                    vertexShader.addNormalsToMap(max(face[i].f1-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f2-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f3-1,0),normal);
                }
                SDL_RenderClear(mRenderer);
                SDL_RenderCopy(mRenderer, skytexture, NULL, NULL);
                mat = RotateRight(0.5);
                verts = vertexShader.rotateMesh(verts, mat);
                fragShader.get_scanline(materials,s->w, s->h,face,verts, Spec);
               // SDL_RenderPresent(mRenderer);
            }
            if(keystate[SDL_SCANCODE_W])
            {
                SDL_RenderClear(mRenderer);
                vertexShader.ClearMap();
                for(int i = 0; i < face.size(); i++)
                {
                    Vector3D normal = face[i].FaceNormal(verts[max(face[i].f1-1,0)],verts[max(face[i].f2-1,0)],verts[max(face[i].f3-1,0)]);
                    vertexShader.addNormalsToMap(max(face[i].f1-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f2-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f3-1,0),normal);
                }

                SDL_RenderCopy(mRenderer, skytexture, NULL, NULL);
                mat = RotateUp(-0.5);
                verts = vertexShader.rotateMesh(verts, mat);
                fragShader.get_scanline(materials,s->w, s->h,face,verts, Spec);
                SDL_RenderPresent(mRenderer);
            }
            if(keystate[SDL_SCANCODE_S])
            {
                vertexShader.ClearMap();
                for(int i = 0; i < face.size(); i++)
                {
                    Vector3D normal = face[i].FaceNormal(verts[max(face[i].f1-1,0)],verts[max(face[i].f2-1,0)],verts[max(face[i].f3-1,0)]);
                    vertexShader.addNormalsToMap(max(face[i].f1-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f2-1,0),normal);
                    vertexShader.addNormalsToMap(max(face[i].f3-1,0),normal);
                }
                SDL_RenderClear(mRenderer);
                SDL_RenderCopy(mRenderer, skytexture, NULL, NULL);
                mat = RotateDown(0.5);
                verts = vertexShader.rotateMesh(verts, mat);
                fragShader.get_scanline(materials,s->w, s->h,face,verts, Spec);
               // SDL_RenderPresent(mRenderer);
            }
            if (event.type == SDL_QUIT)
            {
                quit = 1;
                cout<<"quit"<<endl;
                SDL_Quit();
                kiss_window_event(&pane1, mWindow, &event, &draw);
                exit(1);
            }

                     //kiss_window_event(&window1, mWindow, &event, &draw);

//                     if(kiss_events.mouse_move_window1_event(mWindow,&event, &draw)[0] != NULL)
//                     {
//                     SDL_RenderClear(mRenderer);
//                     vector<float> pos = kiss_events.mouse_move_window1_event(mWindow,&event, &draw);
//                     cout<<1/pos[0]<<endl;
//                     mat = MoveToPos(0, pos[0], pos[1]);
//                     verts = vertexShader.rotateMesh(verts, mat);
//                     fragShader.get_scanline(temp,s->w, s->h,face,mat,normals, verts);
//                     SDL_RenderPresent(mRenderer);
//                     }

             float Spec_scroll = kiss_events.hscrollbar_event_spec(&hscrollbar1, &amblabel, &event,
                &draw);
                if(orig_Spec != Spec_scroll)
                {
                      Spec = Spec_scroll;
                      SDL_RenderClear(mRenderer);
                      SDL_RenderCopy(mRenderer, skytexture, NULL, NULL);                             //normals = vertexShader.getNormals(verts,face);
                      fragShader.get_scanline(materials,s->w, s->h,face,verts, Spec);
                      orig_Spec = Spec;
                }

            kiss_events.hscrollbar_event_diff(&diffScrollbar, &difflabel, &event,
                &draw);
            kiss_events.hscrollbar_event_amb(&specScrollbar, &speclabel, &event,
                &draw);
            SDL_RenderPresent(mRenderer);
                }

                SDL_RenderPresent(mRenderer);
                if (!draw) continue;

                SDL_RenderClear(renderer);
                kiss_window_draw(&window1, renderer);
                kiss_window_draw(&pane1, renderer);
                kiss_window_draw(&pane2, renderer);
                kiss_window_draw(&pane3, renderer);

                kiss_vscrollbar_draw(&vscrollbar1, renderer);
                kiss_textbox_draw(&textbox1, renderer);
                kiss_hscrollbar_draw(&hscrollbar1, renderer);
                kiss_label_draw(&amblabel, renderer);
                kiss_label_draw(&label1, renderer);
                kiss_hscrollbar_draw(&diffScrollbar, renderer);
                kiss_label_draw(&difflabel, renderer);
                kiss_label_draw(&label2, renderer);
                kiss_hscrollbar_draw(&specScrollbar, renderer);
                kiss_label_draw(&speclabel, renderer);
                kiss_label_draw(&label3, renderer);




                SDL_RenderPresent(renderer);

                draw = 0;
            }
            kiss_clean(&objects);
            return 0;
        }


