#include "src/JSON.h"
#include <fstream>
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

    JSON favorite_food;
    favorite_food.add("name", "pizza");
    JSON_ARRAY toppings;
    toppings.add("pepperoni");
    toppings.add("mushrooms");
    favorite_food.add("toppings", toppings);
    obj.add("favorite_food", favorite_food);

    JSON favorite_color;
    favorite_color.add("name", "blue");
    JSON_ARRAY rgb;
    rgb.add(0);
    rgb.add(0);
    rgb.add(255);
    favorite_color.add("rgb", rgb);
    obj.add("favorite_color", favorite_color);

    ofstream out_file("./test/generator_result.json", ios::trunc);
    if (out_file.is_open()) {
        out_file << obj.str();
        out_file.close();
        cout << "String written to file successfully." << endl;
        return 0;
    }
    else {
        cout << "Failed to open file." << endl;
    }
    return 0;
}