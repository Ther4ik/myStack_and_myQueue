#ifndef ROOTEDTREE_H
#define ROOTEDTREE_H

#include <vector>
#include <stdexcept>
#include <cstddef>
#include "myQueue.h"
#include "myStack.h"

class rootedTree
{
public:
	using adjacencyLists = std::vector<std::vector<int>>;
	enum class SearchMethod { BFS, DFS };

private:
	int _rootNode = -1;           // корневая вершина
	std::vector<int> _parents;    // родители
	std::vector<int> _distance;   // расстояние от корня вершины. _distance[0] - расстояние от корня до точки 0 и т.д.
	adjacencyLists _graf;         // списки смежности для корневого дерева. graf[v] — только соседи вершины v
	
	void checkVertex(int vertex) const
	{
		if (_parents.empty())
			throw std::logic_error("rootedTree: neither BFS nor DFS has been run yet");
		if (vertex < 0 || vertex >= static_cast<int>(_parents.size()))
			throw std::out_of_range("rootedTree: vertex is out of range");
	}

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

	rootedTree(const adjacencyLists& graf, int root, SearchMethod method): rootedTree(graf, root)     
	{	
		if (method == SearchMethod::BFS)
			BFS();
		else
			DFS();
	}

	void BFS()     
	{
		int countVertex = static_cast<int>(_graf.size());
	
		_distance.assign(countVertex, -1);                 // значение -1 - вершина не посещенная или недостижима
		_parents.assign(countVertex, -1);

		myQueue<int> Q;                                    // очередь для работы с графом
		Q.push(_rootNode);
		_parents[_rootNode] = _rootNode;
		_distance[_rootNode] = 0;                          // расстояние от корневой до корневой точки                  

		while (!Q.empty())
		{
			int current = Q.front();
			Q.pop();

			for (int neighbor: _graf[current])
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

	int getParent(int vertex) const
	{
		checkVertex(vertex);
		return _parents[vertex];
	}

	int getDistance(int vertex) const
	{
		checkVertex(vertex);
		return _distance[vertex];
	}

	void DFS()
	{
		int countVertex = static_cast<int>(_graf.size());

		_distance.assign(countVertex, -1);                 // перезаписываем результаты для дистанции и для родителей   
		_parents.assign(countVertex, -1);
		
		std::vector<std::size_t> next(countVertex, 0);     // next[v] - индекс следующего соседа v

		myStack<int> S;                                    // cтек для работы с графом
		S.push(_rootNode);
		_parents[_rootNode] = _rootNode;
		_distance[_rootNode] = 0;

		while (!S.empty())
		{
			int current = S.top();

			if (next[current] < _graf[current].size())        // проверяем, всех ли соседей вершины мы просмотрели
			{
				int follow = _graf[current][next[current]];
				next[current]++;

				if (_distance[follow] == -1)                  // заходим в непосещённую вершину
				{ 
					_parents[follow] = current;
					_distance[follow] = _distance[current] + 1;
					S.push(follow);
				}
			}
			else
			{
				S.pop();                                 // соседи кончились: возвращаемся назад
			}
		}
	}
};

#endif // ROOTEDTREE_H