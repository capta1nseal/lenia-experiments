#ifndef _LENIATESTAPPLICATION_
#define _LENIATESTAPPLICATION_

#include <chrono>

#include <SDL2/SDL.h>

class Application
{
public:
    Application();

    void run();

private:
    bool running;
    unsigned int displayWidth, displayHeight;
    bool fullscreen;
    SDL_Point center;

    SDL_DisplayMode displayMode;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Event event;
    const uint8_t *keyboardState;

    void initializeSdl();
    void destroySdl();

    void handleEvents();

    void tick();

    void draw();
};

#endif
