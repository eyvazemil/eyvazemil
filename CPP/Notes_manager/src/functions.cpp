#include "functions.h"

//! poll events for mouse or keyboard input
void pollEvents(Window & window, CNoteList & database) {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        window.pollEvents(event);
        if(window.is_closed()) return;
        database.pollEvents(event);
        if(database.is_category_shown)
            database.positions[database.category_to_be_shown]->pollEvents(event);
    }
}

//! list files in particular directory
//! listFiles function is taken from:
//! http://forum.codecall.net/topic/60157-read-all-files-in-a-folder/
std::vector<std::string> listFiles(std::string path) {
    DIR * dir;
    dirent * pdir;
    std::vector<std::string> files;

    dir = opendir(path.c_str());
    while(pdir = readdir(dir))
        files.push_back(pdir->d_name);

    return files;
}

//! read .txt file
std::vector<char> read_file(const std::string & filename) {
    std::ifstream myReadFile;
    myReadFile >> std::noskipws;
    myReadFile.open(filename);
    std::vector<char> vec;
    char c;
    if(myReadFile.is_open()) {
        while(myReadFile >> c)
            vec.push_back(c);
    }
    myReadFile.close();

    return vec;
}

//! parse the note
void write_notes(const std::string & filename, const std::string & note) {
    std::ofstream file;
    file.open(filename);
    file << note;
    file.close();
}

//! read all notes and write them into our database
void read_note(CNoteList & database, const std::vector<char> & file) {
    int counter = 0;
    Time time;
    std::string header, category, time_string, body;

    //! read time
    while(file[counter] != '\n') {
        time_string += file[counter];
        counter++;
    }
    counter++;

    time = parse_time(time_string);

    //! read category
    while(file[counter] != '\n') {
        category += file[counter];
        counter++;
    }
    counter++;

    //! read the body of the note
    while(counter < file.size()) {
        body += file[counter];
        counter++;
    }

    std::string str_time = time.time_to_string();
    CNote * note = new CNote(str_time, body);
    note->AddBody(body);
    database.AddNote(note, time, category);
}

//! write into the file
void preprocessData(CNoteList & database) {
    std::string str;
    std::vector<std::string> files = listFiles();
    std::vector<std::string> md_files = listFiles("./examples");
    for(const auto & it : files) {
        if(it == "." || it == "..") continue;
        str = "./src/Notes/" + it;
        std::vector<char> file = read_file(str);
        read_note(database, file);
        remove(str.c_str());
    }
    for(const auto & it : md_files) {
        if(it == "." || it == "..") continue;
        str = "./examples/" + it;
        remove(str.c_str());
    }
}

//! parse time
Time parse_time(const std::string & str) {
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
