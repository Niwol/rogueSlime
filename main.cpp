#include <iostream>

#include <SDL2/SDL.h>

constexpr int SCREEN_W = 800;
constexpr int SCREEN_H = 600;

bool init(SDL_Window **w, SDL_Renderer **r);

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    bool quit = false;

    if (!init(&window, &renderer))
    {
        printf("FAIL: init\n");
        exit(0);
    }
    else
    {
        SDL_Event e;

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;

                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
            SDL_RenderClear(renderer);

            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
}

bool init(SDL_Window **w, SDL_Renderer **r)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("FAIL: sdl init\n");
        printf("%s\n", SDL_GetError());
        return false;
    }

    *w = SDL_CreateWindow("Rogue Slime", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if (!*w)
    {
        printf("FAIL: sdl create window\n");
        SDL_Quit();
        return false;
    }

    *r = SDL_CreateRenderer(*w, 0, SDL_RENDERER_ACCELERATED);
    if (!*r)
    {
        printf("FAIL: sdl create renderer\n");
        SDL_DestroyWindow(*w);
        SDL_Quit();
        return false;
    }

    return true;
}