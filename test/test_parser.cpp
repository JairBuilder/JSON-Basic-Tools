#include "src/JSON.h"
#include "src/parser/JSONParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace json;
using namespace std;

int main() {
    
    JSON json;
    ifstream in_file("./test/parse_source.json");
    if (in_file.is_open()) {
        stringstream buffer;
        buffer << in_file.rdbuf();
        string json_str = buffer.str();
        JSONParser json_parser;
        json = json_parser.parse(json_str);
    }
    else {
        cout << "Failed to open file." << endl;
        return -1;
    }

    ofstream out_file("./test/parse_result.json");
    if (out_file.is_open()) {
        out_file << json.str();
        out_file.close();
        cout << "String written to file successfully." << endl;
        return 0;
    }
    else {
        cout << "Failed to open file." << endl;
    }
    return 0;
}