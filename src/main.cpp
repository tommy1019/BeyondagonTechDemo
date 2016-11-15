#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

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

    glewInit();

	bool running = true;

    while (running)
    {
        SDL_Event event;
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            running = false;
            continue;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            std::cout << "Key press!" << std::endl;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        SDL_GL_SwapWindow(mainWindow);
    }
    
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
