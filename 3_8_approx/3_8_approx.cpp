// 3_8_approx.cpp :Defines the entry point for the console application.
//

#include "stdafx.h"
/*
#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/int/branch.hh>
*/

#include <vector>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>

using namespace std;


void brake() {
	std::cout << "Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}


void count_h_parity(vector<bool> seq, vector<bool> &even, vector<bool> &uneven,int &e, int &o) {//can be modified ot return bool vectors
	for (int i = 0; i < seq.size();i++) {
		if (seq[i]) {
			if (i % 2 == 0) {
				even[(i+1)/2]=1;// i/2 rounded up
				e++;
			}
			else {
				uneven[i/2]=1;// i/2 rounded down
				o++;
			}
		}
	}

	return;
}

vector<bool> treat_input(string s) {
	//check if HP
	bool well_formed = true;
	for (char c : s) {
		if (c != 'P'&&c != 'p'&&c != 'H'&&c != 'h')
			well_formed = false;

	}
	if (well_formed) {
		cout << "input is a valid HP string" << endl;
	}
	else {
		cout << "input is NOT a valid HP string" << endl;
		return(vector<bool>{NULL});
	}

	//make a bool array
	size_t size = s.length();
	vector<bool> v(size);

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'H' || s[i] == 'h') {
			v[i] = 1;
		}
	}
	return v;
}
int main()
{
	string input;



	//cout << "Bring me a string!" << endl;
	//getline(cin, input);
	cout << "Automatic string = hhhhhhhhhhhhphphpphhpphhpphpphhpphhpphpphhpphhpphphphhhhhhhhhhhh" << endl;
	input = "hhhhhhhhhhhhphphpphhpphhpphpphhpphhpphpphhpphhpphphphhhhhhhhhhhh";
	vector<bool> seq=treat_input(input);
	int n = seq.size();
	for (bool b: seq) {
	
		cout << b;
	}
	cout << endl;
	vector<bool> even((n+1)/2); //to get index in original: multiply index by 2
	vector<bool> odd(n/2); //to get index in original: multiply index by 2 and add 1
	int e = 0;
	int o = 0;

	count_h_parity(seq,even, odd,e,o);
	brake();
	cout << "Even: ";
	for (auto i = even.begin(); i != even.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	cout << " Odd: ";
	for (auto i = odd.begin(); i != odd.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	
	cout << e << " evens and " << o << " odds. Can find a matching of at least " << (e<o? e/2 : o/2) << endl;

	int eo=0;
	int oe=0;
	for (int i = odd.size() - 1; (odd.size()-1-i)*2 <i*2+1; i--) {
	//even is sometimes 1 longer. When this is the case, we cannot match last even. Therefore counting backwards from odds should give correct result each time
		if (odd[i] && even[(odd.size() - 1) - i]) { //even index is odds index 'reversed'. In cases with unequal length, last element of even is not accessed.
			eo++;
		}
	}
	for (int i = even.size()-1; (even.size() - 1 - i)*2+1 < i*2; i--) {
	//always ignoring first even and ignoring last odd when equal length (draw on paper to understand)
		if (even[i] && odd[even.size() - 1 - i]){
			oe++;
		}
	}
	//this matching method is correct, but ugly AF

	cout << "eo matches: " << eo << endl;
	cout << "oe matches: " << oe << endl;

	return(brake(),0);

}