#include "stdafx.h"
#include "utility.h"
using namespace std;
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
	
	std::stringstream ss;
	std::string a;

	double sim=0;
	double block=0;
	std::string simf;
	std::string blockf;
	std::string tdf;
	static int iterations = 1;
	
	//string problematic_sequence = "PHPHHPHHPPHPHHHHHPPHPPHPPHPHHPHPPPHPPHPHHPPHHPPPPPHPHPPPPHHPPPHPPPHPHPPPPPPPPPPHHPPHPHHHHHHPPPPPPHHPPHPHPPHPHHHHHPHHPHHHPHHPHPHPPPHHHHHHPPHPPHHPHPPHPHHHPHHPHHHPHHHHHPPHPHPHPPPPPPPPPHHHHHHPPHPHPPPHPHHPPHPHPHHPPPHHPPPPPPHHHPPPHHHPPPHHPHPHHPPPHPHHHHHHPPPPHHHHHPPHHPHPHPHHHHHHPPHPPPHHPHHHHPPHHHHHPHHPHPPPPPHPPPHHHHPHPHPPHHHPHHPHPHHPPHHPPHHHPPPPHPHHPPHPHPPPPPHPHPPHHHPPHPHPPHPHHHPPPPPHPPPPPHHHHHPPPPPHHHHPPHHHHHHHPHPPHHPHPHHHPPHPPHHHHHPHPPPHHPHHPPPHHHPPHPHPHPPPPHHHPPPPPPHPPHPHHPHPPHPPHPHHPPPPPPHHHPHPPHPHPPPPPHPHPHPHHPPHHPHHHHHPPHHPPHPPHPPHPPPPHHPHPHPHHPHPPPPPHHHHPPPHHHPHHHPPHHPHPHHPHPPPPHPPHPPPPHHPHHPHHPHPPHPHPHPHHPPPHPHHHPPPHPPPHHHHHHPHHPPPPHHHPHPHHHPPPHHPPHPHPHHPPHHHHHPHHHPPPPHPHPHPPHHPPPPHHPHHHPPHHPPHPHPHPHHHPPHHHHHHHHHPHHHHPHPPHPHHHHPHHHPHHHPPHHHHHPPHPPHHHHHHPHPHHHPHHPPPPHPHHHHPHHHPPPPPPPHHPHHPPHPPHPPHHPPPHHPPPPPPHPPHHHHPPPPPHHPHPHHPPHPPHHHHHPHHHHPHPHHHHPPPHPPHPHPPHHPPHHPPPHHPPPPPHHHPHHHPHPHHPPPPPHPPPHHPHPHPHHPHPPPPHPHHHHPPHHPPPPHPPPHPPPPPHHHPHPHHHH";
	//string j = block3D(problematic_sequence, "UDLRFB", true);
	//ofstream foldout;
	//ofstream dataout;
	//foldout.open("3Dfolds.txt", ios::app);
	//foldout << problematic_sequence << " " << j << endl;//to be handled by lol.py
	//foldout.close();

	//brake();
	//return(0);
	for (int i = 100; i < 100000; i=i*=1.1) { //1.1 for real test




		string t = hp_gen(i);



		string block3f = block3D(t,"UDLRFB",true);
		
		//visualize3D(t, block3f);
		
		//cout << block3f << endl;

		//for (char c : t) {
		//	cout << (char)toupper(c);
		//}
		//cout << endl;
		//cout << block2f << endl;

		
		//ss << iterations << "," << i << "," << sim << "," << block << endl;//csv format
		ofstream foldout;
		//ofstream dataout;
		foldout.open("3Dfolds.txt",ios::app);
		foldout << t << " " << block3f << endl;//to be handled by lol.py
		foldout.close();
		//dataout.open("3Ddata.txt", ios::app);
		
		//std::string command = "echo " + t + " " + block3f + " >> " + "3Dfolds.txt";
		//system(command.c_str());
		//command = "echo " + t + " " + simf + " " + blockf + " >> " + "folds.txt";
		//system(command.c_str());
		
	}


	return(brake(), 0);

}