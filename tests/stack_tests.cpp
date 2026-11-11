#include <stdexcept>
#include <gtest/gtest.h>
#include "myStack.h"

TEST(MyStackTest, NewStackIsEmpty)
{

}

TEST(MyStackTest, PushIncreasesSizeAndSetsTop)
{

}

TEST(MyStackTest, PopFollowsLifoOrder)
{

}

TEST(MyStackTest, TopReturnsModifiableReference)
{

}

TEST(MyStackTest, ConstTopWorks)
{

}

TEST(MyStackTest, PopOnEmptyThrows)
{

}

TEST(MyStackTest, TopOnEmptyThrows)
{

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