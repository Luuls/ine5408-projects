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

template <typename T>
void ArrayStack<T>::print() {
    for (int i = 0; i <= top_; i++) {
        contents[i].print();
    }
    std::cout << std::endl;
}

class XmlParser {
  public:
    // TODO: criar um nó abstrato para criar dois tipos de nós: um para apenas 1 nó
    // e outro para representar vários filhos. Exemplo: XmlElement e XmlElementCollection
    class XmlNode {
      public:
        XmlNode(const std::string& tag = "") : tag(tag) {}
        XmlNode(const XmlNode& other) : tag(other.tag), content(other.content) {
            for (const auto& child : other.children) {
                children.push_back(child);
            }
        }
        XmlNode& operator=(const XmlNode& other) {
            if (this != &other) {
                this->tag = other.getTag();
                this->content = other.content;
                this->children = other.children;
            }
            return *this;
        }

        std::vector<XmlNode> operator[](const std::string& tag) {
            std::vector<XmlNode> nodes;
            for (auto& child : children) {
                if (child.getTag() == tag) {
                    nodes.push_back(child);
                }
            }

            if (nodes.size() > 0) {
                return nodes;
            }

            std::string msg = "Tag not found: " + tag;
            throw std::runtime_error(msg);
        }

        void addChild(XmlNode& child) { children.push_back(child); }

        std::string getContent() const { return this->content; }

        void setContent(const std::string& content) { this->content = content; }

        std::vector<XmlNode> getChildren() const { return this->children; }

        std::string getTag() const { return this->tag; }

      private:
        XmlNode(const std::string& tag, const std::string& content,
                const std::vector<XmlNode>& children)
            : tag(tag), content(content), children(children) {}

        friend class XmlParser;

        std::string tag;
        std::string content;
        std::vector<XmlNode> children;
    };

    typedef XmlNode XmlTree;

    static XmlTree parse(const std::string& xmlPath) {
        std::ifstream xmlFile(xmlPath);
        std::istream_iterator<char> iterFile(xmlFile), endFile;
        std::string xmlContent(iterFile, endFile);
        std::string::iterator iter = xmlContent.begin();
        std::string::iterator end = xmlContent.end();

        // struct local para armazenar o contexto de cada tag
        struct Context {
            XmlNode node;
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

                    std::string tag = readTag(&iter);
                    if (stack.empty() || tag != stack.top().node.getTag()) {
                        throw std::runtime_error("Invalid XML");
                    }

                    Context current = stack.pop();
                    std::string content(readContent(current.contentBegin, contentEnd));
                    current.node.setContent(content);
                    if (stack.empty()){
                        root = current.node;
                    } else {
                        // FIX: Precisa checar se a tag atual vai ter mais de 1 filho
                        stack.top().node.addChild(current.node);
                    }
                } else {
                    std::string tag = readTag(&iter);
                    stack.push({XmlNode(tag), ++iter});
                    continue;
                }
            }
            iter++;
        }

        if (!stack.empty()) {
            throw std::runtime_error("Invalid XML");
        }

        return root;
    }

  private:
    static std::string readTag(std::string::iterator* iter) {
        std::string tag{""};
        while (**iter != '>') {
            tag += **iter;
            (*iter)++;
        }
        return tag;
    }

    // Utilizado para ler o conteúdo dentro de uma tag, a partir de iteradores
    // que apontam para o começo e para o fim do conteúdo.
    static std::string readContent(std::string::iterator contentBegin,
                                   std::string::iterator contentEnd) {
        std::string content{""};
        while (contentBegin != contentEnd) {
            content += *contentBegin;
            ++contentBegin;
        }
        return content;
    }
};

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <xml_path>\n";
        return 1;
    }
    std::string xmlPath = argv[1];
    std::cout << xmlPath << '\n';

    XmlParser::XmlTree xml = XmlParser::parse(xmlPath);
    for (auto& cenario : xml["cenario"]) {
        // TODO: deveria ser utilizado da seguinte forma:
        // XmlElement& name = cenario["nome"];
        // ao invés de um for, já que a tag cenário só possui um nome
        for (auto& nome : cenario["nome"]) {
            std::cout << nome.getTag() << ": " << nome.getContent() << '\n';
        }
    }

    return 0;
}
