#pragma once

#include "JSON_VALUE.h"
#include "JSON_INT.h"
#include "JSON_STRING.h"
#include "JSON_DOUBLE.h"
#include "JSON_BOOL.h"
#include "JSON_OBJECT.h"
#include <vector>
#include <memory>
#include "typedef.h"

namespace json {
    class JSON_ARRAY : public JSON_VALUE {
    public:
        JSON_ARRAY(const std::vector<Value>& value) : value(value) {}
        ~JSON_ARRAY() {}
        std::string str() override {
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
        void add(const int& value) {
            this->value.push_back(std::make_shared<JSON_INT>(value));
        }
        void add(const std::string& value) {
            this->value.push_back(std::make_shared<JSON_STRING>(value));
        }
        void add(const double& value) {
            this->value.push_back(std::make_shared<JSON_DOUBLE>(value));
        }
        void add(const bool& value) {
            this->value.push_back(std::make_shared<JSON_BOOL>(value));
        }
        void add(const JSON_ARRAY& value) {
            this->value.push_back(std::make_shared<JSON_ARRAY>(value));
        }
        void add(const JSON_OBJECT& value) {
            this->value.push_back(std::make_shared<JSON_OBJECT>(value));
        }

    private:
        std::vector<Value> value;
    };
}
