#ifndef ROOTEDTREE_H
#define ROOTEDTREE_H

#include <vector>
#include <iostream>
#include "myQueue.h"

class rootedTree
{
public:
	using adjacencyLists = std::vector<std::vector<int>>;

private:
	int _rootNode = -1;           // коренвая вершина
	std::vector<int> _parents;    // родители
	std::vector<int> _child;      // дети 
	adjacencyLists _graf;         // списки смежности для корневого дерева 0: 1,2,3 ; 1:4,5,6 и т.д. Первый элемент - номер вершина, а после идут смежные вершины с ней 
	
public:

	void BFS(const adjacencyLists& graf, int rootNode)            //передаю список смежности, граф, который мы исследуем  
	{
		_rootNode = rootNode;
		size_t countVertex = graf.size(); 
		myQueue<int> Q;                                    //очередь для работы с графом
		std::vector<bool> order(countVertex, false);       //изначально все вершины не посещенный
		Q.push(_rootNode);
		order[_rootNode] = true;

		while (!Q.empty())
		{
			int current = Q.front();
			Q.pop();
			for (int i = 0; i < graf[current].size(); i++)
			{
				int neighbor = graf[current][i];
				if (!order[neighbor])
				{
					order[neighbor] = true;
					Q.push(neighbor);
				}
			}
		}
	}


};

#endif // ROOTEDTREE_H