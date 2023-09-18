#include "application.hpp"

#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

std::chrono::_V2::steady_clock::time_point now()
{
    return std::chrono::steady_clock::now();
}

Application::Application()
{
    initializeSdl();

    running = false;
    fullscreen = false;
}

void Application::run()
{
    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<double, std::chrono::_V2::steady_clock::period>> start;

    std::chrono::duration<double> delta;
    
    int counter = 0;

    running = true;
    draw();
    while (running)
    {
        start = now();

        handleEvents();

        tick();

        draw();

        delta = now() - start;

        if (counter % 600 == 0)
            std::cout << delta.count() << "\n";
        
        counter += 1;
    }

    destroySdl();
}

void Application::initializeSdl()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GetCurrentDisplayMode(0, &displayMode);

    displayWidth = displayMode.w / 2;
    displayHeight = displayMode.h / 2;
    center.x = displayWidth / 2;
    center.y = displayHeight / 2;

    uint32_t windowFlags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow(
        "lenia testing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        displayWidth, displayHeight,
        windowFlags);
    
    uint32_t renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, renderFlags);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    keyboardState = SDL_GetKeyboardState(NULL);
}
void Application::destroySdl()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::handleEvents()
{
    SDL_PumpEvents();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                displayWidth = event.window.data1;
                displayHeight = event.window.data2;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;
            case SDL_SCANCODE_F11:
                if (fullscreen)
                {
                    SDL_SetWindowFullscreen(window, 0);
                }
                else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                fullscreen = !fullscreen;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Application::tick()
{
    //tick things
}

void Application::draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 15, 47, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
