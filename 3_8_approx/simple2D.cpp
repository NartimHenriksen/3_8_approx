// 3_8_approx.cpp :Defines the entry point for the console application.
//

#include "stdafx.h"


#include "utility.h"

using namespace std;

/******		Vector Functions	******/
template<class T>
vector<T> concatenate(vector<T> a, vector<T> b) {
	b.insert(b.begin(), a.begin(), a.end());
	return(b);
}
template <class T>
vector<T> subset(vector<T> v, int first, int last) {
	vector<T>::const_iterator f = v.begin() + first;
	vector<T>::const_iterator l = v.begin() + 1 + last;
	return (vector<T>(f, l));
}


/******		Declared Functions		******/
string normal_form(vector<bool> seq, int matches, string udlr, bool odds);
string make_loop(int gap, char f, char inc, char dec);






/******		Simple 2d-fold		******/
void count_h_parity(vector<bool> seq, vector<bool> &even, vector<bool> &uneven, int &e, int &o) {//can be modified ot return bool vectors
	for (int i = 0; i < seq.size(); i++) {
		if (seq[i]) {
			if (i % 2 == 0) {
				even[(i + 1) / 2] = 1;// i/2 rounded up
				e++;
			}
			else {
				uneven[i / 2] = 1;// i/2 rounded down
				o++;
			}
		}
	}

	return;
}
string make_loop(int gap, char f, char inc, char dec) {


	string incstr = string(gap, inc);
	string decstr = string(gap, dec);

	return(incstr + f + decstr + f);

}
string make_cusp(vector<bool> seq, string udlr) {

	
	//find next H that can be matched
	int next_h = 3;
	while (!seq[next_h]) {
		if (next_h + 2 >= seq.size()) {
			std::cout << "couldnt match anything after cusp?? better have a look at this" << endl;
			return "";
		}
		else { next_h += 2; }

	}
	int gap = (next_h / 2 - 1);



	char inc = udlr[0];
	char dec = udlr[1];
	char f = udlr[3];
	char b = udlr[2];
	string incstr = string(gap, inc);
	string decstr = string(gap, dec);

	return(incstr + f + decstr + dec + b);

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
			if (i + 3<j)
				i += 2;
			else { return(matchings); }
		}
		while (!seq[j]) {
			if (i + 3 < j)
				j -= 2;
			else
				return(matchings);
		}
		if (j - i > 1) {
			matchings++;
		}

		i += 2;
		j -= 2;

	}
	return (matchings);
}
string normal_form(vector<bool> seq, int matches, string udlr, bool odds) {
	if (seq.empty()||seq.size()==1)
		return "";
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
	else if (seq[0]) { placed++; }
	int i = 1;

	while (placed < matches) {
		if (seq[2 * i + (odds ? 1 : 0)]) {
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



//clean up. Put run and ufold and the commented part of main() into one function called old_fold or something
string ufold(vector<bool> seq, int oematches, int eomatches, string udlr) //make u-fold
{
	bool oecase = oematches > eomatches;


	//1 put matched number of H on the surface
	int matches = (oecase ? oematches : eomatches);
	string fold = normal_form(seq, matches, udlr, oecase);
	//2 make the cusp

	int used = fold.length();//not +1 since last fold-char does not consume a bool
	vector < bool >::const_iterator first = seq.begin() + used;
	vector < bool >::const_iterator last = seq.end();

	vector<bool> step2 = vector<bool>(first, last);
	fold += make_cusp(step2, udlr);

	used = fold.length();
	first = seq.begin() + used;
	last = seq.end();
	vector<bool> step3(first, last);


	//3
	char c[4] = { udlr[1],udlr[0],udlr[3],udlr[2] };
	fold += normal_form(step3, matches, c, false);// think its always 'even' on second part
	
	//4 leftovers
	int leftovers = seq.size() - 1 - fold.length();
	string appendix = string(leftovers, udlr[2]);
	fold += appendix;
	return (fold);
}

string simple2D(string input) {

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

	string my_ufold = ufold(seq, oe, eo, "udlr");
	return(my_ufold);

}

//int func(int x) {
//	return int(sqrt(x));
//}
/*string simple3dfold(vector<bool> seq, int oematches, int eomatches, string udlrfb) {
	/*-------------- 2d method body--------*/
	/*bool oecase = oematches > eomatches;


	//1 put matched number of H on the surface
	int matches = (oecase ? oematches : eomatches);
	string fold = normal_form(seq, matches, udlr, oecase);
	//2 make the cusp

	int used = fold.length();//not +1 since last fold-char does not consume a bool
	vector < bool >::const_iterator first = seq.begin() + used;
	vector < bool >::const_iterator last = seq.end();

	vector<bool> step2 = vector<bool>(first, last);
	fold += make_cusp(step2, udlr);

	used = fold.length();
	first = seq.begin() + used;
	last = seq.end();
	vector<bool> step3(first, last);


	//3
	char c[4] = { udlr[1],udlr[0],udlr[3],udlr[2] };
	fold += normal_form(step3, matches, c, false);// think its always 'even' on second part

												  //4 leftovers
	int leftovers = seq.size() - 1 - fold.length();
	string appendix = string(leftovers, udlr[2]);
	fold += appendix;
	return (fold);
	*/

	//3d to do:
	/*
		no of mathcings
		layer length
		reverse strand 1
		fold by layer until we run out of matchings on each strand.
			Need to decide if we use old or new layer switch strat.
			need to decide on coordinate system
	*/


//}



vector<int> sim3d_pairings(vector<bool> seq, bool eo){
	int i, j;
	if (eo) {
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
	vector<int> pairings(3);

	while (i < j) {
		while (!seq[i]) {
			if (i + 3<j)
				i += 2;
			else { return(pairings); }
		}
		while (!seq[j]) {
			if (i + 3 < j)
				j -= 2;
			else
				return(pairings);
		}
		if (j - i > 1) {
			pairings[0]++;
			pairings[1] = i;
			pairings[2] = j;
		}

		i += 2;
		j -= 2;

	}

	return pairings;
}


string make_strand(vector<bool> seq, int pairings, int j, bool wrap, string udlrfb) {
	int n = seq.size();
	char inc, dec, forw, back;
	inc = udlrfb[0];
	dec = udlrfb[1];
	string res = "";
	//is guaranteed to begin with a 1
	//first one is automatically done
	int lasth = 0;
	pairings -= 1;

	for (int a : seq) {
		cout << a << " ";
	}
	int iter = 0;
	int layercounter = 0;
	int gap;

	//begin with right
	int direction = 3;
	forw = udlrfb[3];
	back = udlrfb[2];
	while (pairings > 0) {
		//find next even H





		while (seq[iter+=2] != 1) {}//check iter then add
		//found

		layercounter++;
		if (layercounter < j) { //normal loop
			gap = iter - lasth;
			lasth = iter;
			res+=make_loop((gap/2)-1,forw, inc, dec);
			pairings--;

		}
		else { //time for layer stuff
			//if less than 8 then finish

			//otherwise add all 8, set iter and lasth and pairings and reset layercounter and wrap
			//else switch layer depending on wrap and flip wrap flag. Also switch direction and reset layercounter
			if (wrap) {
			//do the wrap

				/*ok motherfucks lets try the new better version its easier anyway*/
				/*do as much wrap as possible*/
				char arr[9] = {forw,dec,dec,back,udlrfb[4],back,inc,back,'\0'};
				string wrap(arr);

				if (n - 1 - iter < 8 ){
					//append the first n-1-iter chars of the wrap then return it
					wrap.erase(n-1-iter, 8-(n-1-iter));//i dont think n-1-iter can ever be 0 but be aware of it.

					//iter += wrap.length();
					res += wrap;
					return(res);
					cout << "HEER BITC: " << n << " " << iter << " " << n-1-iter << wrap.length() << endl;
				}
				else {
					res += wrap;
					///
					int skipped = seq[iter + 2]+seq[iter+4]+seq[iter+6];
					if (seq[iter + 6])
						lasth = iter + 6;
					else if (seq[iter + 4])
						lasth = iter + 4;
					else if (seq[iter + 2])
						lasth = iter + 2;

					pairings -= skipped;
					cout << "skipped: " << skipped;
					iter += wrap.length();
				}
			}
			
			else {
			//do the "tunnel"
				char arr[5] = { udlrfb[4],dec,back,back,'\0' };
				if (n - 1 - iter < 4) {
					//append the first n-1-iter chars
					string wrap(arr);
					wrap.erase(n - 1 - iter, 4 - (n - 1 - iter));//i dont think n-1-iter can ever be 0 but be aware of it.
					res += wrap;
					return(res);
				}
				else {
					string wrap(arr);
					res += wrap;

					if (seq[iter + 2])
						lasth = iter + 2;


					int skipped = seq[iter + 2];
					pairings -= skipped;
					cout << "skipped: " << skipped;
					iter += wrap.length();
				}
			}
			char temp;
			temp = forw;
			forw = back;
			back = temp;
			
			temp = inc;
			inc = dec;
			dec = temp;
		
			layercounter = 0;
			wrap = !wrap;
		}

		//check if pairings is 0
		



	}
	return res;
}

string simple3D(string input){

	
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
	vector<int> eo;
	eo.reserve(3);
	vector<int> oe;
	oe.reserve(3);
	eo = sim3d_pairings(seq, true);
	oe = sim3d_pairings(seq, false);
	

	//pairings are vectors of <no of pairings, last paired in first half, first paired in last half>
	vector<int> pairing = (oe[0] > eo[0] ? oe : eo);
	
	int k = func(pairing[0]);
	int j = (pairing[0] - 2 * k + 1) / k;
	//tests for subroutine
	//cout << n << endl;
	cout << pairing[0] << " " << pairing[1] << " " << pairing[2] << " " << k << " " << j << " " << seq.size() << " ";
	
	//start by folding part 2 then do reverse thing. Check with simple 2d normalform
	

	vector<bool> strand1 = reverse_vector(subset(seq, 0, pairing[1]));
	vector<bool> strand2 = subset(seq, pairing[2], seq.size()-1);
	
	string fold1 = make_strand(strand1,pairing[0],j,false,"DURLBF"); //lol just reverse arg letters for translation
	string f1rev(fold1.rbegin(), fold1.rend());

	//try faster translation if there is a way
	//std::replace(fold1.begin(), fold1.end(), 'U', 'x');
	//std::replace(fold1.begin(), fold1.end(), 'L', 'y');
	//std::replace(fold1.begin(), fold1.end(), 'F', 'z');


	int distance = pairing[2] - pairing[1];
	string middle = string((distance - 1) / 2,'B')+"D" + string((distance - 1) / 2,'F');

	string fold2 = make_strand(strand2, pairing[0], j, true, "DULRFB");
	
	return(f1rev+middle+fold2);


	//return(fold1+middle+fold2);
	//return(ThreeDfold);

	//string res
	//best=eo or oe based on eo[0] and oe[0]
	//res=makestrand(seq[0-best[1]],best[0],j,true.udlrfb)
	//res+=foldmiddlepiece(seq[best[1], best[2])
	//res+=makstrand(seq[best[2]-n,best[0],j,false,dulrfb])
	//test 2nd part first
}


