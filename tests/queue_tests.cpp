#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "myQueue.h"

TEST(MyQueueTest, NewQueueIsEmpty)
{
    myQueue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(MyQueueTest, SingleElementIsFrontAndBack)
{
    myQueue<int> q;
    q.push(1);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 1);
}

TEST(MyQueueTest, FrontIsFirstPushedBackIsLastPushed)
{
    myQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
    EXPECT_EQ(q.size(), 3u);
}

TEST(MyQueueTest, ConstFrontAndBack)
{
    myQueue<int> q;
    q.push(5);
    q.push(7);

    const myQueue<int>& cq = q;
    EXPECT_EQ(cq.front(), 5);
    EXPECT_EQ(cq.back(), 7);
    EXPECT_EQ(cq.size(), 2u);
}

TEST(MyQueueTest, PopRemovesFrontElement)
{
    myQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 3);
    EXPECT_EQ(q.size(), 2u);
}

TEST(MyQueueTest, FifoOrderIsPreserved)
{
    myQueue<int> q;
    for (int i = 0; i < 5; ++i)
        q.push(i);

    for (int i = 0; i < 5; ++i)
    {
        ASSERT_FALSE(q.empty());
        EXPECT_EQ(q.front(), i);
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

TEST(MyQueueTest, ReuseAfterBecomingEmpty)
{
    myQueue<int> q;
    q.push(1);
    q.pop();
    q.push(2);

    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 2);
}

TEST(MyQueueTest, PopOnEmptyThrows)
{
    myQueue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(MyQueueTest, FrontAndBackOnEmptyThrow)
{
    myQueue<int> q;
    EXPECT_THROW(q.front(), std::out_of_range);
    EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(MyQueueTest, WorksWithStrings)
{
    myQueue<std::string> q;
    q.push("hello");
    q.push("world");

    EXPECT_EQ(q.front(), "hello");
    EXPECT_EQ(q.back(), "world");
    q.pop();
    EXPECT_EQ(q.front(), "world");
}

