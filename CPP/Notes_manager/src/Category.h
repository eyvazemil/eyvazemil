#ifndef PA2_PROJECT_CATEGORY_H
#define PA2_PROJECT_CATEGORY_H

#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include "CNote.h"
#include "Time.h"
#include "Text.h"
#include "Letters.h"

class Category {
public:
    //! all needed flags
    bool is_note_shown, is_note_changed;
    int offset, m_X, m_Y;
    //! text of the header of the category
    //! only 12 characters
    //! to show on our database dash
    Text * text;
    //! full text of the header of the category
    //! to show on the header of the category
    Text * offset_size;
    Text * full_category_header;
    //! rectangles and textures to show on the screen
    Rectangle HEADER_category;
    Rectangle HEADER_RECT_category;
    Rectangle BODY_category;
    Texture Delete_category;
    Texture Delete_strong_category;
    //! notes
    std::map<Time, CNote *, compareTime> notes;
    //! pointers to notes
    //! made to access notes by index
    std::vector<CNote *> positions;
    //! letters
    Letters * letters;
public:
    //! constructor
    Category(const std::string &);
    //! destructor
    ~Category();
    //! add a note
    void AddNote(const Time &, CNote *);
    //! delete a note
    void Delete(const Time &);
    //! update a time of some note
    void UpdateTime(const Time &);
    //! operator <
    bool operator<(const Category &) const;
    //! get header
    std::string get_category_header() const;
    //! poll events
    void pollEvents(SDL_Event &);
    //! poll events helper
    std::string pollEventsHelper(SDL_Event &);
    //! draw
    void draw();
    //! change header
    void change_category_header(const std::string &);
    //! initialize offset_size
    void intialize_offset_size();
    //! parse time
    Time parse_time(const std::string &);
    //! get current date and clock
    Time GetCurrentTime();
private:
    int note_to_be_shown;
    std::string category_header;
private:
    //! rectangles and textures to show on the screen
    Texture sign_up_medium_category;
    Texture sign_down_medium_category;
    Texture sign_up_category;
    Texture sign_down_category;
    Texture Add_medium_category;
    Texture Add_category;
    Texture cursor;
    Text HEADER_text_category;
};


#endif //PA2_PROJECT_CATEGORY_H

