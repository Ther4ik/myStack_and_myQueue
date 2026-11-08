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


	void BFS(const adjacencyLists& graf, int rootNode)     //передаю список смежности, граф, который мы исследуем  
	{
		int countVertex = static_cast<int>(graf.size());
		if (rootNode < 0 || rootNode >= countVertex)
			throw std::out_of_range("BFS: root node is out of range");

		_graf = graf;                                      //используем оператор копирования, чтобы выделить память и ячейки для написания списка смежности для корневого графа
		_rootNode = rootNode;
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
				if (neighbor < 0 || neighbor >= countVertex)                               //проверка, что в списках смежности нет некоторых точек, чтобы не сломать работу программы 
					throw std::out_of_range("BFS: neighbor is out of range");              

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