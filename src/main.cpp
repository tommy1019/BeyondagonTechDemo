#include <iostream>
#include <math.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>
#include <chrono>

#include <vector>

#include "Entity.h"
#include "Texture.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Shader.h"
#include "TessellationShader.h"
#include "SurfaceBall.h"
#include "Transform.h"
#include "Camera.h"
#include "Surface.h"

#define WIDTH 800
#define HEIGHT 600

#define WINDOW_TITLE "Tech Demo"

void handelInput();
void checkSDLError();

bool running = true;

bool lockedMouse = true;
float speed = .05;

int curResolution = 5;

bool drawPoints = false;
bool filPolys = true;
bool translate = false;

bool drawSingle = false;
int curPatch = 0;

bool surfaceBall = true;

bool keys[256];

SDL_Window *mainWindow;
SDL_GLContext mainContext;

Camera camera;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error initlizating sdl" << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    mainWindow = SDL_CreateWindow(
                                  WINDOW_TITLE,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  WIDTH,
                                  HEIGHT,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    if (!mainWindow)
    {
        std::cout << "Error creating window" << std::endl;
        SDL_Quit();
        return 1;
    }
    
    checkSDLError();
    
    mainContext = SDL_GL_CreateContext(mainWindow);
    checkSDLError();
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    int softwareRendering = -1;
    SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &softwareRendering);
    std::cout << "Gl Accelerated Visual: " << softwareRendering << std::endl;
    
    glPatchParameteri(GL_PATCH_VERTICES, 16);
    glEnable(GL_TEXTURE_2D);
    
    Shader shader("res/shader/basic", false);
    TessellationShader surfaceShader("res/shader/surfaceBall");
    
    Entity teapot("res/teapot.sball", true);
    Texture texture("res/texture/test.png");
    
    Surface teapotOld("teapot.obj");
    
    teapot.transform.rotation.x = (-90) * M_PI/180;
    
    std::vector<Entity> entities;
    
    srand(time(NULL));
    
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
            {
                Entity e = Entity(teapot.surfaceBall);
                
                Transform t;
                t.translation = Vector3(i, j, k);
                t.rotation = Vector3(rand() % 360 * M_PI / 180, rand() % 360 * M_PI / 180, rand() % 360 * M_PI / 180);
                t.scale = Vector3(.1, .1, .1);
                
                e.transform = t;
                
                //entities.push_back(e);
            }
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 1.0f, 0.95f, 1.0f);
    
    glPointSize(4);
    
    float gameTime = 0;
    
    Matrix4 projection = Matrix4::initProjection(800, 600, 80 * M_PI / 180, 0.1, 100);
    Transform::projection = projection;
    
    for (int i = 0; i < 256; i++)
        keys[i] = false;
    
    long double startTime = time(NULL) * 1000;
    long double secondCounter = 0;
    int frames;
    
    //std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    while (running)
    {
        //        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        //        std::cout << "Time Elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(now - start).count() << std::endl;
        //        start = now;
        
        long double curTime = time(NULL) * 1000;
        long double dTime = curTime - startTime;
        startTime = curTime;
        
        secondCounter += dTime;
        frames++;
        if (secondCounter > 1000)
        {
            secondCounter -= 1000;
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
        }
        
        handelInput();
        
        if (translate)
            gameTime++;
        
        teapot.transform.rotation.z = (gameTime) * M_PI/180;
        
        if (filPolys)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (!surfaceBall)
        {
            glUseProgram(shader.program);
            
            Matrix4 transformMatrix = teapot.transform.getTransformMatrix();
            Matrix4 projectionMatrix = Transform::projection * camera.getTransformMatrix() * transformMatrix;
            
            shader.updateTransformMatrix(transformMatrix);
            shader.updateProjectionMatrix(projectionMatrix);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, teapotOld.vertexPtr);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, teapotOld.normalPtr);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, teapotOld.texturePtr);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, teapotOld.indicePtr);
            glDrawElements(GL_TRIANGLES, teapotOld.numIndicies, GL_UNSIGNED_INT, 0);
            
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
        }
        else
        {
            if (drawPoints)
            {
                teapot.renderPoints(shader, camera);
                for (int i = 0; i < entities.size(); i++)
                    entities[i].renderPoints(shader, camera);
            }
            
            surfaceShader.updateGlobals(drawSingle, curPatch);
            surfaceShader.updateEyePos(camera.translation);
            
            texture.useTexture();
            teapot.render(surfaceShader, curResolution, camera);
            
            for (int i = 0; i < entities.size(); i++)
                entities[i].render(surfaceShader, curResolution, camera);
        }
        
        SDL_GL_SwapWindow(mainWindow);
    }
    
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    
    return 0;
}

void handelInput()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
            continue;
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym < 256)
                keys[event.key.keysym.sym] = false;
            
            if (event.key.keysym.sym == SDLK_p)
                drawPoints = !drawPoints;
            if (event.key.keysym.sym == SDLK_o)
                filPolys = !filPolys;
            if (event.key.keysym.sym == SDLK_t)
                translate = !translate;
            if (event.key.keysym.sym == SDLK_i)
            {
                curResolution++;
                std::cout << "Res: " << curResolution << std::endl;
            }
            if (event.key.keysym.sym == SDLK_k)
            {
                curResolution--;
                std::cout << "Res: " << curResolution << std::endl;
            }
            if (event.key.keysym.sym == SDLK_u)
                curPatch++;
            if (event.key.keysym.sym == SDLK_j)
                curPatch--;
            if (event.key.keysym.sym == SDLK_y)
                drawSingle = !drawSingle;
            if (event.key.keysym.sym == SDLK_z)
                lockedMouse = !lockedMouse;
            if (event.key.keysym.sym == SDLK_g)
                surfaceBall = !surfaceBall;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym < 256)
                keys[event.key.keysym.sym] = true;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            if (lockedMouse)
            {
                float dx = (float)(WIDTH / 2  - event.motion.x) / WIDTH;
                float dy = (float)(HEIGHT / 2 - event.motion.y) /  HEIGHT;
                
                camera.rotation = camera.rotation * Quaternion::initRotation(Vector3(0, 1, 0), -dx).normalized();
                camera.rotation = camera.rotation * Quaternion::initRotation(camera.rotation.getLeft(), dy).normalized();
                
                SDL_WarpMouseInWindow(mainWindow, WIDTH / 2, HEIGHT / 2);
            }
        }
    }
    
    if (keys[SDLK_w])
        camera.translation = camera.translation - camera.rotation.getForward() * speed;
    if (keys[SDLK_s])
        camera.translation = camera.translation - camera.rotation.getBack() * speed;
    if (keys[SDLK_a])
        camera.translation = camera.translation + camera.rotation.getLeft() * speed;
    if (keys[SDLK_d])
        camera.translation = camera.translation + camera.rotation.getRight() * speed;
    if (keys[SDLK_q])
        camera.translation = camera.translation - camera.rotation.getUp() * speed;
    if (keys[SDLK_e])
        camera.translation = camera.translation - camera.rotation.getDown() * speed;
}

void checkSDLError()
{
    std::string error = SDL_GetError();
    if (error != "")
    {
        std::cout << "Error (SDL): " << error << std::endl;
        SDL_ClearError();
    }
}


