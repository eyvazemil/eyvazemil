#include <iostream>
#include "Text.h"

//! constructor
Text::Text(int font_size, const std::string & message,
           const SDL_Color & color) : Texture() {
    loadFont(font_size, message, color);
}

//! loadFont method is made by:
//! https://www.youtube.com/watch?v=FIjj6UVXtXk&list=PLEJbjnzD0g7REtyFUestvXSKTyRFs__lu&index=8
void Text::loadFont(int font_size,
                    const std::string & message, const SDL_Color & color) {
    TTF_Font * font = TTF_OpenFont("./src/Resources/Fonts/Imperium_Italic.ttf", font_size);
    SDL_Surface * text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(Window::sdl_renderer, text_surface);
    SDL_FreeSurface(text_surface);
    sdl_texture = text_texture;
}

//! draw
void Text::draw() {
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &(rect->get_rect()->w), &(rect->get_rect()->h));
    Texture::draw();
}