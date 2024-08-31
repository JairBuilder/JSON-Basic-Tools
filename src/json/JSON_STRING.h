#pragma once
#include "JSON_VALUE.h"

namespace json {
    class JSON_STRING : public JSON_VALUE {
    public:
        JSON_STRING(const std::string& value) : value(value) {}
        std::string str() override {
            return "\"" + value + "\"";
        }
        JSON_VALUE& operator=(const std::string& other) override {
            value = other;
            return *this;
        }
    private:
        std::string value;
    };
}
