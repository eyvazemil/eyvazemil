#ifndef PA2_PROJECT_TEXT_H
#define PA2_PROJECT_TEXT_H

#include "Texture.h"

class Text : public Texture {
public:
    //! constructor
    Text(int, const std::string &, const SDL_Color &);
    //! loadFont method is made by:
    //! https://www.youtube.com/watch?v=FIjj6UVXtXk&list=PLEJbjnzD0g7REtyFUestvXSKTyRFs__lu&index=8
    void loadFont(int, const std::string &, const SDL_Color &);
    //! draw
    void draw() override;
};

#endif //PA2_PROJECT_TEXT_H
