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
```

## [`structs.hpp`](include/structs.hpp)

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
};

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
};
```

<br>

## Practice Problems with Stacks and Queues - Strategies

## Exercise 3 (Implemented)
> How would you reverse the elements in a stack (i.e., put the elements at the top of the stack on the bottom and vice versa)? You can use as many additional stacks and queues as temporary storage in your approach.

1. Make an empty list of size = getSize()?
2. Given the list of elements, start with the tail pointer
3. Loop backwards on the stack, until head pointer (prev pointer is null)
4. Create a node, setting tail to head and vice versa

## Exercise 4 (Implemented)
> Come up with a strategy to solve the [valid parentheses problem](https://leetcode.com/problems/valid-parentheses/description/)

1. Create a mapping of the correct set of parentheses
2. Looking at the string, we can assume valid until a mismatch
3. Looping through the list, we want to add opening parentheses to a stack
4. Until a closing parenthesis, we pop the top (last) of the stack if matched
5. If not, return false

Implementation: [`main.cpp`](src/main.cpp)

```cpp


```

## Exercise 5
> Solve the copy stack problem (source: University of Washington CSE122).
> Given a stack return a copy of the original stack (i.e., a new stack with the same values as the original, stored in the same order as the original). Your method should create the new stack and fill it up with the same values that are stored in the original stack.
> You may use one queue as auxiliary storage.