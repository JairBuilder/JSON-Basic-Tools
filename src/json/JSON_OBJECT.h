#pragma once
#include <string>
#include <map>
#include "typedef.h"
#include <utility>
#include <vector>

namespace json {    
    class JSON_OBJECT;
    class JSON_ARRAY : public JSON_VALUE {
    public:
        JSON_ARRAY() {}
        JSON_ARRAY(const std::vector<Value>& value) : value(value) {}
        ~JSON_ARRAY() {}
        std::string str() override;
        void add(const int& value);
        void add(const char * value);
        void add(const double& value);
        void add(const bool& value);
        void add(const JSON_ARRAY& value);
        void add(const JSON_OBJECT& value);
        void add(const Value& value);

    private:
        std::vector<Value> value;
    };

    class JSON_OBJECT : public JSON_VALUE {
        public:
            JSON_OBJECT() {};
            JSON_OBJECT(const std::map<Key, Value>& data) : data(data) {}
            ~JSON_OBJECT() {};

            void add(const Key& key, const int& value);
            void add(const Key& key, const char * value);
            void add(const Key& key, const double& value);
            void add(const Key& key, const bool& value);
            void add(const Key& key, const JSON_OBJECT& value);
            void add(const Key& key, const JSON_ARRAY& value);
            void add(const Key& key, const Value& value);
            void add(std::pair<const Key &, const Value &> pair);
            std::string str();
            
        private:
            std::map<Key, Value> data;
    };
}