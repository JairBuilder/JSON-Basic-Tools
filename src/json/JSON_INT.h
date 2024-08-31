#pragma once
#include "JSON_VALUE.h"

namespace json {
    class JSON_INT : public JSON_VALUE {
    public:
        int value;
        JSON_INT(const int& value) : value(value) {}
        std::string str() override {
            return std::to_string(value);
        }
        JSON_VALUE& operator=(const int& other) override {
            value = other;
            return *this;
        }
    };
}
