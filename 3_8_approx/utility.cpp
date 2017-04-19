#include "utility.h"
#include "stdafx.h"
#include <vector>



#include <iostream>
using namespace std;
void brake() {
	std::cout << std::endl << "Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}
std::string hp_gen(const int length, const int p) { //length and prevalence of H
	std::string s(length, 'p');
	for (int i = 0; i < length; i++) {
		if (rand() % p == 0) {
			s[i] = 'h';
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

string absrev(string f,string udlr) {
	string res = f;
	for (int i = 0; i < res.size(); i++) {
		if (res[i] == 'u')
			res[i] = 'd';
		else if (res[i] == 'd')
			res[i] = 'u';
		else if (res[i] == udlr[0])
			res[i] = udlr[1];
		else if (res[i] == udlr[1])
			res[i] = udlr[0];

		else if (res[i] == udlr[2])
			res[i] = udlr[3];
		else if (res[i] == udlr[3])
			res[i] = udlr[2];
	}
	std::reverse(res.begin(), res.end());
	return res;
}
string rel2abs(string rel, string udlr) {
	string rdlu = string(1, udlr[3]) + udlr[1] + udlr[2] + udlr[0];
	int dir = 0;
	string res = "";
	for (char c : rel) {
		if (c == 'f') {
			res += rdlu[dir];
		}
		if (c == 'r') {
			dir = (dir + 1) % 4;
			res += rdlu[dir];
		}
		if (c == 'l') {
			dir = (dir+4 - 1) % 4;
			res += rdlu[dir];
		}if (c == 'u') {
			res += udlr[4];
		}if (c == 'd') {
			res += udlr[5];
		}
	}
	return res;

}
string abs2rel(string abs, string udlr) {
	string rdlu = string(1, udlr[3]) + udlr[1] + udlr[2] + udlr[0];
	string flr = "flr";

	int dir = 0;
	string res = "";
	int pint = 0;
	int cint=0;
	for (char c : abs) {
		if (c == 'u' || c == 'd') {
			res += c;
		}
		else {
			for (int i = 0; i < 4; i++) {
				if (rdlu[i] == c) {
					cint = i;
				}
			}
			if ((pint + 1) % 4 == cint) {
				res += flr[2];
			}

			if ((pint + 4 - 1) % 4 == cint) {
				res += flr[1];
			}
			if (pint == cint) {
				res += flr[0];
			}
			pint = cint;
		}

	}
	return res;

}