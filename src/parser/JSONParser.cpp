#include "JSONParser.h"

using namespace json;

JSON_OBJECT JSONParser::parse(const std::string& json) {
    this->json = json;
    JSON_OBJECT JSON;
    while (idx < json.size()) {
        std::pair<Key, Value> pair = next_pair();
        if (pair.first == "") break;
        JSON.add(pair);
    }
    return JSON;
}

void JSONParser::skip_blank() {
    idx++;
    while (idx < json.size() && blank_chars.count(json[idx])!=0) {
        idx++;
    }
}

std::pair<Key, Value> JSONParser::next_pair() {
    if (next_char() == '}') return std::make_pair("", nullptr);
    Key key = next_string();
    next_char();
    Value value = parse_value();
    return std::make_pair(key, value);
}

char JSONParser::next_char() {
    skip_blank();
    if (idx >= json.size()) {
        throw std::runtime_error("JSONParser: next_char: idx out of range");
    }
    return json[idx];
}

std::string JSONParser::next_string() {
    if (idx >= json.size()) {
        throw std::runtime_error("JSONParser: next_string: idx out of range");
    }
    while (idx < json.size() && json[idx] != '\"') {
        idx++;
    }
    if (idx >= json.size()) throw std::runtime_error("JSONParser: next_string: can't find next string");
    idx++;//move to string start
    std::string str;
    while (idx < json.size() && json[idx] != '\"') {
        str += json[idx];
        idx++;
    }
    if (idx >= json.size()) throw std::runtime_error("JSONParser: next_string: missing end mark");
    return str;
}

std::string JSONParser::next_word() {
    skip_blank(); //move to first char
    if (idx >= json.size()) {
        throw std::runtime_error("JSONParser: next_word: idx out of range");
    }
    if (word_chars.count(json[idx]) == 0) {
        throw std::runtime_error("JSONParser: next_word: not a word");
    }
    std::string str;
    while (idx < json.size() && word_chars.count(json[idx]) != 0) {
        str += json[idx];
        idx++;
    }
    idx--;
    return str;
}

std::string JSONParser::next_number() {
    skip_blank(); //move to first char
    if (idx >= json.size()) {
        throw std::runtime_error("JSONParser: next_number: idx out of range");
    }
    if (number_chars.find(json[idx]) == number_chars.end()) {
        std::cout<<"error char: "<<json[idx]<<std::endl;
        throw std::runtime_error("JSONParser: next_number: not a number");
    }
    std::string str;
    while (idx < json.size() && number_chars.count(json[idx]) != 0) {
        str += json[idx];
        idx++;
    }
    if (idx >= json.size()) throw std::runtime_error("JSONParser: next_number: end by number but end mark");
    idx--;
    return str;
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_value() {
    if (idx >= json.size()) {
        throw std::runtime_error("JSONParser: parse_value: idx out of range");
    }
    //获取value的首字符，并保持idx在':'上
    size_t pre = idx;
    char c = next_char();
    idx = pre;
    //分情况处理
    if (number_chars.count(c)!=0) return parse_number();
    else if (c == '\"') return parse_string();
    else if (c == '[') return parse_array();
    else if (c == '{') return parse_object();
    else {
        std::string s = next_word();
        idx = pre;
        if (s == "true" || s == "false") return parse_bool();
        else if (s == "null") return parse_null();
        else throw std::runtime_error("JSONParser: parse_value: not a vilid word");
    }
    throw std::runtime_error("JSONParser: parse_value: not a vilid mark");
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_number() {
    size_t pre = idx;
    std::string number = next_number();
    idx = pre;
    unsigned int pos_cnt = 0;
    for (auto c : number) {
        if (c == '.') pos_cnt++;
    }
    if (pos_cnt == 0) return parse_int();
    else if (pos_cnt == 1) return parse_double();
    else throw std::runtime_error("JSONParser: parse_number: not a number");
    // test: 123. , .123
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_int() {
    std::string number = next_number();
    return std::shared_ptr<JSON_INT>(new JSON_INT(std::stoi(number)));
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_double() {
    std::string number = next_number();
    return std::shared_ptr<JSON_DOUBLE>(new JSON_DOUBLE(std::stod(number)));
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_bool() {
    std::string word = next_word();
    if (word == "true") {
        return std::shared_ptr<JSON_BOOL>(new JSON_BOOL(true));
    }
    if (word == "false") {
        return std::shared_ptr<JSON_BOOL>(new JSON_BOOL(false));
    }
    throw std::runtime_error("JSONParser: parse_bool: not a bool"); //never work
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_null() {
    std::string word = next_word();
    if (word == "null") {
        return std::shared_ptr<JSON_NULL>(new JSON_NULL());
    }
    throw std::runtime_error("JSONParser: parse_null: not a null"); //never work
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_string() {
    std::string str = next_string();
    return std::shared_ptr<JSON_STRING>(new JSON_STRING(str));
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_array() {
    JSON_ARRAY array;
    char c = next_char(); //move to '['
    while (c != ']') {
        array.add(parse_value());
        c = next_char();
        if (c != ',' && c != ']') {
            throw std::runtime_error("JSONParser: parse_array: not a array");
        }
    }
    return std::shared_ptr<JSON_ARRAY>(new JSON_ARRAY(array));
}

std::shared_ptr<JSON_VALUE> JSONParser::parse_object() {
    JSON_OBJECT object;
    char c = next_char(); //move to '{'
    while (c != '}') {
        object.add(next_pair());
        c = next_char();
        if (c != ',' && c != '}') {
            throw std::runtime_error("JSONParser: parse_object: not a object");
        }
    }
    return std::shared_ptr<JSON_OBJECT>(new JSON_OBJECT(object));
}
