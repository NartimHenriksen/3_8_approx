
#include "stdafx.h"
#include "utility.h"


using namespace std;

/*
string block3D(string inp){
	
	int count;
	count = 0;

	vector<bool> t = treat_input(inp);
	vector<block> blocks = blockify(t);
	vector<block> p1;
	vector<block> p2;
	////remove bad one
	//pair<vector<block>, vector<block>> split2 = subroutine1(blocks); //need to make X-superblock for Bpp (first one), and Y for Bp (second one)
	pair<vector<block>, vector<block>> split = subroutine2(blocks); //need to make X-superblock for Bpp (first one), and Y for Bp (second one)
																	///
																	//end1 = clock();
	p1 = split.first;
	p2 = split.second;

	xysuperblock X(p1, true);
	xysuperblock Y(p2, false);
	//string twodfold = block2D(inp);
	return("");
}*/