#include <fstream>
#include <iterator>

#include "../include/xml_parser.h"


XmlTree XmlParser::parse(const std::string& xmlPath) {
    std::ifstream xmlFile(xmlPath);
    std::istream_iterator<char> iterFile(xmlFile), endFile;
    std::string xmlContent(iterFile, endFile);
    std::string::iterator iter = xmlContent.begin();
    std::string::iterator end = xmlContent.end();

    // struct local para armazenar o contexto de cada tag
    struct Context {
        XmlTree node;
        std::string::iterator contentBegin;
    };

    XmlTree root;
    ArrayStack<Context> stack;

    // lê caractere por caractere
    while (iter != end) {
        if (*iter == '<') {
            // caso seja uma tag de fechamento
            if (*(++iter) == '/') {
                // o fim do conteúdo da tag que está fechando é em '<'
                std::string::iterator contentEnd = iter - 1;
                iter++;

                std::string identifier = readIdentifier(iter);
                // se for uma tag de fechamento e a pilha estiver vazia
                // ou o identificador da tag de fechamento não condiz com
                // a tag no topo da pilha, significa que o arquivo xml está
                // mal formado
                if (stack.empty() || identifier != stack.top().node.getIdentifier()) {
                    throw std::runtime_error("Invalid XML");
                }

                // recupera o contexto da tag atual
                Context current = stack.pop();
                std::string content(readContent(current.contentBegin, contentEnd));
                current.node.setContent(content);
                // se após desempilhar a pilha ficar vazia, significa que
                // a tag desempilhada é a mais externa, indicando que é a raíz
                if (stack.empty()){
                    root = current.node;
                } else {
                    // caso contrário, adiciona a tag atual na lista de filhos
                    // da tag do topo, que é pai da atual
                    stack.top().node.addChild(current.node);
                }
            } else {
                // se for uma tag de abertura, apenas empilha-a com
                // um ponteiro para o início do seu conteúdo
                std::string identifier = readIdentifier(iter);
                stack.push({XmlTree(identifier), ++iter});
                continue;
            }
        }
        iter++;
    }

    // se ao final da leitura do arquivo a pilha não estiver vazia,
    // o arquivo xml está mal formado
    if (!stack.empty()) {
        throw std::runtime_error("Invalid XML");
    }

    // retorna a raíz (caso nao deu pra entender)
    return root;
}

std::string XmlParser::readIdentifier(std::string::iterator& iter) {
    std::string identifier{""};
    while (*iter != '>') {
        identifier += *iter;
        iter++;
    }
    return identifier;
}

std::string XmlParser::readContent(std::string::iterator contentBegin,
                                std::string::iterator contentEnd) {
    std::string content{""};
    while (contentBegin != contentEnd) {
        content += *contentBegin;
        ++contentBegin;
    }
    return content;
}
