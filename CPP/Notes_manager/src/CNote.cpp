#include "CNote.h"

//! constructor
CNote::CNote(const std::string & rhs, const std::string & str) : time(rhs), body(str), text(nullptr), second_text(nullptr),
                                        NOTE_BODY(RGBA(102, 230, 255, 255), 600, 450, 455, 140),
                                        NOTE_BODY_RECT(RGBA(255, 255, 255, 255), 590, 420, 460, 165),
                                        Delete_note(), Delete_strong_note()
{
    //! load all needed textures and texts
    Delete_note.loadTexture("./src/Resources/Images/Delete.png");
    Delete_strong_note.loadTexture("./src/Resources/Images/Delete_strong.png");
    Delete_note.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 460, 140));
    Delete_strong_note.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 460, 140));
    text = new Text(20, time, {255, 255, 255, 255});
    second_text = new Text(20, time, {255, 255, 255, 255});
}

//! copy constructor
CNote::CNote(CNote * rhs) : NOTE_BODY(RGBA(102, 230, 255, 255), 600, 450, 455, 140),
                                  NOTE_BODY_RECT(RGBA(255, 255, 255, 255), 590, 420, 460, 165),
                                  Delete_note(), Delete_strong_note()
{
    //! load all needed textures and texts
    Delete_note.loadTexture("./src/Resources/Images/Delete.png");
    Delete_strong_note.loadTexture("./src/Resources/Images/Delete_strong.png");
    Delete_note.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 460, 140));
    Delete_strong_note.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 460, 140));
    time = rhs->time;
    body = rhs->body;
    this->text = new Text(20, rhs->time, {255, 255, 255, 255});
    this->second_text = new Text(20, rhs->time, {255, 255, 255, 255});
}

//! destructor
CNote::~CNote() {
    delete text;
    delete second_text;
}

//! add body to the note
CNote & CNote::AddBody(const std::string & rhs) {
    this->body = rhs;
    return *this;
}

//! draw the note on the screen
void CNote::draw() {
    //! draw needed rectangles and textures
    NOTE_BODY.draw();
    NOTE_BODY_RECT.draw();
    second_text->changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 860, 140));
    second_text->draw();
    if(Delete_note.mouse_points())
        Delete_strong_note.draw();
    else Delete_note.draw();
}

//! change time of the note
void CNote::change_time(const Time & t) {
    this->time = t.time_to_string();
    delete this->text;
    text = new Text(20, time, {255, 255, 255, 255});
    delete this->second_text;
    second_text = new Text(20, time, {255, 255, 255, 255});
}

