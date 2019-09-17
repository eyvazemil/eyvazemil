#include "Category.h"

//! constructor
Category::Category(const std::string & str) : category_header(str), text(nullptr), offset_size(nullptr),
                                              sign_up_medium_category(), sign_down_medium_category(),
                                              sign_up_category(), sign_down_category(),
                                              Add_medium_category(), Add_category(), cursor(),
                                              Delete_category(), Delete_strong_category(),
                                              HEADER_category(RGBA(102, 230, 255, 255), 816, 30, 240, 105),
                                              HEADER_RECT_category(RGBA(255, 255, 255, 255), 650, 28, 380, 106),
                                              BODY_category(RGBA(102, 230, 255, 255), 200, 450, 240, 140),
                                              HEADER_text_category(28, "Header :", {255, 255, 255, 255})
{
    //! load all needed textures and texts
    sign_up_medium_category.loadTexture("./src/Resources/Images/triangle_up_medium.png");
    sign_down_medium_category.loadTexture("./src/Resources/Images/triangle_down_medium.png");
    sign_up_category.loadTexture("./src/Resources/Images/triangle_up.png");
    sign_down_category.loadTexture("./src/Resources/Images/triangle_down.png");
    Add_medium_category.loadTexture("./src/Resources/Images/Add_medium.png");
    Add_category.loadTexture("./src/Resources/Images/Add.png");
    cursor.loadTexture("./src/Resources/Images/Cursor.png");
    Delete_category.loadTexture("./src/Resources/Images/Delete.png");
    Delete_strong_category.loadTexture("./src/Resources/Images/Delete_strong.png");
    sign_up_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 420, 540));
    sign_up_medium_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 420, 540));
    sign_down_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 420, 570));
    sign_down_medium_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 420, 570));
    Add_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 330, 550));
    Add_medium_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 330, 550));
    Delete_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 375, 550));
    Delete_strong_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 375, 550));
    HEADER_text_category.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 816, 30, 240, 105));
    text = new Text(20, str.substr(0, 12), {255, 255, 255, 255});
    full_category_header = new Text(20, str.substr(0, 30), {0, 0, 0, 255});
    full_category_header->changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 650, 28, 390, 108));
    offset = 1;
    is_note_shown = false;
    is_note_changed = false;
    m_X = 0;
    m_Y = 0;
}

//! destructor
Category::~Category() {
    delete this->text;
    delete this->offset_size;
    delete this->full_category_header;
    for(auto & it : notes)
        delete it.second;
}

//! add a note
void Category::AddNote(const Time & t, CNote * note) {
    Time time(t);
    notes.insert(std::pair<Time, CNote *>(time, note));
    //! set positions of notes on the screen
    int count = 0;
    for(auto & ti : notes) {
        int y_pos = 141 + 32 * (count % 12);
        (ti.second->text)->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 198, 30, 241, y_pos));
        count++;
    }
    //! set pointers to notes
    positions.clear();
    for(auto & ti : notes)
        positions.push_back(ti.second);
    //! set the offset
    delete offset_size;
    std::string off = std::to_string(offset);
    offset_size = new Text(20, off + "/" + std::to_string(notes.size()), {255, 255, 255, 255});
    offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 250, 550));
}

//! delete a note
void Category::Delete(const Time & time) {
    auto it = notes.find(time);
    //! if such a note exists, delete it
    if(it != notes.end()) {
        delete it->second;
        notes.erase(it);
        //! renew the positions of nootes on the screen
        int count = 0;
        for(auto & i : notes) {
            int y_pos = 141 + 32 * (count % 12);
            (i.second->text)->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 198, 30, 241, y_pos));
            count++;
        }
        //! renew pointers to notes
        positions.clear();
        for(auto & ti : notes)
            positions.push_back(ti.second);
        //! change offset
        if(offset > notes.size() && offset > 12)
            offset -= 12;
        delete offset_size;
        std::string off = std::to_string(offset);
        if(notes.empty())
            offset_size = new Text(20, "0/" + std::to_string(notes.size()), {255, 255, 255, 255});
        else offset_size = new Text(20, off + "/" + std::to_string(notes.size()), {255, 255, 255, 255});
        offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 250, 550));
    }
}

//! update a time of some note
void Category::UpdateTime(const Time & t) {
    auto it = notes.find(t);
    //! if such a note exists,
    //! set its time to the current time
    if(it != notes.end()) {
        CNote * tmp_note = it->second;
        notes.erase(it);
        Time tmp_time = GetCurrentTime();
        tmp_note->change_time(tmp_time);
        notes.insert(std::pair<Time, CNote *>(tmp_time, tmp_note));
        //! renew positions of the notes on the screen
        int count = 0;
        for(auto & ti : notes) {
            int y_pos = 141 + 32 * (count % 12);
            (ti.second->text)->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 198, 30, 241, y_pos));
            count++;
        }
        //! renew pointers to notes
        positions.clear();
        for(auto & ti : notes)
            positions.push_back(ti.second);

        //! find the newly updated note in notes
        if(is_note_shown) {
            int count1 = 0;
            for(auto & i : notes) {
                if(i.first.time_to_string() == tmp_time.time_to_string()) {
                    note_to_be_shown = count1;
                    break;
                }
                count1++;
            }
        }
    }
}

//! operator <
bool Category::operator<(const Category & rhs) const {
    return this->category_header < rhs.category_header;
}

//! get header
std::string Category::get_category_header() const {
    return category_header;
}

//! poll events
void Category::pollEvents(SDL_Event & event) {
    //! if keyboard event occured
    if(event.type == SDL_KEYDOWN) {
        if(is_note_changed) {
            bool tmp_flag = true;
            //! if arrows were clicked, change cursor position
            if(event.key.keysym.sym == SDLK_RIGHT) {
                tmp_flag = false;
                if(m_X != 27 || m_Y != 19) {
                    if(m_X == 27 && m_Y != 19 && positions[note_to_be_shown]->body.size() >= (m_Y + 1) * 28) {
                        m_X = 0;
                        m_Y++;
                    } else {
                        if(positions[note_to_be_shown]->body.size() >= (m_X + 1) + m_Y * 28)
                            m_X++;
                    }
                    cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
                }
            } else if(event.key.keysym.sym == SDLK_LEFT) {
                tmp_flag = false;
                if(m_X != 0 || m_Y != 0) {
                    if(m_X == 0 && m_Y != 0) {
                        m_X = 27;
                        m_Y--;
                    } else
                        m_X--;
                    cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
                }
            } else if(event.key.keysym.sym == SDLK_UP) {
                tmp_flag = false;
                if(m_Y > 0)
                    m_Y--;
                cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
            } else if(event.key.keysym.sym == SDLK_DOWN) {
                tmp_flag = false;
                if(m_Y < 19 && positions[note_to_be_shown]->body.size() >= m_X + (m_Y + 1) * 28)
                    m_Y++;
                else if(m_Y < 19 && positions[note_to_be_shown]->body.size() > (m_Y + 1) * 28) {
                    m_Y++;
                    m_X = (int)positions[note_to_be_shown]->body.size() - m_Y * 28;
                }
                cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
            }
            //! if backspace was clicked, delete the character to the left of cursor
            else if(event.key.keysym.sym == SDLK_BACKSPACE && !positions[note_to_be_shown]->body.empty() &&
                      (m_X != 0 || m_Y != 0)) {
                std::string tmp;
                for(int i = 0; i < m_X + m_Y * 28 - 1; i++)
                    tmp += positions[note_to_be_shown]->body[i];
                for(int i = m_X + m_Y * 28; i < positions[note_to_be_shown]->body.size(); i++)
                    tmp += positions[note_to_be_shown]->body[i];
                positions[note_to_be_shown]->body = tmp;
                if(m_X != 0 || m_Y != 0) {
                    if(m_X == 0 && m_Y != 0) {
                        m_X = 27;
                        m_Y--;
                    } else if(m_X > 0)
                        m_X--;
                    cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
                }
            }

            //! if anything else than backspace was pressed, change the note
            std::string str = pollEventsHelper(event);
            if(!str.empty() && positions[note_to_be_shown]->body.size() + str.size() < 560) {
                positions[note_to_be_shown]->body.insert(m_X + (unsigned long) m_Y * 28, str);
                if(m_X != 27 || m_Y != 19) {
                    if(m_X == 27 && m_Y != 19 && positions[note_to_be_shown]->body.size() >= (m_Y + 1) * 28) {
                        m_X = 0;
                        m_Y++;
                    } else {
                        if(positions[note_to_be_shown]->body.size() >= (m_X + 1) + m_Y * 28)
                            m_X++;
                        }
                    cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
                }
            }
            //! every time the key was pressed, change the time of the note
            if(tmp_flag) {
                Time t(parse_time(positions[note_to_be_shown]->time));
                UpdateTime(t);
            }
        }
    }
    //! if mouse was clicked
    else if(event.type == SDL_MOUSEBUTTONUP) {
        is_note_changed = false;
        //! sign up was clicked
        //! change the offset
        if(sign_up_category.mouse_points()) {
            if(offset > 12) {
                offset -= 12;
                delete offset_size;
                std::string off = std::to_string(offset);
                if(notes.empty())
                    offset_size = new Text(20, "0/" + std::to_string(notes.size()), {255, 255, 255, 255});
                else offset_size = new Text(20, off + "/" + std::to_string(notes.size()), {255, 255, 255, 255});
                offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 250, 550));
            }
        }
        //! sign down was clicked
        //! change the offset
        else if(sign_down_category.mouse_points()) {
            if(offset + 12 <= notes.size()) {
                offset += 12;
                delete offset_size;
                std::string off = std::to_string(offset);
                if(notes.empty())
                    offset_size = new Text(20, "0/" + std::to_string(notes.size()), {255, 255, 255, 255});
                else offset_size = new Text(20, off + "/" + std::to_string(notes.size()), {255, 255, 255, 255});
                offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 250, 550));
            }
        }
        //! add new note
        else if(Add_category.mouse_points()) {
            Time time = GetCurrentTime();
            CNote * note = new CNote(time.time_to_string());
            AddNote(time, note);
        }

        //! if note was clicked,
        //! decide which one to show on the screen
        {
            int count = offset;
            for(int i = offset - 1; i < positions.size(); i++) {
                if(positions[i]->text->rect->mouse_points()) {
                    is_note_shown = true;
                    note_to_be_shown = i;
                    break;
                } else {
                    if(positions[i]->NOTE_BODY.mouse_points()) {
                        if(is_note_shown)
                            is_note_shown = true;
                        break;
                    } else {
                        is_note_shown = false;
                    }
                }
                if(count % 12 == 0) break;
                count++;
            }
        }

        //! delete or change the note
        if(is_note_shown) {
            //! if delete was pressed, delete the note
            if(positions[note_to_be_shown]->Delete_note.mouse_points()) {
                Delete(Time(parse_time(positions[note_to_be_shown]->time)));
                is_note_shown = false;
            }
            //! if note body was pressed, change the note
            else if(!is_note_changed && positions[note_to_be_shown]->NOTE_BODY_RECT.mouse_points()) {
                is_note_changed = true;
                m_X = 0;
                m_Y = 0;
                cursor.changeRectangle(new Rectangle(RGBA(255, 255, 255, 255), 2, 20, 470 + m_X * 20, 170 + m_Y * 20));
            }
        }
    }
}

//! poll events helper
//! selects which character was pressed
//! and return a string with that character
std::string Category::pollEventsHelper(SDL_Event & event) {
    std::string str;
    if(event.key.keysym.sym == SDLK_SPACE)
        str = " ";
    else if(event.key.keysym.sym == SDLK_PERIOD)
        str = ".";
    else if(event.key.keysym.sym == SDLK_COMMA)
        str = ",";
    else if(event.key.keysym.sym == SDLK_SEMICOLON  && SDL_GetModState() & KMOD_SHIFT)
        str = ":";
    else if(event.key.keysym.sym == SDLK_SEMICOLON)
        str = ";";
    else if(event.key.keysym.sym == SDLK_SLASH  && SDL_GetModState() & KMOD_SHIFT)
        str = "?";
    else if(event.key.keysym.sym == SDLK_SLASH)
        str = "/";
    else if(event.key.keysym.sym == SDLK_1  && SDL_GetModState() & KMOD_SHIFT)
        str = "!";
    else if(event.key.keysym.sym == SDLK_QUOTE  && SDL_GetModState() & KMOD_SHIFT)
        str = "\"";
    else if(event.key.keysym.sym == SDLK_QUOTE)
        str = "\'";
    else if(event.key.keysym.sym == SDLK_2  && SDL_GetModState() & KMOD_SHIFT)
        str = "@";
    else if(event.key.keysym.sym == SDLK_3  && SDL_GetModState() & KMOD_SHIFT)
        str = "#";
    else if(event.key.keysym.sym == SDLK_4  && SDL_GetModState() & KMOD_SHIFT)
        str = "$";
    else if(event.key.keysym.sym == SDLK_5  && SDL_GetModState() & KMOD_SHIFT)
        str = "%";
    else if(event.key.keysym.sym == SDLK_6  && SDL_GetModState() & KMOD_SHIFT)
        str = "^";
    else if(event.key.keysym.sym == SDLK_7  && SDL_GetModState() & KMOD_SHIFT)
        str = "&";
    else if(event.key.keysym.sym == SDLK_8  && SDL_GetModState() & KMOD_SHIFT)
        str = "*";
    else if(event.key.keysym.sym == SDLK_9  && SDL_GetModState() & KMOD_SHIFT)
        str = "(";
    else if(event.key.keysym.sym == SDLK_0  && SDL_GetModState() & KMOD_SHIFT)
        str = ")";
    else if(event.key.keysym.sym == SDLK_MINUS  && SDL_GetModState() & KMOD_SHIFT)
        str = "_";
    else if(event.key.keysym.sym == SDLK_MINUS)
        str = "-";
    else if(event.key.keysym.sym == SDLK_EQUALS  && SDL_GetModState() & KMOD_SHIFT)
        str = "+";
    else if(event.key.keysym.sym == SDLK_EQUALS)
        str = "=";
    else if(event.key.keysym.sym == SDLK_a && SDL_GetModState() & KMOD_SHIFT)
        str = "A";
    else if(event.key.keysym.sym == SDLK_b && SDL_GetModState() & KMOD_SHIFT)
        str = "B";
    else if(event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_SHIFT)
        str = "C";
    else if(event.key.keysym.sym == SDLK_d && SDL_GetModState() & KMOD_SHIFT)
        str = "D";
    else if(event.key.keysym.sym == SDLK_e && SDL_GetModState() & KMOD_SHIFT)
        str = "E";
    else if(event.key.keysym.sym == SDLK_f && SDL_GetModState() & KMOD_SHIFT)
        str = "F";
    else if(event.key.keysym.sym == SDLK_g && SDL_GetModState() & KMOD_SHIFT)
        str = "G";
    else if(event.key.keysym.sym == SDLK_h && SDL_GetModState() & KMOD_SHIFT)
        str = "H";
    else if(event.key.keysym.sym == SDLK_i && SDL_GetModState() & KMOD_SHIFT)
        str = "I";
    else if(event.key.keysym.sym == SDLK_j && SDL_GetModState() & KMOD_SHIFT)
        str = "J";
    else if(event.key.keysym.sym == SDLK_k && SDL_GetModState() & KMOD_SHIFT)
        str = "K";
    else if(event.key.keysym.sym == SDLK_l && SDL_GetModState() & KMOD_SHIFT)
        str = "L";
    else if(event.key.keysym.sym == SDLK_m && SDL_GetModState() & KMOD_SHIFT)
        str = "M";
    else if(event.key.keysym.sym == SDLK_n && SDL_GetModState() & KMOD_SHIFT)
        str = "N";
    else if(event.key.keysym.sym == SDLK_o && SDL_GetModState() & KMOD_SHIFT)
        str = "O";
    else if(event.key.keysym.sym == SDLK_p && SDL_GetModState() & KMOD_SHIFT)
        str = "P";
    else if(event.key.keysym.sym == SDLK_q && SDL_GetModState() & KMOD_SHIFT)
        str = "Q";
    else if(event.key.keysym.sym == SDLK_r && SDL_GetModState() & KMOD_SHIFT)
        str = "R";
    else if(event.key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_SHIFT)
        str = "S";
    else if(event.key.keysym.sym == SDLK_t && SDL_GetModState() & KMOD_SHIFT)
        str = "T";
    else if(event.key.keysym.sym == SDLK_u && SDL_GetModState() & KMOD_SHIFT)
        str = "U";
    else if(event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_SHIFT)
        str = "V";
    else if(event.key.keysym.sym == SDLK_w && SDL_GetModState() & KMOD_SHIFT)
        str = "W";
    else if(event.key.keysym.sym == SDLK_x && SDL_GetModState() & KMOD_SHIFT)
        str = "X";
    else if(event.key.keysym.sym == SDLK_y && SDL_GetModState() & KMOD_SHIFT)
        str = "Y";
    else if(event.key.keysym.sym == SDLK_z && SDL_GetModState() & KMOD_SHIFT)
        str = "Z";
    else if(event.key.keysym.sym == SDLK_a)
        str = "a";
    else if(event.key.keysym.sym == SDLK_b)
        str = "b";
    else if(event.key.keysym.sym == SDLK_c)
        str = "c";
    else if(event.key.keysym.sym == SDLK_d)
        str = "d";
    else if(event.key.keysym.sym == SDLK_e)
        str = "e";
    else if(event.key.keysym.sym == SDLK_f)
        str = "f";
    else if(event.key.keysym.sym == SDLK_g)
        str = "g";
    else if(event.key.keysym.sym == SDLK_h)
        str = "h";
    else if(event.key.keysym.sym == SDLK_i)
        str = "i";
    else if(event.key.keysym.sym == SDLK_j)
        str = "j";
    else if(event.key.keysym.sym == SDLK_k)
        str = "k";
    else if(event.key.keysym.sym == SDLK_l)
        str = "l";
    else if(event.key.keysym.sym == SDLK_m)
        str = "m";
    else if(event.key.keysym.sym == SDLK_n)
        str = "n";
    else if(event.key.keysym.sym == SDLK_o)
        str = "o";
    else if(event.key.keysym.sym == SDLK_p)
        str = "p";
    else if(event.key.keysym.sym == SDLK_q)
        str = "q";
    else if(event.key.keysym.sym == SDLK_r)
        str = "r";
    else if(event.key.keysym.sym == SDLK_s)
        str = "s";
    else if(event.key.keysym.sym == SDLK_t)
        str = "t";
    else if(event.key.keysym.sym == SDLK_u)
        str = "u";
    else if(event.key.keysym.sym == SDLK_v)
        str = "v";
    else if(event.key.keysym.sym == SDLK_w)
        str = "w";
    else if(event.key.keysym.sym == SDLK_x)
        str = "x";
    else if(event.key.keysym.sym == SDLK_y)
        str = "y";
    else if(event.key.keysym.sym == SDLK_z)
        str = "z";
    else if(event.key.keysym.sym == SDLK_0)
        str = "0";
    else if(event.key.keysym.sym == SDLK_1)
        str = "1";
    else if(event.key.keysym.sym == SDLK_2)
        str = "2";
    else if(event.key.keysym.sym == SDLK_3)
        str = "3";
    else if(event.key.keysym.sym == SDLK_4)
        str = "4";
    else if(event.key.keysym.sym == SDLK_5)
        str = "5";
    else if(event.key.keysym.sym == SDLK_6)
        str = "6";
    else if(event.key.keysym.sym == SDLK_7)
        str = "7";
    else if(event.key.keysym.sym == SDLK_8)
        str = "8";
    else if(event.key.keysym.sym == SDLK_9)
        str = "9";

    return str;
}

//! draw
void Category::draw() {
    //! draw initial rectangles and textures
    HEADER_category.draw();
    HEADER_RECT_category.draw();
    HEADER_text_category.draw();
    BODY_category.draw();
    if(sign_up_category.mouse_points())
        sign_up_category.draw();
    else sign_up_medium_category.draw();
    if(sign_down_category.mouse_points())
        sign_down_category.draw();
    else sign_down_medium_category.draw();
    if(Add_category.mouse_points())
        Add_category.draw();
    else Add_medium_category.draw();
    if(Delete_category.mouse_points())
        Delete_strong_category.draw();
    else Delete_category.draw();
    full_category_header->draw();
    offset_size->draw();

    //! draw notes
    {
        int count = offset;
        for(int i = offset - 1; i < positions.size(); i++) {
            positions[i]->text->rect->draw();
            positions[i]->text->draw();
            if(count % 12 == 0) break;
            count++;
        }
    }

    //! draw the note itself, if it is shown
    if(is_note_shown) {
        positions[note_to_be_shown]->draw();
        {
            //! draw the characters in the body of the note
            //! using already existing textures of letters
            int x = 470, y = 170;
            for(int i = 0; i < (int)positions[note_to_be_shown]->body.size(); i++) {
                if(i > 559) break;
                if(i != 0 && i % 28 == 0) {
                    x = 470;
                    y += 20;
                }
                if(positions[note_to_be_shown]->body[i] == ' ') {
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '.') {
                    //std::cout << "PERIOD!" << std::endl;
                    letters->period->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->period->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == ',') {
                    letters->comma->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->comma->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '/') {
                    letters->slash->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->slash->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '?') {
                    letters->question_mark->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->question_mark->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '\'') {
                    letters->quote->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->quote->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '\"') {
                    letters->double_quotes->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->double_quotes->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == ':') {
                    letters->colon->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->colon->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == ';') {
                    letters->semicolon->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->semicolon->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '!') {
                    letters->exclamation_mark->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->exclamation_mark->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '@') {
                    letters->at->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->at->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '#') {
                    letters->hash->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->hash->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '$') {
                    letters->dollar_sign->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->dollar_sign->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '%') {
                    letters->percentage->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->percentage->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '^') {
                    letters->XOR->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->XOR->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '&') {
                    letters->bit_and->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->bit_and->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '*') {
                    letters->star->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->star->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '(') {
                    letters->left_bracket->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->left_bracket->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == ')') {
                    letters->right_bracket->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->right_bracket->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '-') {
                    letters->minus->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->minus->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '_') {
                    letters->under_score->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->under_score->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '+') {
                    letters->add->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->add->draw();
                    x += 20;
                    continue;
                }
                if(positions[note_to_be_shown]->body[i] == '=') {
                    letters->equal->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->equal->draw();
                    x += 20;
                    continue;
                }
                if(isupper(positions[note_to_be_shown]->body[i])) {
                    int n = (int)positions[note_to_be_shown]->body[i];
                    n -= 65;
                    letters->upper_case_letters[n]->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->upper_case_letters[n]->draw();
                } else if(islower(positions[note_to_be_shown]->body[i])) {
                    int n = (int)positions[note_to_be_shown]->body[i];
                    n -= 97;
                    letters->lower_case_letters[n]->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->lower_case_letters[n]->draw();
                } else {
                    int n = (int)positions[note_to_be_shown]->body[i];
                    n -= 48;
                    letters->numbers[n]->changeRectangle(new Rectangle(RGBA(0, 0, 0, 255), 20, 20, x, y));
                    letters->numbers[n]->draw();
                }
                x += 20;
            }
        }
        //! draw the cursor, if note is in change mode
        if(is_note_changed)
            cursor.draw();
    }
}

//! change header
void Category::change_category_header(const std::string & str) {
    this->category_header = str;
    delete this->text;
    delete this->full_category_header;
    text = new Text(20, str.substr(0, 12), {255, 255, 255, 255});
    full_category_header = new Text(20, str.substr(0, 30), {0, 0, 0, 255});
    full_category_header->changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 650, 28, 390, 108));
}

//! initialize offset_size
void Category::intialize_offset_size() {
    if(notes.empty())
        offset_size = new Text(20, "0/" + std::to_string(notes.size()), {255, 255, 255, 255});
    else offset_size = new Text(20, "1/" + std::to_string(notes.size()), {255, 255, 255, 255});
    offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 250, 550));
}

//! parse time
Time Category::parse_time(const std::string & str) {
    std::istringstream iss(str);
    int day, month, year, hour, minute, seconds;
    char c;
    iss >> day;
    iss >> c;
    iss >> month;
    iss >> c;
    iss >> year;
    iss >> hour;
    iss >> c;
    iss >> minute;
    iss >> c;
    iss >> seconds;
    return Time(Date(day, month, year), Clock(hour, minute, seconds));
}

//! get current time from the system
Time Category::GetCurrentTime() {
    int day, month, year, hour, minute, seconds;
    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);
    day = aTime->tm_mday;
    month = aTime->tm_mon + 1;
    year = aTime->tm_year + 1900;
    hour = aTime->tm_hour;
    minute = aTime->tm_min;
    seconds = aTime->tm_sec;

    Time time(Date(day, month, year), Clock(hour, minute, seconds));
    return time;
}

