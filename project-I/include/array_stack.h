#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions


template<typename T>
//! CLASSE PILHA
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

#endif

