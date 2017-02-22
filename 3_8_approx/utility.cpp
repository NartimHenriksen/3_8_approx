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

