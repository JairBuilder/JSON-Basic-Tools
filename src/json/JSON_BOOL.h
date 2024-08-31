#pragma once
#include "JSON_VALUE.h"

namespace json {
    class JSON_BOOL : public JSON_VALUE {
    public:
        
        JSON_BOOL(const bool& value) : value(value) {}
        std::string str() override {
            return value ? "true" : "false";
        }
        JSON_VALUE& operator=(const bool& other) override {
            value = other;
            return *this;
        }
    private:
        bool value;
    };
}
