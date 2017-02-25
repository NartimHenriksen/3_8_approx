#include "utility.h"
#include "stdafx.h"
#include <vector>



#include <iostream>

void brake() {
	std::cout << std::endl << "Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}
std::string hp_gen(const int length) {
	std::string s(length, 'h');
	for (int i = 0; i < length; i++) {
		if (rand() % 2 == 0) {
			s[i] = 'p';
		}

	}
	return(s);
}


template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}

void visualize3D(std::string inp, std::string fold) {
	//*** By Chrisitan Nørgaard storm***//
	std::string filename = "hpview3D.py";
	std::string command = "python " + filename + " " + inp + " " + fold;
	system(command.c_str());

}