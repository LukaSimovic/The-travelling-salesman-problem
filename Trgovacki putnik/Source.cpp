#include<iostream>

#include "Graf.h"

int main()
{
	bool kraj = false;
	Graph OurGraph;
	OurGraph.size = 0;
	OurGraph.niz = (List**)calloc(1, sizeof(List*));
	Init(OurGraph);
	while (!kraj)
	{
		std::cout << "\nIzaberi metodu resavanja:"
			"\n1. D-ALGORITAM"
			"\n2. Heuristicka metoda"
			"\n0. Kraj rada"
			"\n\n Vas izbor? ";
		int izbor; std::cin >> izbor;
		int min = -1; int border;
		int* Ld = new int[OurGraph.size];
		std::pair <int, int* > mojPar(min, Ld);
		switch (izbor)
		{
		case 0: kraj = true; break;

		case 1:

			for (int i = 0; i < OurGraph.size; i++) {
				std::pair <int, int*> temp = Permutacije(OurGraph, i);
				if (temp.first < mojPar.first || mojPar.first == -1) mojPar = temp;
			}
			std::cout << "\n\nMinimum minimuma: " << mojPar.first << "\nZa redosled:\t";
			for (int i = 0; i < OurGraph.size; i++) {
				if (i != OurGraph.size - 1)
					std::cout << mojPar.second[i] << " -> ";
				else
					std::cout << mojPar.second[i] << std::endl;

			}
			break;
		case 2:
			int it;
			std::cout << "\nUnesite maksimalnu zeljenu vrednost puta: ";
			std::cin >> border;
			std::cout << "\nUnesite broj iteracija (ukoliko ne zelite iteracije upisite 1):";
			std::cin >> it;
			for (int i = 0; i < OurGraph.size; i++) {
				std::pair <int, int*> temp = Permutacije(OurGraph, i, border, it);
				if ((temp.first < mojPar.first&&temp.first!=-1) || mojPar.first == -1)
				{
					mojPar = temp;
				}
				if (i == OurGraph.size - 1)
					std::cout << "Resavanje se svelo na D-algoritam"<<std::endl;
			}
			std::cout << "\n\nDuzina puta: " << mojPar.first << "\nZa redosled:\t";
			for (int i = 0; i < OurGraph.size; i++) {
				if (i != OurGraph.size - 1)
					std::cout << mojPar.second[i] << " -> ";
				else
					std::cout << mojPar.second[i] << std::endl;

			}
			break;
		default:
			std::cout << "POGRESAN UNOS! IZABERITE OPET!\n ";
			break;
		}
	}
	system("pause");
	return 0;
}