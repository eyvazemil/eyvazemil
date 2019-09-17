#include "Rectangle.h"
#include <iostream>

//! constructor
Rectangle::Rectangle(const RGBA & p_rgba, int w, int h, int x, int y) : rgba(p_rgba) {
    width = w;
    height = h;
    x_pos = x;
    y_pos = y;
    rect.w = width;
    rect.h = height;
    rect.x = x_pos;
    rect.y = y_pos;
    outline = false;
}

Rectangle::Rectangle(const Rectangle & rhs) {
    this->width = rhs.width;
    this->height = rhs.height;
    this->x_pos = rhs.x_pos;
    this->y_pos = rhs.y_pos;
    rect.w = rhs.width;
    rect.h = rhs.height;
    rect.x = rhs.x_pos;
    rect.y = rhs.y_pos;
    outline = rhs.outline;
}

//! poll events
void Rectangle::pollEvents(SDL_Event & event) {
    if(event.type == SDL_MOUSEMOTION) {
        if(event.motion.x >= x_pos && event.motion.x <= x_pos + width &&
           event.motion.y >= y_pos && event.motion.y <= y_pos + height) {
            outline = false;
        }
    }
}

//! draw
void Rectangle::draw() {
    if(this->mouse_points()) {
        SDL_Rect tmp_rect = {x_pos - 1, y_pos - 1, width + 2, height + 2};
        SDL_SetRenderDrawColor(Window::sdl_renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(Window::sdl_renderer, &tmp_rect);
    }
    SDL_Color color = {(Uint8) rgba.m_r, (Uint8) rgba.m_g, (Uint8) rgba.m_b, (Uint8) rgba.m_a};
    SDL_SetRenderDrawColor(Window::sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Window::sdl_renderer, &rect);
}

//! mouse position is here
bool Rectangle::mouse_points() const {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(x >= x_pos && x <= x_pos + width &&
       y >= y_pos && y <= y_pos + height) return true;
    return false;
}

//! get rect
SDL_Rect * Rectangle::get_rect() {
    return &rect;
}
