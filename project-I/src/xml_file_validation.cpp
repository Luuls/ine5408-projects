#include <iostream>
#include <string>
#include <vector>

#include "array_stack.h"

std::vector<std::string> validadeFile(std::string file) {

    std::vector<std::string> tags_vector;
    std::string tag;

    for (int i = 0; i < file.size(); i++) {
        if (file[i] == '<') {
            for (int j = i + 1; j < file.size(); j++) {
                if (file[j] == '>') {
                    tags_vector.push_back(tag);
                    tag = "";
                    break;
                }
                tag += file[j];
            }
        }
    }
    return tags_vector;
}

int main() {
    std::string s = "<tag_test> abab , oba <tag_test/>";

    std::vector<std::string> answer = validadeFile(s);

    for (auto e : answer) {
        std::cout << e << std::endl;
    }

    return 0;
}
