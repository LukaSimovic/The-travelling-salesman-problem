#ifndef GRAF_H
#define GRAF_H


#include <iostream>
#include<string>
#include<fstream>
#include<utility>

class Node
{
public:
	int GetID() const
	{
		return id;
	}
	friend std::ostream& operator<<(std::ostream& os, Node& myNode);

private:
	static int ID;
	bool visited = false;
	int id=ID++;
};

struct lstNode
{
	Node* myNode;
	lstNode* next;
};


class Pair
{
public:
	Pair(Node* n1, Node* n2, int dist) : nod1_(n1), nod2_(n2), dist_(dist) {}

	friend std::ostream& operator << (std::ostream & os, Pair& p);
public:
	Node* nod1_, *nod2_;
	int dist_;
};


class List
{
public:

	List()
	{
		head = last = nullptr;
	}
	List(const List&) = delete;
	List(List&&) = delete;
	List& operator = (const List&) = delete;
	List& operator = (List&&) = delete;
	~List();

	bool isInList(lstNode* newNode);
	bool Dodaj(lstNode* newNode);
	bool Izbaci(Node* outNode);


	lstNode* GetHead()
	{
		return head;
	}


	friend std::ostream& operator<<(std::ostream& os, List& myList);

private:
	lstNode* head, * last;
};

class Graph
{
public:

	int Dist(int, int);

	List** niz;
	int size;
	Pair** pairs;
	Node* operator [](int);
};

std::pair<int,int*> Permutacije(Graph&, int);
std::pair<int, int*> Permutacije(Graph& myGraph, int myNode, int& border,int it);

bool Povezi(Graph& myGraph, int ind1, int ind2);
bool DodajGranu(Graph& myGraph);
void Ispis(Graph& myGraph);
void BrisiGraf(Graph& myGraph);
void Init(Graph& myGraph);
lstNode* GetNode(Graph& myGraph, Node* pom);
int CalcDist(int*, Graph&);
int CalcDist(int* IDs, Graph& myGraph, int border);
void Kopiraj(int*, int*,int);

#endif GRAF_H