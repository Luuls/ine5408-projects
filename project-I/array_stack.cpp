#include "array_stack.h"

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    // COLOQUE SEU CODIGO AQUI...
    max_size_ = max;
    contents = new T[max];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        // COLOQUE SEU CODIGO AQUI...
        top_++;
        contents[top_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    // COLOQUE SEU CODIGO AQUI...
    if (top_ == -1) {
        throw std::out_of_range("pilha vazia");
    }
    top_--;
    return contents[top_ + 1];
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    // COLOQUE SEU CODIGO AQUI...
    return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    // COLOQUE SEU CODIGO AQUI...
    top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    // COLOQUE SEU CODIGO AQUI...
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ == -1;
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1 == static_cast<int>(max_size_);
}

