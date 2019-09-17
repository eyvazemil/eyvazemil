#ifndef PA2_PROJECT_FUNCTIONS_H
#define PA2_PROJECT_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <memory>
#include <functional>
#include <sstream>
#include <fstream>
#include <climits>
#include <dirent.h>
#include "Letters.h"
#include "CNoteList.h"
#include "Category.h"
#include "Window.h"
#include "Rectangle.h"
#include "Texture.h"
#include "Text.h"

class CNoteList;

//! poll events for mouse or keyboard input
void pollEvents(Window &, CNoteList &);
//! list files in particular directory
std::vector<std::string> listFiles(std::string path = "./src/Notes");
//! read .txt file
std::vector<char> read_file(const std::string &);
//! parse the note
void read_note(CNoteList &, const std::vector<char> &);
//! read all notes and write them into our database
void preprocessData(CNoteList &);
//! write into the file
void write_notes(const std::string &, const std::string &);
//! parse time
Time parse_time(const std::string &);

#endif //PA2_PROJECT_FUNCTIONS_H
