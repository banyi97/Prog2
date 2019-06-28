#pragma once
#include "Graph.hpp"
#include <fstream>
#include <sstream>

template <class T>
class GraphStorage
{
private:
	std::vector<Graph<T>*> *_storage;
	
	Graph<T>* addNewPoint(T& point)
	{
		auto *newGraph = new Graph<T>(point);
		_storage->push_back(newGraph);
		return  newGraph;
	}
public:
	GraphStorage() : _storage(new std::vector<Graph<T>*>()) { std::cout << "Graphstorage const" << std::endl; };
	GraphStorage(GraphStorage *p) { (*_storage) = (*p); }
	~GraphStorage() { freeGraphStorage(); delete _storage; std::cout << "Graphstorage destructor" << std::endl; };
	void addGraphPoint(T& point1,T& point2)
	{
		Graph<T> *p;
		int num = findElemenet(point1);
		if (num == -1)
		{
			p = addNewPoint(point1);
		}
		else
		{
			p = (*_storage)[num];
		}
		num = findElemenet(point2);
		if(num == -1)
		{
			Graph<T> *p2 = addNewPoint(point2);
			p->addGraphNextPoint(p2);
		}
		else
		{
			if(!(p->elementsNextPoint(point2)))
				p->addGraphNextPoint((*_storage)[num]);
		}
	}
	int findElemenet(T& data)
	{
		for(int i = 0; i<_storage->size();++i)
		{
			Graph<T> *p = (*_storage)[i];
			if (data == p->getGraphPoint())
				return i;
		}
		return -1;
	}
	void freeGraphStorage()
	{
		int max = _storage->size();
		for (int i = 0; i < max; ++i)
		{
			Graph<T> *p = (*_storage)[i];
			std::cout << p->getGraphPoint() << std::endl;
			delete p;
		}
	}
	void fileRead(std::string fileName)
	{
		std::ifstream file(fileName);
		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string a, b;
			if (!(iss >> a >> b)) { continue; } // error
			std::cout << a << " " << b << std::endl;
			addGraphPoint(a, b);
		}
	}
	std::vector<Graph<T>*>* getStorage()
	{
		return this->_storage;
	}
};

