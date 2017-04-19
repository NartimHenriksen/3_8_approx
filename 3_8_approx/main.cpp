#include "stdafx.h"
#include "utility.h"
using namespace std;


void scoresTest(int p) { //outputs length, seq and folds to foldout.txt. Handled by Score_calc.py

	
	ofstream dfoldout;

	dfoldout.open("foldout.txt", ios::app);
	for (int i = 200; i < 201; i += 1000) {
		string t = hp_gen(i, p);
		dfoldout << t.length() << " " << t << " " << simple2D(t) << " " << block2DA(t) << " " << block3D(t, "UDLRFB",false) << endl;
	}
	dfoldout.close();
}
void runTest(int p) {//50 iterations to smoothen curve. Can be plotted directly. remember to let it work


	ofstream out;

	out.open("times.txt", ios::app);
	out << "Length " << "Algorithm1 " << "Algorithm2 " << "Algorithm3" << endl;
	for (int i = 1000; i < 100000; i += 1000) {
		string t = hp_gen(i,p);
		int iter = 50;


		double time_2d_ms = time_any(iter, t, simple2D) / iter;
		double time_b2da_ms = time_any(iter, t, block2DA) / iter;
		double time_b3d_ms = time_any(iter, t, block3D) / iter;

		cout << i << " " << time_2d_ms << " " << time_b2da_ms << " " << time_b3d_ms << endl;

		out << i << " " << time_2d_ms << " " << time_b2da_ms << " " << time_b3d_ms << endl;
	}
	out.close();

}
void sabTest(int p) {
	for (int i = 1000; i < 100000; i += 1000) {
							//logdata outputs to 3Ddata.txt, folds to 3Dfolds.txt
		string t = hp_gen(i, p);//Both files are to be handled by lol.py
		string block3f = block3D(t, "UDLRFB", true);
		ofstream foldout;
		foldout.open("3Dfolds.txt", ios::app);
		foldout << t.length() << " " << t << " " << block3f << endl;
		foldout.close();
	}
}
void sabTest3D(int p) {
	for (int i = 1000; i < 100000; i += 1000) {


		string t = hp_gen(i, p);

		SAB3D(t);
	}
}
void sabTest2D(int p) {
	for (int i = 1000; i < 100000; i += 1000) {


		string t = hp_gen(i, p);

		SAB2D(t);
	}
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
		"ppphhpphhhhpphhhphhphhphhhhpppppppphhhhhhpphhhhhhppppppppphphhphhhhhhhhhhhpphhhphhphpphphhhpppppphhh" };

	/*

	///block

	for (string inp : inps) {
		string fold = block2D(inp);
		cout << fold << endl;
		visualize(inp, fold);
		
	}
	brake();

	///simple

	for (string inp : inps) {
		string fold = simple2D(inp);
		cout << fold << endl;
		visualize(inp, fold);

	}
	brake();

	///3D

	*/
	
	//runTest(2);
	//scoresTest(2);
	//sabTest(2);
	//sabTest2D(2);
	//sabTest3D(2);

	for (int i = 0; i < 1; i+=1) {
		//cout << simple3D(inps[i]) << endl;
		//cout << "ppphhpphhhhpphhhphhphhphhhhpppppppphhhhhhpphhhhhhppppppppphphhphhhhhhhhhhhpphhhphhphpphphhhpppppphhh" << endl;
		//cout << simple3D("ppphhpphhhhpphhhphhphhphhhhpppppppphhhhhhpphhhhhhppppppppphphhphhhhhhhhhhhpphhhphhphpphphhhpppppphhhphphphppppppppphhhhhhphphphppphhhpphphpphhhhphpphpphppppphpphpphpphhhhhphphphphpphpphpphppppppppppppppppphpphhhhphpphpphpppphpphhhhphpphpphppppppppppppppphphphhhhhhhhhhphppp") << endl;

		cout << simple3D("ppphhpphhhhpphhhphhphhphhhhpppppppphhhhhhpphhhhhhppppppppphphhphhhhhhhhhhhpphhhphhphpphphhhpppppphhh") << endl;
		
		/**** TIMING STUFF ****/
		
		/*
		string t = hp_gen(i);
		int iter = 50;

		
		double time_2d_ms = time_any(iter, t, simple2D)/iter;
		double time_b2da_ms = time_any(iter, t, block2DA)/iter;
		double time_b3d_ms = time_any(iter, t, block3D)/iter;
		
		cout << i << " " << time_2d_ms << " " << time_b2da_ms << " " << time_b3d_ms << endl;
		*/

		/**** Scoring stuff ****/
		
		
		
		/*
		string t = hp_gen(i);
		ofstream dfoldout;

		dfoldout.open("foldout.txt", ios::app);
		dfoldout << t.length() << " " << t << " " << simple2D(t) << " " << block2DA(t) << " " << block3D(t, "UDLRFB", false ) << endl;
		*/

		//visualize3D(t, block3f);

		//cout << block3f << endl;

		//for (char c : t) {
		//	cout << (char)toupper(c);
		//}
	}


	return(brake(), 0);

}