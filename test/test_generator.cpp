#include "../src/json/JSON_OBJECT.h"
#include <iostream>
using namespace json;
using namespace std;

int main() {
    JSON_OBJECT obj;
    obj.add("name", "John");
    obj.add("age", 30);
    obj.add("is_student", true);
    JSON_ARRAY scores;
    scores.add(100);
    scores.add(90);
    scores.add(80);
    obj.add("scores", scores);
    JSON_OBJECT address;
    address.add("street", "123 Main St");
    address.add("city", "Anytown");
    address.add("state", "CA");
    obj.add("address", address);
    cout << obj.str() << endl;
    return 0;
}