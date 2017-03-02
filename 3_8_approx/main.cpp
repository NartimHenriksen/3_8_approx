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
	cout << string(15 / 2, 'r') << endl;
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
	for (int i = 20; i < 500; i=i+1) {
		string t = hp_gen(i);

		//sim = time_simple2d(iterations,t);
		//block = time_block2d(iterations,t);

		//simf = simple2D(t);


		//string block2f = block2DB(t,"nswe");
		string block3f = block3D(t,"UDLRFB");

		//tdf = block3D(t);
		
		//visualize3D(t,block2f);
		//visualize3D(t, block3f);
		cout << block3f << endl;
		//cout << absrev(block3f,"UDLRFB") << endl;
		//cout << rel2abs(block3f,"UDLRFB")<<endl;
		for (char c : t) {
			cout << (char)toupper(c);
		}
		cout << endl;
		//cout << block2f << endl;

		
		//ss << iterations << "," << i << "," << sim << "," << block << endl;//csv format
		//ss >> a;
		//cout << a << endl;
		//std::string command = "echo " + t + " " + simf + " " + blockf + " >> " + "folds.txt";
		//system(command.c_str());
		//command = "echo " + t + " " + simf + " " + blockf + " >> " + "folds.txt";
		//system(command.c_str());
		
	}


	return(brake(), 0);

}