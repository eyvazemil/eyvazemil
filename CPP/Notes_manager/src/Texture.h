#ifndef PA2_PROJECT_TEXTURE_H
#define PA2_PROJECT_TEXTURE_H

#include "Rectangle.h"

class Texture {
public:
    //! contructor
    Texture();
    //! destructor
    ~Texture();
    //! load textures from given file
    void loadTexture(const std::string &);
    //! change the position
    //! of the texture on the screen
    void changeRectangle(Rectangle *);
    //! draw to the screen
    virtual void draw();
    //! check if mouse points
    //! to this texture
    bool mouse_points() const;
public:
    //! sdl texture
    SDL_Texture * sdl_texture;
    //! rectangle where this texture
    //! is located on the screen
    Rectangle * rect;
};

#endif //PA2_PROJECT_TEXTURE_H
