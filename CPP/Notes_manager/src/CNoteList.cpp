#include "CNoteList.h"

//! constructor
CNoteList::CNoteList() : category(RGBA(102, 230, 255, 255), 200, 30, 10, 105),
                         rect(RGBA(102, 230, 255, 255), 200, 450, 10, 140),
                         sign_up_medium(), sign_down_medium(), sign_up(),
                         sign_down(), Add_medium(), Add(),
                         Delete(), Delete_strong(), offset_size(nullptr), temporary_category(nullptr),
                         text(28, "Category", {255, 255, 255, 255}),
                         AddError(20, "Message: \"New Category \" already presents. Change the header of it to Add any new category", {255, 255, 255, 255}),
                         CategoryError(20, "Such category already exists or it is empty", {255, 255, 255, 255})
{
    //! load all needed textures and texts
    sign_up_medium.loadTexture("./src/Resources/Images/triangle_up_medium.png");
    sign_down_medium.loadTexture("./src/Resources/Images/triangle_down_medium.png");
    sign_up.loadTexture("./src/Resources/Images/triangle_up.png");
    sign_down.loadTexture("./src/Resources/Images/triangle_down.png");
    Add_medium.loadTexture("./src/Resources/Images/Add_medium.png");
    Add.loadTexture("./src/Resources/Images/Add.png");
    Delete.loadTexture("./src/Resources/Images/Delete.png");
    Delete_strong.loadTexture("./src/Resources/Images/Delete_strong.png");
    text.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 150, 30, 40, 105));
    AddError.changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 913, 22, 10, 20));
    CategoryError.changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 413, 22, 10, 43));
    sign_up.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 170, 540));
    sign_up_medium.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 170, 540));
    sign_down.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 170, 570));
    sign_down_medium.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 20, 20, 170, 570));
    Add.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 30, 30, 20, 550));
    Add_medium.changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 30, 30, 20, 550));
    add_error = false;
    category_error = false;
    error_counter = 0;
    error_category_counter = 0;
    is_category_shown = false;
    is_category_changed = false;
    offset = 1;
}

//! destructor
CNoteList::~CNoteList() {
    delete offset_size;
    delete temporary_category;
    for(auto & it : categories)
        delete it.second;
}

//! add category
void CNoteList::AddCategory(const std::string & str) {
    auto it = SearchCategory(str);
    if(it == categories.end()) {
        Category * cat = new Category(str);
        cat->letters = &this->letters;
        categories.insert(std::pair<std::string, Category *>(str, cat));
        //! set categories positions on the screen
        int count = 0;
        for(auto & ti : categories) {
            int y_pos = 141 + 32 * (count % 12);
            (ti.second->text)->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 198, 30, 11, y_pos));
            count++;
        }
        //! set pointers to the categories
        positions.clear();
        for(auto & ti : categories)
            positions.push_back(ti.second);
        //! set offset
        delete offset_size;
        std::string off = std::to_string(offset);
        offset_size = new Text(20, off + "/" + std::to_string(categories.size()), {255, 255, 255, 255});
        offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 70, 550));
    }
}

//! add a note
void CNoteList::AddNote(CNote * note, const Time & t, const std::string & str) {
    auto it = SearchCategory(str);
    if(it != categories.end())
        it->second->AddNote(t, note);
    else {
        AddCategory(str);
        it = SearchCategory(str);
        it->second->AddNote(t, note);
    }
}

//! draw to the screen
void CNoteList::draw() {
    //! draw initial rectangles and textures
    category.draw();
    text.draw();
    rect.draw();
    if(rect.mouse_points()) {
        if(sign_up.mouse_points())
            sign_up.draw();
        else sign_up_medium.draw();
        if(sign_down.mouse_points())
            sign_down.draw();
        else sign_down_medium.draw();
        if(Add.mouse_points())
            Add.draw();
        else Add_medium.draw();
        offset_size->draw();
    }

    //! draw categories
    {
        int count = offset;
        for(int i = offset - 1; i < positions.size(); i++) {
            positions[i]->text->rect->draw();
            positions[i]->text->draw();
            if(count % 12 == 0) break;
            count++;
        }
    }

    //! draw category body
    if(is_category_shown) {
        positions[category_to_be_shown]->draw();
        if(is_category_changed && temporary_category != nullptr) {
            Rectangle HEADER_RECT_category(RGBA(255, 255, 255, 255), 650, 28, 380, 106);
            HEADER_RECT_category.draw();
            temporary_category->draw();
        }
    }

    //! error messages
    if(add_error) {
        AddError.rect->draw();
        AddError.draw();
        if(error_counter == 2000) {
            error_counter = 0;
            add_error = false;
        }
        error_counter++;
    }

    if(category_error) {
        CategoryError.rect->draw();
        CategoryError.draw();
        if(error_category_counter == 2000) {
            error_category_counter = 0;
            category_error = false;
        }
        error_category_counter++;
    }
}

//! poll events
void CNoteList::pollEvents(SDL_Event & event) {
    //! if keyboard was clicked
    if(event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
        if(is_category_changed) {
            if(event.key.keysym.sym == SDLK_BACKSPACE) {
                //! if backspace was clicked
                tmp_category_header = tmp_category_header.substr(0, tmp_category_header.size() - 1);
                delete temporary_category;
                temporary_category = new Text(20, tmp_category_header.substr(0, 30), {0, 0, 0, 255});
                temporary_category->changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 650, 28, 390, 108));
            } else {
                //! if anything else than backspace was clicked
                bool flag = false;
                std::string str = event.text.text;
                for(auto & it : str) {
                    if(!isalnum(it) && it != '_') {
                        flag = true;
                        break;
                    }
                }
                //! temporary category name changed
                if(!flag && tmp_category_header.size() < 30) {
                    tmp_category_header += str;
                    delete temporary_category;
                    temporary_category = new Text(20, tmp_category_header.substr(0, 30), {0, 0, 0, 255});
                    temporary_category->changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 650, 28, 390, 108));
                }
            }
        }
    }
    //! if mouse was clicked
    else if(event.type == SDL_MOUSEBUTTONUP) {
        //! if category was changed and after that mouse was clicked
        //! decide if it is needed to change category header to the new one
        //! or leave as it was
        if(is_category_changed) {
            //! if the new header is equal to the old one, don't change anything
            if(tmp_category_header != positions[category_to_be_shown]->get_category_header()) {
                auto it = categories.find(tmp_category_header);
                auto i = categories.find(positions[category_to_be_shown]->get_category_header());
                //! error, such category header already exists
                if(tmp_category_header.empty() || it != categories.end()) {
                    category_error = true;
                } else {
                    //! change category header
                    Category * tmp = positions[category_to_be_shown];
                    tmp->letters = &this->letters;
                    tmp->change_category_header(tmp_category_header);
                    categories.erase(i);
                    categories.insert(std::pair<std::string, Category *>(tmp_category_header, tmp));
                    //! renew positions of categories on the screen
                    int count = 0;
                    for(auto & ti : categories) {
                        int y_pos = 141 + 32 * (count % 12);
                        (ti.second->text)->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 198, 30, 11, y_pos));
                        count++;
                    }
                    //! renew pointers to the categories
                    positions.clear();
                    for(auto & ti : categories)
                        positions.push_back(ti.second);
                    //! find and show the changed category
                    {
                        int count1 = 0;
                        for(auto & it1 : categories) {
                            if(it1.first == tmp_category_header) {
                                category_to_be_shown = count1;
                                break;
                            }
                            count1++;
                        }
                    }
                }
            }
            SDL_StopTextInput();
        }
        delete temporary_category;
        temporary_category = nullptr;
        is_category_changed = false;
        //! sign up is clicked
        //! then decrement the offset
        if(sign_up.mouse_points()) {
            if(offset > 12) {
                offset -= 12;
                delete offset_size;
                std::string off = std::to_string(offset);
                if(categories.empty())
                    offset_size = new Text(20, "0/" + std::to_string(categories.size()), {255, 255, 255, 255});
                else offset_size = new Text(20, off + "/" + std::to_string(categories.size()), {255, 255, 255, 255});
                offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 70, 550));
            }
        }
        //! sign down is clicked
        //! then increment the offset
        else if(sign_down.mouse_points()) {
            if(offset + 12 <= categories.size()) {
                offset += 12;
                delete offset_size;
                std::string off = std::to_string(offset);
                if(categories.empty())
                    offset_size = new Text(20, "0/" + std::to_string(categories.size()), {255, 255, 255, 255});
                else offset_size = new Text(20, off + "/" + std::to_string(categories.size()), {255, 255, 255, 255});
                offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 70, 550));
            }
        }
        //! add new category
        else if(Add.mouse_points()) {
            if(categories.empty())
                AddCategory("NewCategory");
            else {
                auto it = categories.find("NewCategory");
                if(it != categories.end()) {
                    //! can't add category because of the NewCategory category
                    add_error = true;
                } else AddCategory("NewCategory");
            }
        }

        {
            int count = offset;
            for(int i = offset - 1; i < positions.size(); i++) {
                //! if mouse was clicked on particular category
                //! that category is going to be shown
                if(positions[i]->text->rect->mouse_points()) {
                    is_category_shown = true;
                    category_to_be_shown = i;
                    positions[i]->intialize_offset_size();
                    tmp_category_header = positions[category_to_be_shown]->get_category_header();
                    break;
                } else {
                    //! if mouse was clicked inside of the body of shown category
                    if(is_category_shown && (positions[category_to_be_shown]->HEADER_category.mouse_points() ||
                       positions[category_to_be_shown]->BODY_category.mouse_points() ||
                       (!positions[category_to_be_shown]->notes.empty() && positions[category_to_be_shown]->is_note_shown &&
                        positions[category_to_be_shown]->notes.begin()->second->NOTE_BODY.mouse_points())))
                    {
                        is_category_shown = true;
                    } else {
                        is_category_shown = false;
                    }
                }
                if(count % 12 == 0) break;
                count++;
            }
        }

        //! delete category or change its header
        {
            if(is_category_shown) {
                // change header of the category
                if(!is_category_changed && positions[category_to_be_shown]->HEADER_RECT_category.mouse_points()) {
                    is_category_changed = true;
                    tmp_category_header = positions[category_to_be_shown]->get_category_header();
                    delete temporary_category;
                    temporary_category = new Text(20, tmp_category_header.substr(0, 30), {0, 0, 0, 255});
                    temporary_category->changeRectangle(new Rectangle(RGBA(0, 0, 0, 0), 650, 28, 390, 108));
                    SDL_StartTextInput();
                }
                //! delete category
                else if(positions[category_to_be_shown]->Delete_category.mouse_points()) {
                    DeleteCategory(positions[category_to_be_shown]->get_category_header());
                    is_category_shown = false;
                }
            }
        }
    }
}

//! delete category
void CNoteList::DeleteCategory(const std::string & str) {
    auto it = SearchCategory(str);
    if(it != categories.end()) {
        delete it->second;
        categories.erase(it);
        //! renew positions of categories on the screen
        int count = 0;
        for(auto & i : categories) {
            int y_pos = 141 + 32 * (count % 12);
            (i.second->text)->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 198, 30, 11, y_pos));
            count++;
        }
        //! renew pointers to categories
        positions.clear();
        for(auto & ti : categories)
            positions.push_back(ti.second);
        //! renew offset after deletion
        if(offset > categories.size() && offset > 12)
            offset -= 12;
        delete offset_size;
        std::string off = std::to_string(offset);
        if(categories.empty())
            offset_size = new Text(20, "0/" + std::to_string(categories.size()), {255, 255, 255, 255});
        else offset_size = new Text(20, off + "/" + std::to_string(categories.size()), {255, 255, 255, 255});
        offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 70, 550));
    }
}

//! search for the category with given header
std::map<std::string, Category *>::iterator CNoteList::SearchCategory(const std::string & str) {
    std::map<std::string, Category *>::iterator it;
    for(it = categories.begin(); it != categories.end(); it++) {
        if(it->second->get_category_header() == str)
            break;
    }
    return it;
}

//! initialize offset_size
void CNoteList::intialize_offset_size() {
    if(categories.empty())
        offset_size = new Text(20, "0/" + std::to_string(categories.size()), {255, 255, 255, 255});
    else offset_size = new Text(20, "1/" + std::to_string(categories.size()), {255, 255, 255, 255});
    offset_size->changeRectangle(new Rectangle(RGBA(102, 230, 255, 255), 30, 30, 70, 550));
}

