#include <iostream>
#include <fstream>
#include "GraphStorage.hpp"

template<class T>
class BFS
{
private:
	Graph<T> *place1;
	Graph<T> *place2;
	int _level;
	std::vector<std::vector<Graph<T>*>*> *listOfGraph;
public:
	BFS(GraphStorage<T> *p, T& place1, T& place2) : _level(0), listOfGraph(new std::vector<std::vector<Graph<T>*>*>())
	{
		int num1 = p->findElemenet(place1);
		int num2 = p->findElemenet(place2);
		if (num1 == -1 || num2 == -1)
			throw "Place of exceptions";
		std::vector<Graph<T>*> *storagep = p->getStorage();
		this->place1 = (*storagep)[num1];
		this->place2 = (*storagep)[num2];
		auto *graph = new std::vector<Graph<T>*>();
		graph->push_back(this->place1);
		listOfGraph->push_back(graph);
		std::cout << "BFS const" << std::endl;
	}
	~BFS()
	{
		reset();
		delete listOfGraph;
		std::cout << "BFS dest" << std::endl;
	}
	int run()
	{
		for (int i = 0; i < listOfGraph->size(); ++i)
		{
			std::vector<Graph<T>*> *p = (*listOfGraph)[i];
			for(int j = 0; j < p->size(); ++j)
			{
				Graph<T> *graphp = (*p)[j];
				if (*place2 == *graphp)
					return i;
			}
		}
		throw "Exceptions";
	}
	void sortGraph()
	{
			std::vector<Graph<T>*> *p = (*listOfGraph)[_level];
			auto *actual = new std::vector<Graph<T>*>();
			int newElement = 0;
			for (int i = 0; i < p->size(); ++i)
			{
				Graph<T> *graphp = (*p)[i];
				std::vector<Graph<T>*> *qlistp = graphp->getNextPoints();
				for (int j = 0; j < qlistp->size(); ++j)
				{
					Graph<T> *p_graph = (*qlistp)[j];
					if (!(elementListOfGraph(p_graph)))
					{
						actual->push_back(p_graph);
						++newElement;
					}
				}
			}
			listOfGraph->push_back(actual);
			++_level;
			if (newElement > 0)
				sortGraph();
	}
	bool elementListOfGraph(Graph<T> *point)
	{
		for(int i = 0; i < listOfGraph->size(); ++i)
		{
			std::vector<Graph<T>*> *p = (*listOfGraph)[i];
			for(int j = 0; j < p->size(); ++j)
			{
				Graph<T> *graphp = (*p)[j];
				if ((*point) == (*graphp))
					return true;
			}
		}
		return false;
	}
	void reset()
	{
		_level = 0;
		int max = listOfGraph->size();
		for(int i = 0; i < max; ++i)
		{
			std::vector<Graph<T>*> *p = (*listOfGraph)[i];
			delete p;
		}
	}
};


int main()
{
	
	auto *graphstorege = new GraphStorage<std::string>();
	graphstorege->fileRead("Text.txt");
	std::string a, b;
	a = "Budapest";
	b = "Kecskemet";
	auto *bfs = new BFS<std::string>(graphstorege, a, b);
	std::cout << "Sorted #############" << std::endl;
	bfs->sortGraph();
	int run = bfs->run();
	std::cout << "#################" << std::endl << run << std::endl << "################" << std::endl;
	delete bfs;

	delete graphstorege;

	int q;
	std::cin >> q;
	return 0;
}
