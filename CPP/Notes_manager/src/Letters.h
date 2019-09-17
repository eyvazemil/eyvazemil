#ifndef PA2_PROJECT_LETTERS_H
#define PA2_PROJECT_LETTERS_H

#include <vector>
#include <string>
#include "Text.h"

class Letters {
public:
    //! uppercase letters
    std::vector<Text *> upper_case_letters;
    //! lowercase letters
    std::vector<Text *> lower_case_letters;
    //! numbers
    std::vector<Text *> numbers;
    //! signs
    Text * period, * comma, * colon, * semicolon, * slash, * question_mark, * exclamation_mark;
    Text * quote, * double_quotes, * at, * hash, * dollar_sign, * percentage, * XOR, * bit_and, * star;
    Text * under_score, * minus, * add, * equal;
    Text * left_bracket, * right_bracket;
public:
    //! constructor
    Letters();
    //! destructor
    ~Letters();
};

#endif //PA2_PROJECT_LETTERS_H
