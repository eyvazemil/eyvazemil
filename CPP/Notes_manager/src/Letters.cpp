#include "Letters.h"

//! constructor
Letters::Letters() {
    char c;
    //! if character is in uppercase
    for(int i = 65; i <= 90; i++) {
        c = (char)i;
        std::string s;
        s += c;
        upper_case_letters.push_back(new Text(20, s, {0, 0, 0, 255}));
    }
    //! if character is in lowercase
    for(int i = 97; i <= 122; i++) {
        c = (char)i;
        std::string s;
        s += c;
        lower_case_letters.push_back(new Text(20, s, {0, 0, 0, 255}));
    }
    //! if character is a number
    for(int i = 48; i <= 57; i++) {
        c = (char)i;
        std::string s;
        s += c;
        numbers.push_back(new Text(20, s, {0, 0, 0, 255}));
    }
    //! if character is a sign
    period = new Text(20, ".", {0, 0, 0, 255});
    comma = new Text(20, ",", {0, 0, 0, 255});
    colon = new Text(20, ":", {0, 0, 0, 255});
    semicolon = new Text(20, ";", {0, 0, 0, 255});
    slash = new Text(20, "/", {0, 0, 0, 255});
    question_mark = new Text(20, "?", {0, 0, 0, 255});
    exclamation_mark = new Text(20, "!", {0, 0, 0, 255});
    quote = new Text(20, "\'", {0, 0, 0, 255});
    double_quotes = new Text(20, "\"", {0, 0, 0, 255});
    at = new Text(20, "@", {0, 0, 0, 255});
    hash = new Text(20, "#", {0, 0, 0, 255});
    dollar_sign = new Text(20, "$", {0, 0, 0, 255});
    percentage = new Text(20, "%", {0, 0, 0, 255});
    XOR = new Text(20, "^", {0, 0, 0, 255});
    bit_and = new Text(20, "&", {0, 0, 0, 255});
    star = new Text(20, "*", {0, 0, 0, 255});
    under_score = new Text(20, "_", {0, 0, 0, 255});
    minus = new Text(20, "-", {0, 0, 0, 255});
    add = new Text(20, "+", {0, 0, 0, 255});
    equal = new Text(20, "=", {0, 0, 0, 255});
    left_bracket = new Text(20, "(", {0, 0, 0, 255});
    right_bracket = new Text(20, ")", {0, 0, 0, 255});
}

//! destructor
Letters::~Letters() {
    for(auto & it : upper_case_letters)
        delete it;
    for(auto & it : lower_case_letters)
        delete it;
    for(auto & it : numbers)
        delete it;
    delete period;
    delete comma;
    delete colon;
    delete semicolon;
    delete slash;
    delete question_mark;
    delete exclamation_mark;
    delete quote;
    delete double_quotes;
    delete at;
    delete hash;
    delete dollar_sign;
    delete percentage;
    delete XOR;
    delete bit_and;
    delete star;
    delete under_score;
    delete minus;
    delete add;
    delete equal;
    delete left_bracket;
    delete right_bracket;
}