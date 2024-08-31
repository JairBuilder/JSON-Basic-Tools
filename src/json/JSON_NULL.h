#pragma once
#include "JSON_VALUE.h"

namespace json {
    class JSON_NULL : public JSON_VALUE {
    public:
        JSON_NULL() {}
        std::string str() override {
            return "null";
        }
    };
}
