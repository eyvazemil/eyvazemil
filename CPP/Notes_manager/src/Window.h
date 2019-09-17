#ifndef PA2_PROJECT_SDL_HANDLING_H
#define PA2_PROJECT_SDL_HANDLING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "RGBA.h"

//! Window class and all its member variables and methods are made by:
//! https://www.youtube.com/watch?v=G6QNF_bfudI&list=PLEJbjnzD0g7REtyFUestvXSKTyRFs__lu&index=3

class Window {
public:
    Window(const std::string &, int, int);
    ~Window();
    //! create a window
    bool initialize();
    //! clear
    void clear(const RGBA & color) const;
    //! show to screen
    void present() const;
    //! poll events
    void pollEvents(SDL_Event &);
    //! check if window is closed
    bool is_closed() const;
    //! renderer
    static SDL_Renderer * sdl_renderer;
private:
    bool closed;
    int width, height;
    std::string sdl_window_name;
    SDL_Window * sdl_window;
};

#endif //PA2_PROJECT_SDL_HANDLING_H
