#pragma once
#include <string>

namespace json {
    class JSON_VALUE {
    public:
        virtual ~JSON_VALUE() {}
        virtual std::string str() = 0;
        virtual JSON_VALUE& operator=(const int &other) {
            return *this;
        }
        virtual JSON_VALUE& operator=(const std::string &other) {
            return *this;
        }
        virtual JSON_VALUE& operator=(const bool &other) {
            return *this;
        }
        virtual JSON_VALUE& operator=(const double &other) {
            return *this;
        }
    };
}