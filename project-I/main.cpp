#include <cstdint> // std::size_t
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <stdexcept> // C++ exceptions
#include <string>
#include <vector>

template <typename T> class ArrayStack {
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

template <typename T>
ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template <typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    // COLOQUE SEU CODIGO AQUI...
    max_size_ = max;
    contents = new T[max];
    top_ = -1;
}

template <typename T>
ArrayStack<T>::~ArrayStack() { delete[] contents; }

template <typename T>
void ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        // COLOQUE SEU CODIGO AQUI...
        top_++;
        contents[top_] = data;
    }
}

template <typename T>
T ArrayStack<T>::pop() {
    // COLOQUE SEU CODIGO AQUI...
    if (top_ == -1) {
        throw std::out_of_range("pilha vazia");
    }
    top_--;
    return contents[top_ + 1];
}

template <typename T>
T& ArrayStack<T>::top() {
    // COLOQUE SEU CODIGO AQUI...
    return contents[top_];
}

template <typename T>
void ArrayStack<T>::clear() {
    // COLOQUE SEU CODIGO AQUI...
    top_ = -1;
}

template <typename T>
std::size_t ArrayStack<T>::size() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1;
}

template <typename T>
std::size_t ArrayStack<T>::max_size() {
    // COLOQUE SEU CODIGO AQUI...
    return max_size_;
}

template <typename T>
bool ArrayStack<T>::empty() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ == -1;
}

template <typename T>
bool ArrayStack<T>::full() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1 == static_cast<int>(max_size_);
}

class XmlParser {
  public:
    class XmlNode {
      public:
        XmlNode(const std::string& tag = "") : tag(tag) {}

        void addChild(XmlNode& child) { children.push_back(child); }

        void setContent(const std::string& content) { this->content = content; }

        std::vector<XmlNode> getChildren() const { return this->children; }

        std::string getTag() const { return this->tag; }

      private:
        XmlNode(const std::string& tag, const std::string& content,
                const std::vector<XmlNode>& children)
            : tag(tag), content(content), children(children) {}

        friend class XmlParser;

        const std::string tag;
        std::string content;
        std::vector<XmlNode> children;
    };

    typedef XmlNode XmlTree;

    static void parse(const std::string& xmlPath) {
        std::ifstream xmlFile(xmlPath);
        std::istream_iterator<char> iter(xmlFile), end;

        struct Context {
            Context& operator=(const Context& other);
            XmlNode node;
            std::istream_iterator<char> tagOpening;
        };

        XmlTree root;
        ArrayStack<Context> stack;
        std::string currentTag;
        std::string content;
        bool toReadContent = false;

        // lê caractere por caractere
        while (!stack.empty() && iter != end) {
            if (*iter == '<') {
                if (*(++iter) == '/') {
                    iter++;
                    std::string tag = readTag(&iter);
                    if (tag != stack.top().node.getTag()) {
                        throw std::runtime_error("Invalid XML");
                    }

                    stack.pop();
                    stack.print();
                } else {
                    std::string tag = readTag(&iter);
                    stack.push({XmlNode(tag), iter});
                    stack.print();
                }
            }
            iter++;
        }

        /* while (iter != end) { */
        /*     if (*iter == '<') { */
        /*         if (*(++iter) == '/') { */
        /*             if (stack.empty()) { */
        /*                 throw std::runtime_error("Invalid XML"); */
        /*             } */
        /**/
        /*             iter++; */
        /*             std::string tag = readTag(&iter); */
        /*             if (tag != stack.top().node.tag) { */
        /*                 throw std::runtime_error("Invalid XML"); */
        /*             } */
        /**/
        /*             stack.pop(); */
        /*             stack.print(); */
        /*         } else { */
        /*             std::string tag = readTag(&iter); */
        /*             stack.push(tag); */
        /*             stack.print(); */
        /*         } */
        /*     } */
        /*     iter++; */
        /* } */

        if (!stack.empty()) {
            throw std::runtime_error("Invalid XML");
        }

        /* return root; */
    }

  private:
    static std::string readTag(std::istream_iterator<char>* iter) {
        std::string tag;
        while (**iter != '>') {
            tag += **iter;
            (*iter)++;
        }
        return tag;
    }
};

int main() {
    std::string xmlPath;
    std::cin >> xmlPath;
    std::cout << xmlPath << '\n';

    XmlParser::XmlTree xml = XmlParser::parse(xmlPath);
    XmlParser::parse(xmlPath);

    return 0;
}
