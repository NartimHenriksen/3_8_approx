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
template<class T>
vector<T> concatenate(vector<T> a, vector<T> b) {
	b.insert(b.begin(),a.begin(), a.end());
	return(b);
}
template <class T>
vector<T> subset(vector<T> v, int first, int last) {
	vector<T>::const_iterator f = v.begin() + first;
	vector<T>::const_iterator l = v.begin() + 1+last;
	return (vector<T>(f,l));
}

void brake() {
	std::cout << endl << "Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}
bool cond(int a, int b, int A, int B) {
	return((a < b) || ((a = b) && (A < B)));
}

struct block {
	vector<bool> sequence;
	int size;
	int val;
	bool is_x;
	bool is_sep = false; //mb dont even need this when we have val

};
//true if it starts with x,false if it starts with y. They alternate so rest should be clear
bool first_label_x(vector<block> blocks) {
	int first=0;
	int second=0;
	for (int i = 1; i < blocks.size(); i += 4) {
		for (bool b : blocks[i].sequence) {
			if (b)
				first++;
		}
	}
	for (int i = 3; i < blocks.size(); i += 4) {
		for (bool b : blocks[i].sequence) {
			if (b)
				second++;
		}
	}
	if(first<second)
		return true;
	if (first == second) //if they are equal then X should have the most 1's in endpoints
	{
		if (blocks[0].size == 0)//first block has an endpoint so x can be there
			return true;
		else
			return (blocks.size() % 4 == 3); //This is true when last block has same parity as first block, and false otherwise
			
	}	
	else
		return false;
}
void label_blocks(vector<block> &blocks) {
	bool next_label = first_label_x(blocks);
	for (int i = 1; i < blocks.size(); i += 2) {
		blocks[i].is_x = next_label;
		next_label = !next_label;
	}
}
//int show how many 0 are in the block sepators, or how many 1s in the blocks.

block make_block(vector<bool> seq, bool is_x) {//just constructor for the block
	block res;
	res.is_x = is_x;
	res.sequence = seq;
	int v = 0;
	for (bool b : seq) {
		if (b)
			v++;
	}
	res.val = v;
	res.size = seq.size();
	res.is_sep = (res.val == 0); 
	


	return res;
}

block make_block(vector<bool> seq) {//just constructor for the block
	block res;
	res.sequence = seq;
	int v = 0;
	for (bool b : seq) {
		if (b)
			v++;
	}
	res.val = v;
	res.size = seq.size();
	res.is_sep = (res.val == 0);



	return res;
}
vector<block> blockify(vector<bool> seq) {
	vector<block> blocks= vector<block>();
	int i = 0;
	while (!seq[i]) {
		i++;
	}
	block supp = make_block(vector<bool>(i, false));
	blocks.push_back(supp);

	int j = 0;
	while (i <= seq.size() - 1) {
		j = i + 1;
		while (! ( j == seq.size() || (seq[j] && (j - i) % 2 == 1)))
		{ j++; } //"until seq[j] is 1 AND distance to i is uneven"
		//count block 0 that separate them
		int z = 0;

		while (seq[j - z - 1] == 0) {
			z += 1;
		}

		blocks.push_back(make_block(subset(seq, i, j - 1-z)));
		blocks.push_back(make_block(vector<bool>(z,false)));
		i = j;
				

	}
	return blocks;
	
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
	//	cout << "input is a valid HP string" << endl;
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
/*std::vector<bool> reverse_vector(std::vector<bool>v)
{
	std::reverse(v.begin(), v.end());
	return v;
}*/
string make_loop(int gap, char f, char inc, char dec) {

	
	string incstr = string(gap, inc);
	string decstr = string(gap, dec);

	return(incstr + f + decstr + f);

}
   /*
	*	seq = boolvector to start the NF from
	*	matches = number of H to put in the 'surface'
	*	udlr = alphabet to use in the fold output. default is "udlr" for "up, down, left, right"
	*	used = reference for the function to pass back how many bools it consumed from seq
	*	odds = true iff we are matching odds. Turned out to be nessecary
	*/	
string normal_form(vector<bool> seq, int matches, string udlr, bool odds) {
	
	char f = udlr[3];
	char inc = udlr[0];
	char dec = udlr[1];
	//check first one manually since we dont need to fold it. Then start from i=1
	int placed = 0;
	int gap = 0;
	string fold = "";
	if (odds) {
		fold += f;
		if (seq[1])
			placed++;
	}
	else if(seq[0]) {placed++;}
	int i = 1;

	while (placed < matches) {
		if (seq[2 * i+(odds?1:0)]) {
			fold += make_loop(gap, udlr[3], udlr[0], udlr[1]);
			placed++;
			i++;
			gap = 0;
		}
		else {
			gap++;
			i++;
		}
	}
	return(fold);

}
string make_cusp(vector<bool> seq, string udlr) {
	
	if (seq[1]) {
		std::cout << "Cusp had a match in it." << endl;
	}
	//find next H that can be matched
	int next_h=3;
	while (!seq[next_h]) {
		if (next_h + 2 >= seq.size()) {
			std::cout << "couldnt match anything after cusp?? better have a look at this" << endl;
			return "";
		}
		else { next_h += 2; }

	}
	int gap= (next_h/2 -1);
	


	char inc = udlr[0]; 
	char dec = udlr[1];
	char f = udlr[3];
	char b = udlr[2];
	string incstr = string(gap, inc);
	string decstr = string(gap, dec);

	std::cout << "cusp  gap: " << gap << endl;
	return(incstr + f + decstr + dec+b);
	
}
string ufold(vector<bool> seq, int oematches, int eomatches, string udlr) //make u-fold
{
	bool oecase = oematches > eomatches;


	//1 put matched number of H on the surface
	int matches = (oecase ? oematches : eomatches);
	string fold = normal_form(seq, matches, udlr,oecase); 
	//2 make the cusp

	int used = fold.length();//not +1 since last fold-char does not consume a bool
	vector < bool >::const_iterator first = seq.begin() + used;
	vector < bool >::const_iterator last = seq.end();
	
	vector<bool> step2 = vector<bool>(first, last);
	fold += make_cusp(step2,udlr);

	used = fold.length();
	first = seq.begin()+used;
	last = seq.end();
	vector<bool> step3(first,last);
	
	cout << "Step 3 (after cusp) begins with; ";
	for (bool b : step3) {
		cout << b;
	}
	cout << endl;

	//3
	char c[4] = { udlr[1],udlr[0],udlr[3],udlr[2] };
	try
	{
		fold += normal_form(step3, matches, c, false);// think its always 'even' on second part
	}
	catch (int e)
	{
		cout << "Exeption in second NF. Refolding with -1. Exception number: " << e << '\n';
		fold += normal_form(step3, matches-1, c, !oecase);// do full and redo with -1 if exception
	}
	//4 leftovers
	int leftovers = seq.size() - 1 - fold.length();
	string appendix = string(leftovers, udlr[2]);
	fold += appendix;
	return (fold);
}
int matchings(vector<bool> seq, bool evenodd) {
		
	int i;
	int j;
	if (evenodd) {
		//i is first even and j is last odd
		i = 0;
		if (seq.size() % 2 == 0)
			j = seq.size() - 1;
		else
			j = seq.size() - 2;
	}
	else {//odd-even
		i = 1; 
		if (seq.size() % 2 == 0)
			j = seq.size() - 2;
		else
			j = seq.size() - 1;
	}
	int matchings = 0;

	while (i < j) {
		while (!seq[i]) {
			if(i+2<j)
				i += 2;
			else { return(matchings); }
		}
		while (!seq[j]) {
			if (i + 2 < j)
				j -= 2;
			else
				return(matchings);
		}
		if (j - i > 1) {
			matchings++;	
		}
		else if (j - i == 1) {
			cout << "matched pair were neighbours" << endl;
		}
		else { cout << "Wait, what?" << endl; }

		i += 2;
		j -= 2;
		
	}
	return (matchings);
}
int subroutine1(vector<bool> seq) {
	vector<block> blocks = blockify(seq);
	//bool labels = first_label_x(blocks);

	//vector<vector<bool>> B1= subset(blocks, 0, 2);
	//vector<vector<bool>> B2 = subset(blocks, 3, blocks.size()-1);
	return 0;

}

string run(string input) {

	vector<bool> seq = treat_input(input);
	int n = seq.size();

	int H_e = 0;
	int H_o = 0;
	for (int i = 0; i < seq.size(); i++) {
		if (seq[i]) {
			if (i % 2 == 0) {
				H_e++;
			}
			else {
				H_o++;
			}
		}
	}
	int all_e = (n + 1) / 2;
	int all_o = n / 2;

	int eo = 0;
	int oe = 0;
	

	eo = matchings(seq, true);
	oe = matchings(seq, false);
	cout << "even/odd matches: " << eo << endl;
	cout << "odd/even matches: " << oe << endl;

	string my_ufold = ufold(seq, oe, eo, "udlr");
	cout << my_ufold << endl;
	return(my_ufold);

}
int main()
{
	string inps[] = {
		"hhppppphhppphppphp",
		"hphphhhppphhhhpphh",
		"phpphphhhphhphhhhh",
		"hphpphhphpphphhpphph",
		"hhhpphphphpphphphpph",
		"hhpphpphpphpphpphpphpphh",
		"pphpphhpppphhpppphhpppphh",
		"ppphhpphhppppphhhhhhhpphhpppphhpphpp",
		"pphpphhpphhppppphhhhhhhhhhpppppphhpphhpphpphhhhh",
		"hhphphphphhhhphppphppphpppphppphppphphhhhphphphphh",
		"pphhhphhhhhhhhppphhhhhhhhhhphppphhhhhhhhhhhhpppphhhhhhphhphp",
		"hhhhhhhhhhhhphphpphhpphhpphpphhpphhpphpphhpphhpphphphhhhhhhhhhhh",
		"hhhhpppphhhhhhhhhhhhpppppphhhhhhhhhhhhppphhhhhhhhhhhhppphhhhhhhhhhhhppphpphhpphhpphph",
		"pppppphphhppppphhhphhhhhphhpppphhpphhphhhhhphhhhhhhhhhphhphhhhhhhppppppppppphhhhhhhpphphhhpppppphphh",
		"ppphhpphhhhpphhhphhphhphhhhpppppppphhhhhhpphhhhhhppppppppphphhphhhhhhhhhhhpphhhphhphpphphhhpppppphhh"};

	/*
	for (string inp : inps) {
		string fold=run(inp);
		
		std::string filename = "hpview.py"; //use path relative in project i guess
		std::string command = "python "+filename+ " " + inp + " "+ fold;
		system(command.c_str());
	}
	*/
	for (string s: inps) {
		cout << s << endl;
		vector<block>blocks = blockify(treat_input(s));
		label_blocks(blocks);
		for (block b : blocks) {
			cout << (b.is_sep ? "SEP: " : (b.is_x ? "  X: " : "  Y: "));
			for (bool ba : b.sequence) { cout << ba; }

			cout << endl;
			cout << "Size: " << b.size << " Val: " << b.val << endl;

		}
	}

	cout << endl;

	
	cout << endl;

	return(brake(),0);

}