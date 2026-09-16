# Assignment 2 - Linked Data Structures

## [`DoublyLinkedList.hpp`](include/DoublyLinkedList.hpp)

The implementation of the double linked list is used for the stack and queue data structure.

```cpp
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node*  head_;   // front of list
    Node*  tail_;   // back of list
    size_t len_; 

public:
    DoublyLinkedList();

    void pushFront(T data);   // insert at front
    void pushBack(T data);    // insert at back

    std::optional<T> popFront();    // remove & return front value, nullopt if empty
    std::optional<T> popBack();     // remove & return back value, nullopt if empty

    std::optional<T> peekFront() const; // read front value, nullopt if empty
    std::optional<T> peekBack()  const; // read back value, nullopt if empty

    bool   isEmpty() const;
    size_t getSize() const;
};
};
```


```cpp
// Last In, First Out
class Stack {
private:
    DoublyLinkedList<T> list_;
public:
    void push(T data);    // insert at back

    std::optional<T> pop();       // remove & return front value
    std::optional<T> peek();      // return front value

    bool    isEmpty();
    size_t  getSize();
}

// First In, First Out
class Queue {
private:
    DoublyLinkedList<T> list_;
public:
    void enqueue(T data);    // insert at back

    std::optional<T> dequeue();     // remove & return front value
    std::optional<T> peek();        // return front value

    bool    isEmpty();
    size_t  getSize();
}

            
```
