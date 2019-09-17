#ifndef PA2_PROJECT_CNOTE_H
#define PA2_PROJECT_CNOTE_H

#include <string>
#include <iostream>
#include "Text.h"
#include "Time.h"
#include "Letters.h"

class CNote {
public:
    //! body of the note
    std::string body;
    //! time of the note created or updated
    std::string time;
    //! time text to show on category dash
    //! and to show on the note body itself
    Text * text, * second_text;
    //! rectangles and textures
    //! to show on the screen
    Rectangle NOTE_BODY;
    Rectangle NOTE_BODY_RECT;
    Texture Delete_note;
    Texture Delete_strong_note;
public:
    //! constructor
    CNote(const std::string &, const std::string & str = "");
    //! copy constructor
    CNote(CNote *);
    //! destructor
    ~CNote();
    //! add body to the note
    CNote & AddBody(const std::string &);
    //! draw the note on the screen
    void draw();
    //! change the time of the note
    void change_time(const Time &);
};

#endif //PA2_PROJECT_CNOTE_H
