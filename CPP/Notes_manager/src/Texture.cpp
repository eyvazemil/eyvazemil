#include <iostream>
#include "Texture.h"

//! constructor
Texture::Texture() {
    sdl_texture = nullptr;
    rect = nullptr;
}

//! destructor
Texture::~Texture() {
    delete rect;
    SDL_DestroyTexture(sdl_texture);
}

//! load textures from given file
void Texture::loadTexture(const std::string & path) {
    SDL_Surface * loadSurface = IMG_Load(path.c_str());
    if(loadSurface != nullptr) {
        sdl_texture = SDL_CreateTextureFromSurface(Window::sdl_renderer, loadSurface);
        SDL_FreeSurface(loadSurface);
    }
}

//! change the position
//! of the texture on the screen
void Texture::changeRectangle(Rectangle * tmp_rect) {
    delete this->rect;
    this->rect = tmp_rect;
}

//! draw to the screen
void Texture::draw() {
    if(sdl_texture)
        SDL_RenderCopy(Window::sdl_renderer, sdl_texture, nullptr, rect->get_rect());
}

//! check if mouse points
//! to this texture
bool Texture::mouse_points() const {
    if(rect->mouse_points()) return true;
    return false;
}