#pragma once
#include "JSON_VALUE.h"

namespace json {
    class JSON_DOUBLE : public JSON_VALUE {
    public:
        double value;
        JSON_DOUBLE(const double& value) : value(value) {}
        std::string str() override {
            return std::to_string(value);
        }
        JSON_VALUE& operator=(const double& other) override {
            value = other;
            return *this;
        }
    };
}
