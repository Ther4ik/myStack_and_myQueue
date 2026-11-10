#include <stdexcept>
#include "gtest.h"
#include "myQueue.h"

TEST(MyQueue, NewStackIsEmpty)
{
    myQueue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

