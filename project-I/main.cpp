// Copyright [2024] <Caio César Rodrigues de Aquino, Luan da Silva Moraes>

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
        top_++;
        contents[top_] = data;
    }
}

template <typename T>
T ArrayStack<T>::pop() {
    if (top_ == -1) {
        throw std::out_of_range("pilha vazia");
    }
    top_--;
    return contents[top_ + 1];
}

template <typename T>
T& ArrayStack<T>::top() {
    return contents[top_];
}

template <typename T>
void ArrayStack<T>::clear() {
    top_ = -1;
}

template <typename T>
std::size_t ArrayStack<T>::size() {
    return top_ + 1;
}

template <typename T>
std::size_t ArrayStack<T>::max_size() {
    return max_size_;
}

template <typename T>
bool ArrayStack<T>::empty() {
    return top_ == -1;
}

template <typename T>
bool ArrayStack<T>::full() {
    return top_ + 1 == static_cast<int>(max_size_);
}

template <typename T>
void ArrayStack<T>::print() {
    for (int i = 0; i <= top_; i++) {
        contents[i].print();
    }
    std::cout << std::endl;
}

class XmlTree {
    public:
    XmlTree() = default;

    XmlTree(const XmlTree& other) : identifier(other.identifier), content(other.content) {
        for (const auto& child : other.children) {
            children.push_back(child);
        }
    }

    XmlTree& operator=(const XmlTree& other) {
        if (this != &other) {
            this->identifier = other.getIdentifier();
            this->content = other.content;
            this->children = other.children;
        }
        return *this;
    }

    std::vector<XmlTree> operator[](const std::string& identifier) {
        std::vector<XmlTree> nodes;
        for (auto& child : children) {
            if (child.getIdentifier() == identifier) {
                nodes.push_back(child);
            }
        }

        if (nodes.size() > 0) {
            return nodes;
        }

        std::string msg = "Identifier not found: " + identifier;
        throw std::runtime_error(msg);
    }

    void addChild(XmlTree& child) { children.push_back(child); }

    std::string getContent() const { return this->content; }

    void setContent(const std::string& content) { this->content = content; }

    std::vector<XmlTree> getChildren() const { return this->children; }

    std::string getIdentifier() const { return this->identifier; }

  private:
    friend class XmlParser;

    XmlTree(const std::string& identifier) : identifier(identifier) {}

    XmlTree(const std::string& identifier, const std::string& content,
            const std::vector<XmlTree>& children)
        : identifier(identifier), content(content), children(children) {}

    std::string identifier;
    std::string content;
    std::vector<XmlTree> children;
};

class XmlParser {
  public:
    static XmlTree parse(const std::string& xmlPath) {
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

  private:
    static std::string readIdentifier(std::string::iterator& iter) {
        std::string identifier{""};
        while (*iter != '>') {
            identifier += *iter;
            iter++;
        }
        return identifier;
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

struct Coordinate {
    int x;
    int y;
};

class Solver {
  public:
    static int solve(std::vector<std::vector<int>>& matrix, Coordinate robotPos) {
        if (matrix[robotPos.x][robotPos.y] == 0) {
            return 0;
        }

        int height = matrix.size();
        int width = matrix[0].size();

        ArrayStack<Coordinate> cellsToVisit(2350);

        matrix[robotPos.x][robotPos.y] = 0;
        int totalArea = 1;

        Coordinate offsets[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
        while (true) {
            for (const auto& offset : offsets) {
                Coordinate newPos = {robotPos.x + offset.x, robotPos.y + offset.y};
                if (newPos.x < 0 || newPos.x >= height || newPos.y < 0 || newPos.y >= width) {
                    continue;
                }
                if (matrix[newPos.x][newPos.y] == 1) {
                    // marca a posição empilhada como 0 para não ser empilhada novamente
                    // futuramente
                    matrix[newPos.x][newPos.y] = 0;
                    totalArea++;
                    cellsToVisit.push({newPos.x, newPos.y});
                }
            }

            if (cellsToVisit.empty()) {
                return totalArea;
            }

            robotPos = cellsToVisit.pop();
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <xml_path>\n";
        return 1;
    }

    std::string xmlPath = argv[1];
    XmlTree xml;
    try {
        xml = XmlParser::parse(xmlPath);
    }
    catch (std::runtime_error e) {
        std::cout << "erro\n";
        return 0;
    }

    for (auto& scenario : xml["cenario"]) {
        int width = std::stoi(scenario["dimensoes"][0]["largura"][0].getContent());
        int height = std::stoi(scenario["dimensoes"][0]["altura"][0].getContent());

        // a matriz vem do xml como uma string unidimensional.
        // Portanto, transforma-se-a em uma matriz bidimensional antes de
        // computar a área varrida pelo robô
        std::string xmlMatrix = scenario["matriz"][0].getContent();
        std::vector<std::vector<int>> matrix(height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                matrix[i].push_back(xmlMatrix[i * width + j] - '0');
            }
        }

        int robotX = std::stoi(scenario["robo"][0]["x"][0].getContent());
        int robotY = std::stoi(scenario["robo"][0]["y"][0].getContent());
        Coordinate robotPos = {robotX, robotY};

        int totalArea = Solver::solve(matrix, robotPos);
        std::cout << scenario["nome"][0].getContent() << " " << totalArea << '\n';
    }

    return 0;
}
