#include <stdexcept>
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
    s.push(2);
    EXPECT_FALSE(s.empty());
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
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(MyStackTest, TopReturnsModifiableReference)
{
    myStack<int> s;
    s.push(5);
    s.top() = 10;
    EXPECT_EQ(s.top(), 10);
}

TEST(MyStackTest, ConstTopWorks)
{
    myStack<int> s;
    s.push(7);
    const myStack<int>& cs = s;
    EXPECT_EQ(cs.top(), 7);
}

TEST(MyStackTest, PopOnEmptyThrows)
{
    myStack<int> s;
    EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(MyStackTest, TopOnEmptyThrows)
{
    myStack<int> s;
    EXPECT_THROW(s.top(), std::out_of_range);

    const myStack<int>& cs = s;
    EXPECT_THROW(cs.top(), std::out_of_range);
}

TEST(MyStackTest, WorksWithStrings)
{
    myStack<std::string> s;
    s.push("hello");
    s.push("world");

    EXPECT_EQ(q.top(), "world");
    s.pop();
    EXPECT_EQ(s.top(), "hello");
}