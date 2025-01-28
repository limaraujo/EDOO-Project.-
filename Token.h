#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <variant>
using namespace std;

class Token {
    private:
        string type;
        variant <int, bool, string> value;
    
    public:
        Token(string type, variant<int, bool, string> val) : type(type), value(val) {}


        const string& getType() const { 
            return this->type; 
        }
        const auto& getValue() const { 
            return this->value; 
        }
        
        ~Token() = default;
        
    std::string to_string() const {
        std::string result = "[TOKEN] type-> " + type + " value-> ";

        if (std::holds_alternative<int>(value)) {
            result += std::to_string(std::get<int>(value));
        } else if (std::holds_alternative<bool>(value)) {
            result += std::get<bool>(value) ? "true" : "false";
        } else if (std::holds_alternative<std::string>(value)) {
            result += "\"" + std::get<std::string>(value) + "\"";
        }
        return result;
    }

};

#endif