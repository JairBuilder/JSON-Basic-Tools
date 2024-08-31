#include "JSON_OBJECT.h"
#include "JSON_INT.h"
#include "JSON_STRING.h"
#include "JSON_DOUBLE.h"
#include "JSON_BOOL.h"

using namespace json;

void JSON_OBJECT::add(const Key& key, const std::string& value) {
    data[key] = std::make_shared<JSON_STRING>(value);
}
void JSON_OBJECT::add(const Key& key, const int& value) {
    data[key] = std::make_shared<JSON_INT>(value);
}

void JSON_OBJECT::add(const Key& key, const double& value) {
    data[key] = std::make_shared<JSON_DOUBLE>(value);
}

void JSON_OBJECT::add(const Key& key, const bool& value) {
    data[key] = std::make_shared<JSON_BOOL>(value);
}

void JSON_OBJECT::add(const Key& key, const JSON_OBJECT& value) {
    data[key] = std::make_shared<JSON_OBJECT>(value);
}

void JSON_OBJECT::add(const Key& key, const JSON_ARRAY& value) {
    data[key] = std::make_shared<JSON_ARRAY>(value);
}

void JSON_ARRAY::add(const int& value) {
    this->value.push_back(std::make_shared<JSON_INT>(value));
}

void JSON_ARRAY::add(const std::string& value) {
    this->value.push_back(std::make_shared<JSON_STRING>(value));
}

void JSON_ARRAY::add(const double& value) {
    this->value.push_back(std::make_shared<JSON_DOUBLE>(value));
}

void JSON_ARRAY::add(const bool& value) {
    this->value.push_back(std::make_shared<JSON_BOOL>(value));
}

void JSON_ARRAY::add(const JSON_ARRAY& value) {
    this->value.push_back(std::make_shared<JSON_ARRAY>(value));
}

void JSON_ARRAY::add(const JSON_OBJECT& value) {
    this->value.push_back(std::make_shared<JSON_OBJECT>(value));
}

std::string JSON_ARRAY::str() {
    std::string result = "[";
    for (int i = 0; i < value.size(); i++) {
        result += value[i]->str();
        if (i != value.size() - 1) {
            result += ",";
        }
    }
    result += "]";
    return result;
}

std::string JSON_OBJECT::str() {
    std::string result = "{";
    for (auto it = data.begin(); it != data.end(); ++it) {
        result += "\"" + it->first + "\":" + it->second->str();
        if (++it != data.end()) {
            result += ",";
        }
        --it;
    }
    result += "}";
    return result;
}
