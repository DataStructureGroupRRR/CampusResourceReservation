#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    public:
        Node(T value) : value(value) {
            this->prev = nullptr;
            this->next = nullptr;
        }

        T value;
        
        Node<T>* prev;
        Node<T>* next;
};

#endif // NODE_H