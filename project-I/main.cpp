#include <iostream>
#include <istream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

template<typename T>
class ArrayStack {
public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

    void print();

private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};


template<typename T>
ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    // COLOQUE SEU CODIGO AQUI...
    max_size_ = max;
    contents = new T[max];
    top_ = -1;
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

template<typename T>
void ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        // COLOQUE SEU CODIGO AQUI...
        top_++;
        contents[top_] = data;
    }
}

template<typename T>
T ArrayStack<T>::pop() {
    // COLOQUE SEU CODIGO AQUI...
    if (top_ == -1) {
        throw std::out_of_range("pilha vazia");
    }
    top_--;
    return contents[top_ + 1];
}

template<typename T>
T& ArrayStack<T>::top() {
    // COLOQUE SEU CODIGO AQUI...
    return contents[top_];
}

template<typename T>
void ArrayStack<T>::clear() {
    // COLOQUE SEU CODIGO AQUI...
    top_ = -1;
}

template<typename T>
std::size_t ArrayStack<T>::size() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1;
}

template<typename T>
std::size_t ArrayStack<T>::max_size() {
    // COLOQUE SEU CODIGO AQUI...
    return max_size_;
}

template<typename T>
bool ArrayStack<T>::empty() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ == -1;
}

template<typename T>
bool ArrayStack<T>::full() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1 == static_cast<int>(max_size_);
}

template<typename T>
void ArrayStack<T>::print() {
    for (int i = 0; i < top_; i++) {
        std::cout << contents[i] << ", ";
    }
    std::cout << contents[top_] << '\n';
}

class XmlParser {
public:
    class XmlNode {
    public:
        XmlNode(const std::string& tag, const std::string& content, const std::vector<XmlNode>& children):
            tag(tag), content(content), children(children) {}

        XmlNode(const std::string& tag): tag(tag) {}

        void addChild(XmlNode& child) {
            children.push_back(child);
        }

        void addContent(const std::string& content) {
            this->content = content;
        }

    private:
        friend class XmlParser;

        const std::string tag;
        std::string content;
        std::vector<XmlNode> children;
    };


    XmlParser(const std::string& filePath) {
    }
};

int main() {
    std::string xmlPath;
    std::cin >> xmlPath;
    std::cout << xmlPath << '\n';

    std::ifstream xmlFile(xmlPath);
    std::istream_iterator<char> iter(xmlFile), end;

    ArrayStack<std::string> stack;
    /* XmlParser::XmlNode root("root"); */
    /* stack.push("root"); */

    // lê caractere por caractere
    while (iter != end) {
        if (*iter == '<') {
            if (*(++iter) == '/') {
                if (stack.empty()) {
                    throw std::runtime_error("Invalid XML");
                }

                iter++;
                std::string tag;
                while (*iter != '>') {
                    tag += *iter;
                    iter++;
                }

                if (tag != stack.top()) {
                    throw std::runtime_error("Invalid XML");
                }

                stack.pop();
                stack.print();
            }
            else {
                std::string tag;
                while (*iter != '>') {
                    tag += *iter;
                    iter++;
                }

                stack.push(tag);
                stack.print();
            }
        }
        iter++;
    }

    return 0;
}
