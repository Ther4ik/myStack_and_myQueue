#ifndef ROOTEDTREE_H
#define ROOTEDTREE_H

#include <vector>
#include <stdexcept>
#include "myQueue.h"

class rootedTree
{
public:
	using adjacencyLists = std::vector<std::vector<int>>;

private:
	int _rootNode = -1;           // кореневая вершина
	std::vector<int> _parents;    // родители
	std::vector<int> _distance;   // расстояние от корня вершины. _distance[0] - расстояние от корня до точки 0 и т.д.
	adjacencyLists _graf;         // списки смежности для корневого дерева. graf[v] — только соседи вершины v
	
public:

	rootedTree(const adjacencyLists& graf, int root): _rootNode(root), _graf(graf)
	{
		int countVertex = static_cast<int>(_graf.size());

		if (root < 0 || root >= countVertex)
			throw std::out_of_range("rootedTree: root node is out of range");

		for (const auto& neighbors : _graf)
			for (int j : neighbors)
				if (j < 0 || j >= countVertex)
					throw std::out_of_range("rootedTree: neighbor is out of range");
	}

	void BFS()     
	{
		int countVertex = static_cast<int>(graf.size());
	
		_distance.assign(countVertex, -1);                 // значение -1 - вершина не посещенная или недостижима
		_parents.assign(countVertex, -1);

		myQueue<int> Q;                                    //очередь для работы с графом
		Q.push(_rootNode);
		_parents[_rootNode] = _rootNode;
		_distance[_rootNode] = 0;

		while (!Q.empty())
		{
			int current = Q.front();
			Q.pop();

			for (int neighbor: graf[current])
			{
				if (_distance[neighbor] == -1)
				{
					_distance[neighbor] = _distance[current] + 1;
					_parents[neighbor] = current;
					Q.push(neighbor);
				}
			}

		}
	}




};

#endif // ROOTEDTREE_H