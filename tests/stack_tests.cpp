#include <stdexcept>
#include <string>
#include <gtest/gtest.h>
#include "myStack.h"

TEST(MyStackTest, NewStackIsEmpty)
{
    myStack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(MyStackTest, PushIncreasesSizeAndSetsTop)
{
    myStack<int> s;

    s.push(1);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1u);
    EXPECT_EQ(s.top(), 1);

    s.push(2);
    EXPECT_EQ(s.size(), 2u);
    EXPECT_EQ(s.top(), 2);
}

TEST(MyStackTest, PopFollowsLifoOrder)
{
    myStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    EXPECT_EQ(s.size(), 2u);

    s.pop();
    EXPECT_EQ(s.top(), 1);
    EXPECT_EQ(s.size(), 1u);
}

TEST(MyStackTest, TopReturnsModifiableReference)
{
    myStack<int> s;
    s.push(1);
    s.push(2);

    s.top() = 20;           // меняем верхний элемент через ссылку
    EXPECT_EQ(s.top(), 20);
    EXPECT_EQ(s.size(), 2u);
}

TEST(MyStackTest, ConstTopWorks)
{
    myStack<int> s;
    s.push(5);
    s.push(7);

    const myStack<int>& cs = s;
    EXPECT_EQ(cs.top(), 7);
    EXPECT_EQ(cs.size(), 2u);
}

TEST(MyStackTest, PopOnEmptyThrows)
{
    myStack<int> s;
    EXPECT_THROW(s.pop(), std::out_of_range);

    s.push(1);
    s.pop();
    EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(MyStackTest, TopOnEmptyThrows)
{
    myStack<int> s;
    const myStack<int>& cs = s;
    EXPECT_THROW(cs.top(), std::out_of_range);
}

TEST(MyStackTest, WorksWithStrings)
{
    myStack<std::string> s;
    s.push("hello");
    s.push("world");

    EXPECT_EQ(s.top(), "world");
    s.pop();
    EXPECT_EQ(s.top(), "hello");
}