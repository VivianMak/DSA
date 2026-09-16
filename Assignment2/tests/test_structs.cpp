#include <gtest/gtest.h>
#include "structs.hpp"
#include "DoublyLinkedList.hpp"

void createOrderedList(DoublyLinkedList::DoublyLinkedList<int>& list){
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
}

TEST(LinkedList, EmptyList)
{
    DoublyLinkedList::DoublyLinkedList<int> list;
    EXPECT_TRUE(list.popFront() == std::nullopt);
    EXPECT_TRUE(list.popBack() == std::nullopt);
    EXPECT_TRUE(list.peekFront() == std::nullopt);
    EXPECT_TRUE(list.peekBack() == std::nullopt);
    // Popping/peeking an empty list must leave it unchanged.
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(LinkedList, PushFront)
{
    DoublyLinkedList::DoublyLinkedList<int> list;
    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    // list is now: 3 <-> 2 <-> 1
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.peekFront(), 3);
    EXPECT_EQ(list.peekBack(), 1);
}

TEST(LinkedList, PushBack)
{
    DoublyLinkedList::DoublyLinkedList<int> list;
    createOrderedList(list);
    // list is now: 1 <-> 2 <-> 3
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.peekFront(), 1);
    EXPECT_EQ(list.peekBack(), 3);
}

TEST(LinkedList, PopFuncs)
{
    DoublyLinkedList::DoublyLinkedList<int> list;
    createOrderedList(list);
    // list is now: 1 <-> 2 <-> 3
    EXPECT_EQ(list.popFront(), 1);
    EXPECT_EQ(list.popBack(), 3);
}

TEST(LinkedList, PopFuncReassign)
{
    DoublyLinkedList::DoublyLinkedList<int> list;
    createOrderedList(list);
    // list is now: 1 <-> 2 <-> 3
    EXPECT_EQ(list.popBack(), 3);
    EXPECT_EQ(list.popBack(), 2);
}