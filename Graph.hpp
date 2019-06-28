#pragma once
#include  <vector>
#include  <string>
template<class T>
class Graph
{
	T* _graphPoint;
	std::vector<Graph*>* _graphNextPoints;

public:
	Graph(T& data)
		: _graphPoint(new T(data)),
		  _graphNextPoints(new std::vector<Graph*>())
	{
		std::cout << "Graph const" << std::endl;
	}
	~Graph()
	{
		delete _graphPoint;
		delete _graphNextPoints;
		std::cout << "Graph desturctor" << std::endl;
	}
	T& getGraphPoint() { return *_graphPoint; }
	void addGraphNextPoint(Graph *place)
	{
		_graphNextPoints->push_back(place);
	}
	bool operator==(Graph<T>& other)
	{
		return this->getGraphPoint() == other.getGraphPoint();
	}
	bool elementsNextPoint(T& point)
	{
		int max = _graphNextPoints->size();
		for (int i = 0; i < max; ++i)
		{
			Graph *p = (*_graphNextPoints)[i];
			if (point == p->getGraphPoint())
				return true;
		}
		return false;
	}
	std::vector<Graph*>* getNextPoints()
	{
		return this->_graphNextPoints;
	}
};


