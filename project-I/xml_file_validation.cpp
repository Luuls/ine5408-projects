#include <iostream>
#include <string>

class XmlValidation {
public:
    void getTagWords(std::string file) {

        char current_character = 'a';
        std::string current_word;
        int i = 0;

        while (current_character != ' ') {
            current_character = file[i];
            current_word += current_character;
        }
    }
private:
    std::string current_word;
};
