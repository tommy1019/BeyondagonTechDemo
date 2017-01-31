#include <iostream>
#include <math.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>

#include <vector>

#include "Entity.h"
#include "Texture.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Shader.h"
#include "TessellationShader.h"
#include "SurfaceBall.h"
#include "Transform.h"

#define WIDTH 800
#define HEIGHT 600

#define WINDOW_TITLE "Beyondagon Tech Demo"

void checkSDLError()
{
	std::string error = SDL_GetError();
	if (error != "")
	{
		std::cout << "Error (SDL): " << error << std::endl;
		SDL_ClearError();
	}
}

int main()
{
    SDL_Window *mainWindow;
    SDL_GLContext mainContext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error initlizating sdl" << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

//    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 0);
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

	bool running = true;

    glPatchParameteri(GL_PATCH_VERTICES, 16);
    glEnable(GL_TEXTURE_2D);

    Shader shader("res/shader/basic", false);
    TessellationShader surfaceShader("res/shader/surfaceBall");

    Entity teapot("res/teapot.sball");
    Texture texture("res/texture/teapot.png");

    std::vector<Entity> entities;

    srand(time(NULL));

//    for (int i = 0; i < 100; i++)
//        entities.push_back(Entity(teapot.surfaceBall, Transform(Vector3(rand() % 4 - 2, rand() % 4 - 2, -3 + rand() % 2), Vector3(rand() % 360 * M_PI / 180, rand() % 360 * M_PI / 180, rand() % 360 * M_PI / 180), Vector3(.1, .1, .1))));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPointSize(4);

    float time = 0;

    Matrix4 projection = Matrix4::initProjection(800, 600, 80 * M_PI / 180, 0.1, 100);
    Transform::projection = projection;

    float speed = .1;

    int curResolution = 1;

    bool drawPoints = false;
    bool filPolys = true;
    bool translate = false;

    while (running)
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
                if (event.key.keysym.sym == SDLK_p)
                    drawPoints = !drawPoints;
                if (event.key.keysym.sym == SDLK_o)
                    filPolys = !filPolys;
                if (event.key.keysym.sym == SDLK_t)
                    translate = !translate;
                if (event.key.keysym.sym == SDLK_i)
                    curResolution++;
                if (event.key.keysym.sym == SDLK_k)
                    curResolution--;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_w)
                    teapot.transform.translation.z += speed;
                if (event.key.keysym.sym == SDLK_s)
                    teapot.transform.translation.z -= speed;
                if (event.key.keysym.sym == SDLK_a)
                    teapot.transform.translation.x += speed;
                if (event.key.keysym.sym == SDLK_d)
                    teapot.transform.translation.x -= speed;
                if (event.key.keysym.sym == SDLK_q)
                    teapot.transform.translation.y += speed;
                if (event.key.keysym.sym == SDLK_e)
                    teapot.transform.translation.y -= speed;
            }
        }

        if (translate)
        {
            time++;
//            std::cout << "TIME: " << time << std::endl;
//            curResolution = abs((int) (cos(M_PI/180 * (time)) * 5)) + 2;
        }

        teapot.transform.rotation.y = (time) * M_PI/180;

        if (filPolys)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (drawPoints)
        {
            teapot.renderPoints(shader);
            for (int i = 0; i < entities.size(); i++)
                entities[i].renderPoints(shader);
        }

        

        texture.useTexture();
        teapot.render(surfaceShader, curResolution);
        for (int i = 0; i < entities.size(); i++)
            entities[i].render(surfaceShader, curResolution);

        SDL_GL_SwapWindow(mainWindow);
    }
    
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
