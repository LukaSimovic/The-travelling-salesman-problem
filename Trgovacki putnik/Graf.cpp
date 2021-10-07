#include "Graf.h"
#include<cstdlib>
#include<algorithm>


int Node::ID = 0;

int Graph::Dist(int id1, int id2)
{
	int NumPair = (size * (size - 1)) / 2;
	for (int i = 0; i < NumPair; i++)
	{
		if ((pairs[i]->nod1_->GetID() == id1 && pairs[i]->nod2_->GetID() == id2) || (pairs[i]->nod1_->GetID() == id2 && pairs[i]->nod2_->GetID() == id1))
			return pairs[i]->dist_;
	}
	return 0;
}

Node* Graph::operator[](int index)
{
	return niz[index]->GetHead()->myNode;
}



std::ostream& operator<<(std::ostream& os, Node& myNode)
{
	os << "Node[ " << myNode.id << "] ";
	return os;
}

std::ostream& operator<<(std::ostream& os, Pair& p)
{
	os << *p.nod1_ << " " << *p.nod2_ << ", dist: " << p.dist_<<std::endl;
	return os;
}


std::ostream& operator<<(std::ostream& os, List& myList)
{
	lstNode* pom = myList.head;
	while (pom)
	{
		os << *(pom->myNode) << " ---> ";
		pom = pom->next;
	}
	return os;
}

bool Povezi(Graph& myGraph, int ind1, int ind2)
{
	if (ind1 >= 0 && ind1 < myGraph.size && ind2 >= 0 && ind2 < myGraph.size && ind1 != ind2)
	{
		lstNode* tmp = new lstNode();
		tmp->myNode = myGraph.niz[ind1]->GetHead()->myNode;
		myGraph.niz[ind2]->Dodaj(tmp);
		tmp = new lstNode();
		tmp->myNode = myGraph.niz[ind2]->GetHead()->myNode;
		myGraph.niz[ind1]->Dodaj(tmp);
		return true;
	}
	else
		return false;
}

bool DodajGranu(Graph& myGraph)
{
	int i = -1, j = -1;
	std::cout << "Unesite indekse izmedju kojih dodajete granu: ";
	std::cin >> i >> j;
	if (Povezi(myGraph, i, j))
	{
		return true;
	}
	else
		return false;
}

void Ispis(Graph& myGraph)
{
	if (myGraph.size == 0)
		std::cout << "Nema cvorova!\n";
	else
	{
		for (int i = 0; i < myGraph.size; i++)
		{
			std::cout << "Indeks: " << i << ": " << *myGraph.niz[i] << std::endl;
		}
	}
}


void BrisiGraf(Graph& myGraph)
{
	for (int i = 0; i < myGraph.size; i++)
	{
		delete myGraph.niz[i];
	}
	myGraph.size = 0;
}

void Init(Graph& myGraph)
{
	BrisiGraf(myGraph);
	int n;
	std::cout << "Unesite broj cvorova grafa:\n";
	std::cin >> n;
	if (!(n > 0))
	{
		std::cin.clear();
		std::cin.ignore();
		n = 1;
	}
	myGraph.size = n;
	myGraph.niz = (List**)realloc(myGraph.niz, n * (sizeof(List*)));
	int NumPair = (n * (n - 1)) / 2;
	for (int i = 0; i < n; i++)
	{
		myGraph.niz[i] = new List();
		lstNode* tmp = new lstNode();
		tmp->myNode = new Node();
		myGraph.niz[i]->Dodaj(tmp);
	}
	myGraph.pairs = new Pair * [NumPair];
	int ind = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (Povezi(myGraph, i, j))
			{
				myGraph.pairs[ind] = new Pair(myGraph[i], myGraph[j], rand()%100 + 1);

				std::cout << *myGraph.pairs[ind++];
			}
		}
	}
}

lstNode* GetNode(Graph& myGraph, Node* pom)
{
	for (int i = 0; i < myGraph.size; i++)
		if (myGraph[i] == pom)
			return myGraph.niz[i]->GetHead();
	return nullptr;
}



List::~List()
{
	while (head)
	{
		lstNode* old = head;
		head = head->next;
		delete old;
	}
}

bool List::isInList(lstNode* newNode)
{
	lstNode* pom = head;
	while (pom)
	{
		if (pom->myNode == newNode->myNode)
			return true;
		pom = pom->next;
	}
	return false;
}

bool List::Dodaj(lstNode* newNode)
{
	if (!isInList(newNode))
	{
		if (newNode)
		{
			if (!head)
				head = newNode;
			else
				last->next = newNode;
			last = newNode;
			return true;
		}
	}
	return false;
}

bool List::Izbaci(Node* outNode)
{
	lstNode* pom = head;
	lstNode* tek = nullptr;
	while (pom)
	{
		if (pom->myNode == outNode)
		{
			if (pom == head)
			{
				head = head->next;
			}
			else
			{
				if (pom == last)
					last = tek;
				tek->next = pom->next;
			}
			pom->next = nullptr;
			return true;
		}
		tek = pom;
		pom = pom->next;
	}
	return false;
}


int CalcDist(int* IDs, Graph& myGraph)
{
	int put = 0;
	for (int i = 0; i < myGraph.size - 1; i++)
	{
		put += myGraph.Dist(IDs[i], IDs[i + 1]);
	}
	return put;
}
int CalcDist(int* IDs, Graph& myGraph, int border)
{
	int put = 0;
	for (int i = 0; i < myGraph.size - 1; i++)
	{
		put += myGraph.Dist(IDs[i], IDs[i + 1]);
		if (put > border) return -1;
	}
	return put;
}


void Kopiraj(int* a, int* b, int n)
{
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}
}


std::pair<int,int*> Permutacije(Graph& myGraph, int myNode)
{
	int perm = 1;
	int *IDs = new int[myGraph.size];
	List* Poc = myGraph.niz[myNode];
	for (int i = 1; i < myGraph.size; i++)
		perm *= i;

	int min=-1;
	lstNode *pom=Poc->GetHead();
	int ind = 0;
	int * validPut= new int[myGraph.size];
	while (pom)
	{
		IDs[ind]=pom->myNode->GetID();
		pom = pom->next;
		ind++;
	}
	int temp;

	do
	{
		for (int i = 0; i < myGraph.size; i++)
		{
			std::cout << IDs[i] << " ";
		}
		std::cout << std::endl;
		temp = CalcDist(IDs, myGraph);
		std::cout << "Dist: " << temp <<std::endl;
		if (min == -1 || min > temp) {
			min = temp; Kopiraj(validPut, IDs, myGraph.size);
		}

	} while (std::next_permutation(IDs + 1, IDs + myGraph.size));

	std::pair <int, int* > a(min, validPut);
	
	return a;
}

std::pair<int, int*> Permutacije(Graph& myGraph, int myNode,int& border,int it)
{
	int perm = 1;
	int* IDs = new int[myGraph.size];
	List* Poc = myGraph.niz[myNode];
	for (int i = 1; i < myGraph.size; i++)
		perm *= i;

	int min = -1;
	lstNode* pom = Poc->GetHead();
	int ind = 0;
	int* validPut = new int[myGraph.size];
	while (pom)
	{
		IDs[ind] = pom->myNode->GetID();
		pom = pom->next;
		ind++;
	}
	int temp;

	do
	{
		for (int i = 0; i < myGraph.size; i++)
		{
			std::cout << IDs[i] << " ";
		}
		std::cout << std::endl;
		temp = CalcDist(IDs, myGraph,border);
		std::cout << "Dist ";
		if(temp==-1)
			std::cout<< "> "<<border << std::endl;
		else
		{
			std::cout << ": " << temp << std::endl;
			if (min == -1 || min > temp) {
				min = temp; Kopiraj(validPut, IDs, myGraph.size);
			}
			if (min != -1 && min < border) {
				border = min; it--; 
				std::cout << "\nNadjena prva iteracija:\n";
				system("Pause");
			}
		}
	} while (std::next_permutation(IDs + 1, IDs + myGraph.size)&&it);

	std::pair <int, int* > a(min, validPut);

	return a;
}