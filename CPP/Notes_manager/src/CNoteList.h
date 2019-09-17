#ifndef PA2_PROJECT_CNOTELIST_H
#define PA2_PROJECT_CNOTELIST_H

#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "Time.h"
#include "CNote.h"
#include "Rectangle.h"
#include "Texture.h"
#include "Text.h"
#include "Category.h"

class CNoteList {
public:
    //! all needed error messages and flags
    bool add_error, category_error, is_category_shown, is_category_changed;
    int offset, error_counter, error_category_counter, category_to_be_shown;
    //! all categories
    std::map<std::string, Category *> categories;
    //! pointers to categories
    //! made to access categories by index
    std::vector<Category *> positions;
    //! letters
    Letters letters;
public:
    //! default constructor
    CNoteList();
    //! destructor
    ~CNoteList();
    //! add category
    void AddCategory(const std::string &);
    //! add a note
    void AddNote(CNote *, const Time &, const std::string &);
    //! draw to the screen
    void draw();
    //! poll events
    void pollEvents(SDL_Event &);
    //! delete category
    void DeleteCategory(const std::string &);
    //! search for the category with given header
    std::map<std::string, Category *>::iterator SearchCategory(const std::string &);
    //! initialize offset_size
    void intialize_offset_size();
private:
    //! all needed rectangles and textures
    //! to render on the screen
    Rectangle category, rect;
    Texture sign_up_medium;
    Texture sign_down_medium;
    Texture sign_up;
    Texture sign_down;
    Texture Add_medium;
    Texture Add;
    Texture Delete;
    Texture Delete_strong;
    Text text;
    Text AddError;
    Text CategoryError;
    Text * offset_size;
    Text * temporary_category;
    std::string tmp_category_header;
};

#endif //PA2_PROJECT_CNOTELIST_H
