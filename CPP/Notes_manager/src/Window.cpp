#include <iostream>
#include "Window.h"

//! Window class and all its member variables and methods are made by:
//! https://www.youtube.com/watch?v=G6QNF_bfudI&list=PLEJbjnzD0g7REtyFUestvXSKTyRFs__lu&index=3

//! constructor
Window::Window(const std::string & str, int w, int h) {
    sdl_window_name = str;
    width = w;
    height = h;
    closed = false;
    sdl_window = nullptr;
    sdl_renderer = nullptr;

    closed = !initialize();
}

//! destructor
Window::~Window() {
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyRenderer(sdl_renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

//! create a window
bool Window::initialize() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL!\nError: " << SDL_GetError() << std::endl;
        return false;
    }

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "Could not initialize PNG_IMAGE!\nError: " << SDL_GetError() << std::endl;
        return false;
    }

    if(TTF_Init() == -1) {
        std::cout << "Could not initialize TTF!\nError: " << SDL_GetError() << std::endl;
        return false;
    }

    sdl_window = SDL_CreateWindow(sdl_window_name.c_str(),
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_SHOWN);
    if(sdl_window == nullptr) {
        std::cout << "Could not create a window!\nError: " << SDL_GetError() << std::endl;
        return false;
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if(sdl_renderer == nullptr) {
        std::cout << "Could not create a renderer!\nError: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

//! clear
void Window::clear(const RGBA & rgba) const {
    SDL_SetRenderDrawColor(sdl_renderer, (Uint8)rgba.m_r, (Uint8)rgba.m_g, (Uint8)rgba.m_b, (Uint8)rgba.m_a);
    SDL_RenderClear(sdl_renderer);
}

//! show to screen
void Window::present() const {
    SDL_RenderPresent(sdl_renderer);
}

//! poll events
void Window::pollEvents(SDL_Event & event) {
    if(event.type == SDL_QUIT)
        closed = true;
    else if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_ESCAPE)
            closed = true;
    }
}

//! check if window is closed
bool Window::is_closed() const {
    return closed;
}
