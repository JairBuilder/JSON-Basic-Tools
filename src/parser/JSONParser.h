#pragma once

#include "../json/JSON_OBJECT.h"
#include "../json/JSON_STRING.h"
#include "../json/JSON_BOOL.h"
#include "../json/JSON_NULL.h"
#include "../json/JSON_INT.h"
#include "../json/JSON_DOUBLE.h"
#include "../json/typedef.h"
#include <unordered_set>
#include <memory>
#include <string>
#include <stdexcept>
namespace json {
    class JSONParser {
    public:
        JSONParser() {}
        ~JSONParser() {}

        JSON_OBJECT parse(const std::string& json);

    private:
        int idx = 0;
        std::string json;

        std::unordered_set<char> blank_chars  = { ' ', '\n', '\r', '\t' };
        std::unordered_set<char> number_chars = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '+', 'e', 'E', '.' };
        std::unordered_set<char> word_chars   = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_' };

    private:
        std::pair<Key, Value> next_pair();    // get next pair and move idx to it's end char, before the ','
        std::string next_string();            // get next string and move idx to it's end mark
        std::string next_number();            // get next number and move idx to it's end char
        std::string next_word();              // get next word and move idx to it's end char
        char next_char();                     // get next char and move idx to it
        void skip_blank();                    // move idx to next vilid char

        std::shared_ptr<JSON_VALUE> parse_value();
        std::shared_ptr<JSON_VALUE> parse_number();
        std::shared_ptr<JSON_VALUE> parse_string();
        std::shared_ptr<JSON_VALUE> parse_array();
        std::shared_ptr<JSON_VALUE> parse_object();
        std::shared_ptr<JSON_VALUE> parse_int();
        std::shared_ptr<JSON_VALUE> parse_double();
        std::shared_ptr<JSON_VALUE> parse_bool();
        std::shared_ptr<JSON_VALUE> parse_null();
    };
}
