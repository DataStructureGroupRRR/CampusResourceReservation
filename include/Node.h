#ifndef NODE_H
#define NODE_H

#define DELETE_LL(headNode, nextNode)\
while (headNode) {\
    nextNode = headNode->next;\
    delete headNode;\
\
    headNode = nextNode;\
}

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