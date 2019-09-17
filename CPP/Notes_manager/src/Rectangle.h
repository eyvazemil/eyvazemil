#ifndef PA2_PROJECT_RECTANGLE_H
#define PA2_PROJECT_RECTANGLE_H

#include "Window.h"
#include "RGBA.h"

class Rectangle {
public:
    //! constructor
    Rectangle(const RGBA &, int, int, int, int);
    Rectangle(const Rectangle &);
    //! poll events
    void pollEvents(SDL_Event &);
    //! draw
    void draw();
    //! mouse position is here
    bool mouse_points() const;
    //! get rect
    SDL_Rect * get_rect();
protected:
    //! sdl rectangle
    SDL_Rect rect;
    //! color of the rectangle
    RGBA rgba;
    //! position of the rectangle
    int width, height;
    int x_pos, y_pos;
    //! if outline of the rectangle is shown
    bool outline;
};

#endif //PA2_PROJECT_RECTANGLE_H
