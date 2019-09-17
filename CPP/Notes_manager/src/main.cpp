#include "functions.h"

//! initialize static member of Window class
SDL_Renderer * Window::sdl_renderer = nullptr;

//! main
int main(int argc, char * argv[]) {

    //! create a window
    Window window("Notes manager", 1066, 600);

    //! create a database
    CNoteList database;
    //! fill the database with already existing notes
    preprocessData(database);
    //! initialize the offset of the database
    database.intialize_offset_size();

    //! draw to the screen
    //! until the window is not closed
    while(!window.is_closed()) {
        window.clear(RGBA(191, 179, 255, 255));
        //! poll events
        pollEvents(window, database);
        //! draw the database
        database.draw();
        //! show to the screen
        window.present();
    }

    //! write all the notes in the files
    unsigned long file_counter = 1;
    std::string file_name, file_name_md;
    for(auto & it : database.categories) {
        for(auto & ti : it.second->notes) {
            //! s1 is a string for .txt file
            //! s2 is a string for .md file
            std::string s1, s2, t = ti.first.time_to_string();
            file_name = "./src/Notes/Note_" + std::to_string(file_counter) + ".txt";
            file_name_md = "./examples/Note_" + std::to_string(file_counter) + ".md";
            s1 = t;
            s1 += "\n";
            s2 += "# _" + it.second->get_category_header() + "_\n";
            s1 += it.second->get_category_header();
            s1 += "\n";
            s2 += "---\n";
            s2 += "##### _";
            s2 += t;
            s2 += "_";
            s2 += "\n";
            s2 += "---";
            s2 += "\n";
            s1 += ti.second->body;
            for(auto & c : ti.second->body) {
                if(c == '#' || c == '*' || c == '_')
                    s2 += "\\";
                s2 += c;
            }
            write_notes(file_name, s1);
            write_notes(file_name_md, s2);
            file_counter++;
        }
    }

    return 0;
}
