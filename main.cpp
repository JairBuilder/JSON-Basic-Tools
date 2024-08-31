#include <cctype>
#include <ios>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



class JSON_VALUE {
public:
  virtual ~JSON_VALUE() {}
  virtual void str() = 0;
  virtual JSON_VALUE& operator=(const int &other) {
    return *this;
  }
  virtual bool operator=(const string &other) {
    return false;
  }
};

class JSON_INT : public JSON_VALUE{
public:
  int value;
  JSON_INT(const int& value) : value(value) {}
  void str() override {
    cout << value << endl;
  }
  JSON_VALUE& operator=(const int& other) override {
    value = other;
    return *this;
  }
};

class JSON_STRING : public JSON_VALUE {
public:
  string value;
  JSON_STRING(const string& value) : value(value) {}
  void str() override {
    cout << value << endl;
  }
  bool operator=(const string& other) override {
    value = other;
    return true;
  }
};

class JSON_LIST : public JSON_VALUE {
public:
  vector<shared_ptr<JSON_VALUE>> value;
  JSON_LIST(const vector<shared_ptr<JSON_VALUE>>& value) : value(value) {}
  JSON_LIST() {}
  void str() override {
    cout << "[";
    for (int i = 0; i < value.size(); i++) {
      value[i]->str();
      if (i != value.size() - 1) {
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
  void add(const int& value) {
    this->value.push_back(make_shared<JSON_INT>(value));
  }
  void add(const string& value) {
    this->value.push_back(make_shared<JSON_STRING>(value));
  }
};

using Key = string;
using Value = std::shared_ptr<JSON_VALUE>;

class JSON {
public:
  JSON() {}
  map<Key, Value> data;
  void add(const Key& key, const int& value) {
    data[key] = make_shared<JSON_INT>(value);
  }
  void add(const Key& key, const string& value) {
    data[key] = make_shared<JSON_STRING>(value);
  }
  void add(const Key& key, const JSON_LIST& value) {
    data[key] = make_shared<JSON_LIST>(value.value);
  }
  
};

int main() {
  JSON json;
  json.add("key1", 10);
  json.data["key1"]->str();
  json.add("key2", "abc");
  json.data["key2"]->str();
  JSON_LIST list;
  list.add(1);
  list.add("gg");
  list.add(3);
  json.add("key3", list); 
  json.data["key3"]->str();
  return 0;
}
