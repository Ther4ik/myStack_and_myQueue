#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "rootedTree.h"

using Graph = rootedTree::adjacencyLists;
using Method = rootedTree::SearchMethod;

//        0                                      
//       / \
//      1---2
//     / \ / \
//    3   4---5

//       BFS           
//        0
//       / \
//      1   2
//     / \   \ 
//    3   4   5

//       DFS     
//        0
//        |
//        1
//       / \
//      2   3
//      |
//      4
//      |
//      5

static Graph sampleGraf()
{
    return {
        {1, 2},        // 0
        {0, 2, 3, 4},  // 1
        {0, 1, 4, 5},  // 2
        {1},           // 3
        {1, 2, 5},     // 4
        {2, 4}         // 5
    };
}

static void expectValidRootedTree(const Graph& g, const rootedTree& t, int root) // проверяет результат обхода
{
    const int countVertex = static_cast<int>(g.size());

    EXPECT_EQ(t.getParent(root), root);
    EXPECT_EQ(t.getDistance(root), 0);

    int treeEdges = 0; // счётчик рёбер дерева

    for (int vertex = 0; vertex < countVertex; vertex++)
    {
        if (vertex == root) continue;  // пропускаем проверки для корневой точки

        const int p = t.getParent(vertex);
        ASSERT_NE(p, -1) << "vertex " << vertex << " has no parent"; // проверка, что мы посетили точку p, которая является родителем для v

        EXPECT_NE(std::find(g[p].begin(), g[p].end(), vertex), g[p].end()) << "no edge " << p << " -> " << vertex;    // проверка, что ребро p - v существует в исходном графе
        EXPECT_EQ(t.getDistance(vertex), t.getDistance(p) + 1) << "vertex " << vertex;

        // идём к корню: должны дойти не более чем за n шагов
        int cur = vertex, steps = 0;
        while (cur != root && steps <= countVertex)
        {
            cur = t.getParent(cur);
            steps++;
        }
        EXPECT_EQ(cur, root) << "vertex " << vertex << " does not lead to the root";  // проверка, что дошли до корня

        treeEdges++;
    }
    EXPECT_EQ(treeEdges, countVertex - 1);        // свойство дерева: m = n - 1 
}

TEST(RootedTreeSample, BFSParentsAndDistances)
{
    rootedTree t(sampleGraf(), 0, Method::BFS);

    const int parents[] = { 0, 0, 0, 1, 1, 2 };
    const int distances[] = { 0, 1, 1, 2, 2, 2 };

    for (int v = 0; v < 6; ++v)
    {
        EXPECT_EQ(t.getParent(v), parents[v]) << "vertex " << v;
        EXPECT_EQ(t.getDistance(v), distances[v]) << "vertex " << v;
    }
}

TEST(RootedTreeSample, DFSParentsAndDistances)
{
    rootedTree t(sampleGraf(), 0, Method::DFS);

    const int parents[] = { 0, 0, 1, 1, 2, 4 };
    const int distances[] = { 0, 1, 2, 2, 3, 4 };

    for (int v = 0; v < 6; ++v)
    {
        EXPECT_EQ(t.getParent(v), parents[v]) << "vertex " << v;
        EXPECT_EQ(t.getDistance(v), distances[v]) << "vertex " << v;
    }
}

TEST(RootedTreeSample, BFSAndDFSBuildDifferentButValidTrees)
{
    const Graph g = sampleGraf();
    rootedTree bfs(g, 0, Method::BFS);
    rootedTree dfs(g, 0, Method::DFS);

    expectValidRootedTree(g, bfs, 0);
    expectValidRootedTree(g, dfs, 0);

    // у вершины 2 родители разные
    EXPECT_EQ(bfs.getParent(2), 0);
    EXPECT_EQ(dfs.getParent(2), 1);
    EXPECT_LT(bfs.getDistance(5), dfs.getDistance(5));   // BFS даёт кратчайшие
}

TEST(RootedTreeSample, ConstructorWithMethodChecksArguments)
{
    EXPECT_THROW(rootedTree(sampleGraf(), -1, Method::BFS), std::out_of_range);
    EXPECT_THROW(rootedTree(sampleGraf(), 6, Method::DFS), std::out_of_range);
}

TEST(RootedTreeSample, TwoArgConstructorStillRequiresTraversal)
{
    rootedTree t(sampleGraf(), 0);
    EXPECT_THROW(t.getParent(0), std::logic_error);
}