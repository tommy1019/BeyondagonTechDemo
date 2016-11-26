#include <iostream>
#include <math.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include "Matrix4.h"
#include "Shader.h"
#include "SurfaceBall.h"

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

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 0);
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
    
    Shader shader("res/shader/basic", false);
    Shader surfaceShader("res/shader/surfaceBall", true);

    SurfaceBall ball("res/teapot.sball");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    glPointSize(4);

    int uProjectionPoint = glGetUniformLocation(shader.program, "projection");
    int uProjectionSurface = glGetUniformLocation(surfaceShader.program, "projection");
    int uResolution = glGetUniformLocation(surfaceShader.program, "resolution");

    float time = 0;

    Matrix4 projection;
    projection.initProjection(800, 600, 80 * M_PI / 180, 0.1, 100);

    Matrix4 translation;
    translation.initTranslation(0, 0, -3);

    Matrix4 scale;
    scale.initScale(1, 1, 1);

    Matrix4 rotation;
    rotation = rotation.initRotation(0, 0, 0);

    Matrix4 transform;

    float x, y, z;

    x = 0;
    y = 0;
    z = 0;

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
                    z += speed;
                if (event.key.keysym.sym == SDLK_s)
                    z -= speed;
                if (event.key.keysym.sym == SDLK_a)
                    x += speed;
                if (event.key.keysym.sym == SDLK_d)
                    x -= speed;
                if (event.key.keysym.sym == SDLK_q)
                    y += speed;
                if (event.key.keysym.sym == SDLK_e)
                    y -= speed;
            }
        }

        if (translate)
        {
            time++;
            std::cout << "TIME: " << time << std::endl;
        }

        translation.initTranslation(x, y, z);
        rotation = rotation.initRotation((time) * M_PI/180, 0, 0);

        if (filPolys)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
        transform = projection * translation * rotation * scale;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(shader.positionPos);
        glBindBuffer(GL_ARRAY_BUFFER, ball.vertices);
        glVertexAttribPointer(shader.positionPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ball.indices);

        if (drawPoints)
        {
            glUseProgram(shader.program);
            glUniformMatrix4fv(uProjectionPoint, 1, false, &transform.a[0][0]);
            glDrawElements(GL_POINTS, ball.numPatches * 16, GL_UNSIGNED_INT, NULL);
        }

        glUseProgram(surfaceShader.program);
        glUniformMatrix4fv(uProjectionSurface, 1, false, &transform.a[0][0]);
        glUniform1i(uResolution, curResolution);
        glDrawElements(GL_PATCHES, ball.numPatches * 16, GL_UNSIGNED_INT, NULL);

        SDL_GL_SwapWindow(mainWindow);
    }
    
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
