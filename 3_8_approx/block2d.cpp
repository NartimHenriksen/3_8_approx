
#include "stdafx.h"
#include "utility.h"
#include <time.h>


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
int f(int x) {

	return((int) (log(x) / log(2))); //try sqrt?
}


/******		Declared Functions		******/
string normal_form(vector<bool> seq, int matches, string udlr, bool odds);
string make_loop(int gap, char f, char inc, char dec);
string make_loop_rel(int gap) {

	if (gap == 0) {
		return "ff";
	}
	else {
		string fstr = string(gap - 1, 'f');
		return ("l"+ fstr+"rr"+fstr +"l");
	}
}


/******		Utility Functions		******/
/*
void brake() {
std::cout << endl << "Enter to continue...";
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}
*/
bool cond(int a, int b, int A, int B) {
	return((a < b) || ((a == b) && (A < B)));
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
template<class T>
std::vector<T> reverse_vector(std::vector<T>v)
{
std::reverse(v.begin(), v.end());
return v;
}
void visualize(string inp, string fold) {
	//*** By Chrisitan N�rgaard storm***//
	std::string filename = "hpview.py";
	std::string command = "python " + filename + " " + inp + " " + fold;
	system(command.c_str());

}

string normal_form_rel(vector<bool> seq, int matches, bool odds) {
	if (seq.empty() || seq.size() == 1)
		return "";
	//check first one manually since we dont need to fold it. Then start from i=1
	int placed = 0;
	int gap = 0;
	string fold = "";
	if (odds) {
		fold += 'f';
		if (seq[1])
			placed++;
	}
	else if (seq[0]) { placed++; }
	int i = 1;

	while (placed < matches) {
		if (seq[2 * i + (odds ? 1 : 0)]) {
			fold += make_loop_rel (gap);
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






/******		Blocks and Superblocks		******/

struct block {
	vector<bool> sequence;
	size_t size;
	int val=0;
	bool is_x;
	block(vector<bool> seq, bool x) :
		is_x(x),
		sequence(seq),
		size(seq.size())

	{
		for (bool b : seq) {
			if (b)
				val++;
		}
	}
	block(vector<bool> seq) :
		sequence(seq),
		size(seq.size())
	{
		for (bool b : seq) {
			if (b)
				val++;
		}
	}

};
void print_blocks(vector<block> blocks) {
	for (block b : blocks) {
		cout << (b.val==0 ? "SEP: " : (b.is_x ? "  X: " : "  Y: "));
		for (bool ba : b.sequence) { cout << ba; }

		cout << "\nSize: " << b.size << " Val: " << b.val << "\n" << endl;

	}


}
struct superblock {
	vector<block> blocks;
	size_t size;
	int xval;
	int yval;
};//normal form without being x or y. may not need to use this



struct xysuperblock {
	vector<block> blocks; //as defined in paper, it starts and end with non-sep blocks //not right noww
	int total_sequence_length = 0;//total length. To get number of blocks use the vector
	int xval = 0; //val of all x blocks
	int yval = 0; //ditto y blocks
	bool is_x_superblock;
	xysuperblock(vector<block> blox, bool x) {
		is_x_superblock = x;
		blocks = blox;
		for (block b : blocks) {
			total_sequence_length += b.size;///remove this stuff entirely??
			if (b.is_x)
				xval += b.val;
			else
				yval += b.val;
		}


	}
	string superblock_normal_form(string udlr = "udlr")//int forward, int inc, int dec, string udlr = "udlr")
	{
		//vector<block> blbl = blocks; //for debug
									 //leave out beginning sep blocks and then handle them after
		string res = "";
		int i = 0;
		int begin_gap = 0;
		while (i<blocks.size() && (blocks[i].val==0 || !(blocks[i].is_x == is_x_superblock))) {// while i is in legal range AND either condition is not fulfilled
			begin_gap += blocks[i].size;
			//add then increase
			i++;

		}

		if (begin_gap % 2 == 1) {
			res += udlr[3];//could also put inc
			begin_gap--;
		}

		if (begin_gap > 0) {
			res += make_loop((begin_gap / 2) - 1, udlr[3], udlr[0], udlr[1]);
		}

		/*if (blocks[0].val == 0) {
		if (blocks[0].size > 0) {

		res += normal_fold.erase(0, 1); //cannot remove last
		}
		return(res+xysuperblock(subset(blocks, 1, blocks.size() - 1),is_x_superblock).superblock_normal_form(forward,inc,dec,udlr));
		}
		bool fold_first =(blocks[0].is_x == is_x_superblock); // !xor (x er f�rst, superblock er x)
		if (!fold_first) { //handlne beginning and then fold first

		string normal_fold = make_loop(((blocks[0].size + blocks[1].size - 1) / 2), udlr[forward], udlr[inc], udlr[dec]);
		res += normal_fold.erase(normal_fold.length()-1, 1); //Folds of even length er taken to be normal folds but with last char removed
		i = 2;
		}
		*/
		int a = (int)blocks.size();
		//folding first from her on out
		for (i; i < a; i += 4) {


			if (i < a - 4) {//fiddle widdit
							//fold one block to the face
				res += normal_form(blocks[i].sequence, blocks[i].val, udlr, false);
				//loop next three around
				res += make_loop(
					((blocks[i + 1].size + blocks[i + 2].size + blocks[i + 3].size) - 1) / 2, //the -1 is not strictly speaking necessary. Can remove after testing
					udlr[3], udlr[0], udlr[1]);
			}


			else if (i == a - 4) {//The blocks all end with 0. So last non sep block is size-2. So this edge case has the last block to be folded on either size-4 or size-2.

				res += normal_form(blocks[i].sequence, blocks[i].val, udlr, false);

				int gap = 0;
				for (int j = i + 1; j < blocks.size(); j++) {//3 loops
					gap = gap + blocks[j].size;

				}

				res += string(gap, udlr[3]);
				//if (gap > 1) { //never 0 cause there is another nonsep block in this case
				//	res += make_loop((gap-1)/2, udlr[forward], udlr[inc], udlr[dec]);
				//}
				//res += udlr[forward]; //make a dummy since its uneven
			}
			else { //i should be size-2 in this case

				res += normal_form(blocks[i].sequence, blocks[i].val, udlr, false);
				int gap = blocks[i + 1].size;
				if (gap > 0) {
					res += string(gap, udlr[3]);
				}

			}
			//Both methods were written for the first 2d thing, but will do. Can modified for efficiency
		}

		return res;

	}
	string superblock_normal_form_rel() {//f(orward) //l(eft) r(ight) up/down
		//vector<block> blbl = blocks; //for debug
		//leave out beginning sep blocks and then handle them after
		string res = "";
		int i = 0;
		int begin_gap = 0;
		while (i<blocks.size() && (blocks[i].val == 0 || !(blocks[i].is_x == is_x_superblock))) {// while i is in legal range AND either condition is not fulfilled
			begin_gap += blocks[i].size;
			//add then increase
			i++;

		}

		if (begin_gap % 2 == 1) {
			res += 'f';
			begin_gap--;
		}

		if (begin_gap > 0) {
			res += make_loop_rel((begin_gap / 2) - 1);
		}

		/*if (blocks[0].val == 0) {
		if (blocks[0].size > 0) {

		res += normal_fold.erase(0, 1); //cannot remove last
		}
		return(res+xysuperblock(subset(blocks, 1, blocks.size() - 1),is_x_superblock).superblock_normal_form(forward,inc,dec,udlr));
		}
		bool fold_first =(blocks[0].is_x == is_x_superblock); // !xor (x er f�rst, superblock er x)
		if (!fold_first) { //handlne beginning and then fold first

		string normal_fold = make_loop(((blocks[0].size + blocks[1].size - 1) / 2), udlr[forward], udlr[inc], udlr[dec]);
		res += normal_fold.erase(normal_fold.length()-1, 1); //Folds of even length er taken to be normal folds but with last char removed
		i = 2;
		}
		*/
		int a = (int)blocks.size();
		//folding first from her on out
		for (i; i < a; i += 4) {


			if (i < a - 4) {//fiddle widdit
							//fold one block to the face
				res += normal_form_rel(blocks[i].sequence, blocks[i].val, false);
				//loop next three around
				res += make_loop_rel(
					((blocks[i + 1].size + blocks[i + 2].size + blocks[i + 3].size) - 1) / 2);
			}


			else if (i == a - 4) {//The blocks all end with 0. So last non sep block is size-2. So this edge case has the last block to be folded on either size-4 or size-2.

				res += normal_form_rel(blocks[i].sequence, blocks[i].val, false);

				int gap = 0;
				for (int j = i + 1; j < blocks.size(); j++) {//3 loops
					gap = gap + blocks[j].size;
				}

				res += string(gap, 'f');
			}
			else {

				res += normal_form_rel(blocks[i].sequence, blocks[i].val, false);
				int gap = blocks[i + 1].size;
				if (gap > 0) {
					res += string(gap, 'f');
				}

			}
			//Both methods were written for the first 2d thing, but will do. Can modified for efficiency
		}

		return res;
	
	}
};
bool first_label_x(vector<block> blocks) {
	int first = 0;
	int second = 0;
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
	if (first<second)
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

vector<block> blockify(vector<bool> seq) {


	vector<block> blocks = vector<block>();
	int i = 0;
	while (!seq[i]) {
		i++;
	}

	block supp(vector<bool>(i, false));
	blocks.push_back(supp);

	int j = 0;

	while (i < seq.size()) {

		j = i + 1;

		while (!(j == seq.size() || (seq[j] && (j - i) % 2 == 1)))
		{
			j++;
		} //"until seq[j] is 1 AND distance to i is uneven"
		  //count block 0 that separate them
		int z = 0;

		while (seq[j - z - 1] == 0) {
			z += 1;
		}

		blocks.push_back(block(subset(seq, i, j - 1 - z)));
		blocks.push_back(block(vector<bool>(z, false)));

		i = j;


	}

	label_blocks(blocks);
	return blocks;

}


/*
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



	return res;
}
*/



/*****		Subroutine 1. ***/
int MXY(vector<block> A, vector<block> B, bool capital) {

	//clock_t st = clock();
	int XA = 0;
	int YB = 0;
	for (block bloc : A) {
		if (bloc.is_x) //can be true when its a sep block, but val will be 0 anyway
			XA += bloc.val;
	}
	for (block bloc : B) {
		if (!bloc.is_x)
			YB += bloc.val;
	}

	//clock_t end = clock();
	//double post = ((double)(end - st) * 1000 / CLOCKS_PER_SEC);
	//cout << "MXY: " << post << " millisecs" << endl;
	if (capital)
		return (XA>YB ? XA : YB);
	else
		return (XA<YB ? XA : YB);


}
/*
int m_xy(vector<block> A, vector<block> B) {

return (MXY(A, B, false));


}
int m_yx(vector<block> A, vector<block> B) {
return (MXY(B, A, false));
}
int M_xy(vector<block> A, vector<block> B) {
return (MXY(A, B, true));
}
int M_yx(vector<block> A, vector<block> B) {
return (MXY(B, A, true));

}*/
/*
*	seq = boolvector to start the NF from
*	matches = number of H to put in the 'surface'
*	udlr = alphabet to use in the fold output. default is "udlr" for "up, down, left, right"
*	used = reference for the function to pass back how many bools it consumed from seq
*	odds = true iff we are matching odds. Turned out to be nessecary
*/
pair<vector<block>, vector<block>> subroutine1(vector<block> blocks) {

	vector<block> B1 = subset(blocks, 0, 2);
	vector<block> B2 = subset(blocks, 3, blocks.size() - 1);
	vector<block> Bp;
	vector<block> Bpp;
	int e;
	int E;
	if (MXY(B1, B2, false) > MXY(B2, B1, false)) {
		Bp = B2; Bpp = B1; e = MXY(B1, B2, false), E = MXY(B1, B2, true);
	}
	else {
		Bp = B1; Bpp = B2; e = MXY(B2, B1, false), E = MXY(B2, B1, true);
	}
	int k = (blocks.size() - 1) / 2;
	for (int i = 2; i < k; i++) {
		B1 = subset(blocks, 0, i * 2);
		B2 = subset(blocks, 2 * i + 1, blocks.size() - 1);
		if (cond(e, MXY(B1, B2, false), E, MXY(B1, B2, true))) {
			Bp = B2; Bpp = B1; e = MXY(B1, B2, false); E = MXY(B1, B2, true);
		}
		if (cond(e, MXY(B2, B1, false), E, MXY(B2, B1, true))) {
			Bp = B1; Bpp = B2; e = MXY(B2, B1, false); E = MXY(B2, B1, true);
		}
	}

	return{ Bpp,Bp };

}

pair<vector<block>, vector<block>> time_subroutine1(vector<block> blocks) {
	//clock_t start, end;

	vector<block> B1 = subset(blocks, 0, 2);
	vector<block> B2 = subset(blocks, 3, blocks.size() - 1);
	vector<block> Bp;
	vector<block> Bpp;
	int e;
	int E;
	int mxy = MXY(B1, B2, false);
	int myx = MXY(B2, B1, false);
	int Mxy = MXY(B1, B2, true);
	int Myx = MXY(B2, B1, true);

	if (mxy > myx) {
		Bp = B2; Bpp = B1; e = mxy, E = Mxy;
	}
	else {
		Bp = B1; Bpp = B2; e = myx, E = Myx;
	}
	int k = (blocks.size() - 1) / 2;
	//start = clock();
	for (int i = 2; i < k; i++) {
		B1 = subset(blocks, 0, i * 2);
		B2 = subset(blocks, 2 * i + 1, blocks.size() - 1);
		mxy = MXY(B1, B2, false);
		if (e > mxy || (e == mxy && E > (Mxy = MXY(B1, B2, true), Mxy))) {

			Bp = B2; Bpp = B1; e = mxy; E = Mxy;
		}
		if (e > myx || (e == myx && E > (Myx = MXY(B2, B1, true), Myx))) {

			Bp = B1; Bpp = B2; e = myx; E = Myx;
		}
	}
	//end = clock();
	//double time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
	//	cout << "loop zone of subroutine 1: " << time << " ms" << endl;
	return{ Bpp,Bp };

}
pair<vector<block>, vector<block>> subroutine2(vector<block> blocks) {
	//clock_t start, end;

	int B1 = 2;
	int B2 = 3;
	int Bp;
	int Bpp;
	int e;
	int E;
	int x1=0, x2=0, y1=0, y2 = 0;
	for (int i = 0; i < 3; i++) {
		if (blocks[i].is_x) //can be true when its a sep block, but val will be 0 anyway
			x1 += blocks[i].val;
		else { y1 += blocks[i].val; }
	}

	for (int i = 3; i < blocks.size(); i++) {

		if (blocks[i].is_x)
			x2 += blocks[i].val;
		else { y2 += blocks[i].val; }

	}
	int mxy, myx, Mxy, Myx;
	mxy = min(x1, y2);
	myx = min(y1, x2);
	Mxy = max(x1, y2);
	Myx = max(x2, y1);
	bool x_first;
	if (mxy > myx) {
		x_first=true; e = mxy, E = Mxy;
	}
	else {
		x_first=false; e = myx, E = Myx;
	}
	int k = (blocks.size() - 1) / 2;
	//start = clock();
	int best_split = 2; //last block of first part
	for (int i = 2; i < k; i++) {
		//count difference after moving B1/B2 
		
		int diff= blocks[2 * i - 1].val; //2*i -1 should be the one that isnt sep
		int diff_y = 0;
		if (blocks[2 * i - 1].is_x) {
			x1 += diff;
			x2 -= diff;
		}
		else {
			y1 += diff;
			y2 -= diff;
		}


		mxy = min(x1, y2);
		myx = min(y1, x2);
		Mxy = max(x1, y2); //strictly speaking dont have to evaluate this in most cases. Can be lazily evaluated in below ifs
		Myx = max(y1, x2);

		if (e < mxy || (e == mxy && E <  Mxy)) {

			best_split = 2 * i; x_first = true; e = mxy; E = Mxy;
		}
		if (e < myx || (e == myx && E < Myx)) {

			best_split = 2 * i; x_first = false; e = myx; E = Myx;
		}
	}

	//end = clock();
	//double time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
	//	cout << "loop zone of subroutine 1: " << time << " ms" << endl;
	vector<block> first = subset(blocks, 0, best_split);
	vector<block> second = subset(blocks, best_split+1, blocks.size()-1);
	if (x_first)
		return{ first,second };
	else
		return{ second,first };

}




///makes a cusp for algorithm B by taking some aminos from the largest superblock and making a rel fold of them
string exclude_and_fold(xysuperblock &sb, bool exclude_first,string udlr="udlr") {
	string res = "";
	if (exclude_first) {
		block exblock = sb.blocks[0];
		if (exblock.val == 1) {

			int foldlength = sb.blocks[0].size + sb.blocks[1].size + sb.blocks[2].size + sb.blocks[3].size;
			sb.blocks = subset(sb.blocks, 4, sb.blocks.size() - 1);
			return(string(foldlength / 2, udlr[3]) + udlr[1] + string(foldlength / 2, udlr[2]));
			//superblock must exclude this, and the next sep, X and sep.
		}
		else {
			for (int i = 2; i < exblock.size; i += 2) {
				//i=0 is alwasbs the first 1 since the blocks must start and ennd with 1s
				if (exblock.sequence[i]) { 
					sb.blocks[0].val--;

					sb.blocks[0] = block(subset(sb.blocks[0].sequence, i, sb.blocks[0].sequence.size() - 1),sb.blocks[0].is_x);
					
					return(string(i / 2, udlr[3]) + udlr[1] + string(i / 2, udlr[2]));
				}


			}
		}

	}
	else { //exclude last
		int ys = sb.blocks.size();
		block exblock = sb.blocks[ys - 2];
		if (exblock.val == 1) {
			int foldlength = sb.blocks[ys - 4].size + sb.blocks[ys - 3].size + sb.blocks[ys - 2].size + sb.blocks[ys - 1].size+ sb.blocks[ys - 5].size;
			sb.blocks = subset(sb.blocks, 0, ys - 6);
			return(string(foldlength / 2, udlr[3]) + udlr[1] + string(foldlength / 2, udlr[2]));
		}
		else {
			for (int i = exblock.size - 3; i > -1; i -= 2) {
				//i=size-1 is always the last 1 since the blocks must start and ennd with 1s
				if (exblock.sequence[i]) { //this is second last
					sb.blocks[ys - 2].val--;
					
					sb.blocks[ys - 2] = block(subset(sb.blocks[ys - 2].sequence, 0, i),sb.blocks[ys-2].is_x);
					return(string((exblock.size - 1 - i )/ 2, udlr[3]) + udlr[1] + string((exblock.size - 1 - i )/ 2, udlr[2]));
				}

			}
		}
		


	}
	return res;

}


string block2DA(string inp)
{

	int count;
	count = 0;

	//clock_t start1, end1,  start2,end2,start3,end3;
	//double msecs;

	//start1 = clock();
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
	//double pre = ((double)(end1 - start1) * 1000 / CLOCKS_PER_SEC);
	///Need to return which one is B1 and B2. Then need to handle the different cases wrt sep blocks.

	//start2 = clock();
	xysuperblock X(p1, true);

	
	xysuperblock Y(p2, false);


	//end2 = clock();
	/*string xinp = "";
	for (block b : X.blocks) {
	for (bool bo : b.sequence) {
	cout << bo;
	if (bo) {
	xinp += "h";
	}
	else { xinp += "p"; }

	}
	}*/


	//start3 = clock();
	string xfold = X.superblock_normal_form("udlr");
	string yfold = Y.superblock_normal_form("durl");
	string fold;
	if (Y.blocks[0].val == 0) {
		fold = yfold + "u" + xfold;
		//inp = yinp + xinp;
	}
	else {
		fold = xfold + "d" + yfold;
		//inp = xinp + yinp;
	}
	//visualize(inp, fold);

	//std::string filename = "hpview.py";
	//std::string command = "python " + filename + " " + inp + " " + fold + " > " + "folds\\superblock\\" + to_string(count) + "fold";
	//system(command.c_str());


	//end3 = clock();
	//double block = ((double)(end2 - start2 ) * 1000 / CLOCKS_PER_SEC);
	//double foldd = ((double)(end3 - start3) * 1000 / CLOCKS_PER_SEC);
	//cout << pre << "  " << block << " " << foldd << endl;
	return(fold);

}
string block2DB(string inp, string udlr) //modded to accomodate nsew coords
{

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

	
	//////////////////////////here comes an unreadable clusterfuck
	block zi= block(vector<bool>()); //must initialize?
	bool superblock_x_first;
	if (X.blocks[0].val == 0) {
		zi = X.blocks[X.blocks.size() -1];
		superblock_x_first = true;

	}else {
		zi = Y.blocks[Y.blocks.size() - 1];
		superblock_x_first = false;
	}
	string superfold;
	if (zi.size>0|| Y.yval == X.xval) {
	//a
		//damn were using rel stuff after all
		if (superblock_x_first) { //empty from first superblock
			X.blocks[X.blocks.size() - 1] = block(vector<bool>());
		}
		else { Y.blocks[Y.blocks.size() - 1] = block(vector<bool>()); }
		superfold = string(zi.size / 2,udlr[3])+udlr[1]+ string(zi.size / 2, udlr[2]);

	}
	else if (Y.yval > X.xval) {
		//b
		//we are excluding from y. If y is first, we exclude the last. If y is last we exclude its first
		bool exclude_first = superblock_x_first;
		superfold = exclude_and_fold(Y,exclude_first,udlr);
	}
	else {
		//c
		bool exclude_first = !superblock_x_first;
		superfold = exclude_and_fold(X, exclude_first,udlr);
	}
	///////////////////superfold now contains rel fold and superblocks are modified to fit

	
	string fold;
	if (superblock_x_first) {
		string xfold = X.superblock_normal_form(udlr);
		string yfold = Y.superblock_normal_form(string(1,udlr[1])+udlr[0]+udlr[3]+udlr[2]);
		fold = xfold + superfold + yfold;

	}
	else {

		string yfold = Y.superblock_normal_form(udlr);
		string xfold = X.superblock_normal_form(string(1,udlr[1]) +udlr[0]+ udlr[3]+ udlr[2]);
		fold = yfold + superfold + xfold;
	}


	
	//visualize(inp, fold);

	//std::string filename = "hpview.py";
	//std::string command = "python " + filename + " " + inp + " " + fold + " > " + "folds\\superblock\\" + to_string(count) + "fold";
	//system(command.c_str());


	return(fold);

}
/*template <class BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last)
{
	while ((first != last) && (first != --last)) {
		std::iter_swap(first, last);
		++first;
	}
}*/


/////////////// First run subroutine2 and remove the middle part from first vector. Then reverse first vector then fold it forward. Then reverse the fold. Then add the middle. Then fold part2 forward.
///////////////
///////////////



string reversefold(string fold) {
	std::reverse(fold.begin(), fold.end());
	for (int i = 0; i < fold.length(); i++) {
		if (fold[i] == 'l') { fold[i] = 'r'; }
		else if (fold[i] == 'r') { fold[i] = 'l'; }
	}
	fold.erase(fold.length()-1,1);
	return "f" + fold;
}
string block3D(string inp) {

	int count;
	count = 0;
	vector<bool> t = treat_input(inp);

	vector<block> blocks = blockify(t); //turn HP into blocks of 1 and 0
	vector<block> p1;
	vector<block> p2;
	pair<vector<block>, vector<block>> split = subroutine2(blocks); //find the split point
	
	
	p1 = split.first;//X
	p2 = split.second;//Y
	vector<block> first;
	

	//make superblocks from blocks
	xysuperblock X(p1, true);
	xysuperblock Y(p2, false); //think its ok to do this on reversed version

							   //Below part makes fold and modifies the block it came from
	block zi = block(vector<bool>()); //must initialize?
	bool superblock_x_first;
	if (X.blocks[0].val == 0) {
		zi = X.blocks[X.blocks.size() - 1];
		superblock_x_first = true;

	}
	else {
		zi = Y.blocks[Y.blocks.size() - 1];
		superblock_x_first = false;
	}
	string superfold;
	if (zi.size>0 || Y.yval == X.xval) {
		//a
		//damn were using rel stuff after all
		if (superblock_x_first) { //empty from first superblock
			X.blocks[X.blocks.size() - 1] = block(vector<bool>());
		}
		else { Y.blocks[Y.blocks.size() - 1] = block(vector<bool>()); }
		superfold = string(zi.size / 2, 'r') + "d" + string(zi.size / 2, 'l'); //make rel if using this

	}
	else if (Y.yval > X.xval) {
		//b
		//we are excluding from y. If y is first, we exclude the last. If y is last we exclude its first
		bool exclude_first = superblock_x_first;
		superfold = exclude_and_fold(Y, exclude_first);
	}
	else {
		//c
		bool exclude_first = !superblock_x_first;
		superfold = exclude_and_fold(X, exclude_first);
	}
	//superfold now contains fold and superblocks are modified to fit


	/* reversing first superblock*/

	/*
	if (split.first[0].val == 0) {
		first = split.first;
		p1 = reverse_vector(p1);
		for (int i = 0; i < p1.size(); i++) { //reverse all the blocks inside
			p1[i] = block(reverse_vector(p1[0].sequence));
		}
	}
	else {
		first = split.second;
		p2 = reverse_vector(p2);
		for (int i = 0; i < p2.size(); i++) { //reverse all the blocks inside
			p2[i] = block(reverse_vector(p2[0].sequence));
		}
	}
	*/




	//matchings is the 2nd lowest line
	//lines: LB, matchings, actual score, UB
	int matchings = min(X.xval, Y.yval);
	int k = f(matchings);
	int j = (matchings - 2 * k + 1) / k;

	if (k == 1 || j < 2) {
		return block2DB(inp);
	}
	

	string fold;
	int prev = 0;//index of last elements of previous piece
	int iter=0;
	int c;
	//map approach: map "match 1's to indices of string"

	int itr = 0;
	int itsb = 0;
	xysuperblock* fir;
	if (superblock_x_first) { fir = &X; }
	else { fir = &Y; }
	xysuperblock f = *(fir);//f is literally the same pointer as X or Y, whatever is first

	vector<int> boolmap = vector<int>(f.total_sequence_length);//bigger than it needs to be
	for (int i = 0; i < f.blocks.size(); i++) {
		if (f.blocks[i].val > 0 && f.blocks[i].is_x==f.is_x_superblock) { //if block i is right type
													   //scan block and add 1s to map
			for (int ii = 0; ii < f.blocks[i].size; (itr++, ii++)) {
				if (f.blocks[i].sequence[ii]) { //found one
					boolmap[itsb] = itr;
					itsb++;
				}

			}

		}
		else { //else skip to the next
			itr += f.blocks[i].size;
		}

	}//boolmap set
	vector<bool> raw = treat_input(inp);
	int off=0;//accumulated offset
	for (int t = 0; t < k; t++) { //will need to include the off(set) in this loop header

		int from = boolmap[t*j+off];//index of jth 1 of correct parity (in iteration t), offs excluded
		int to = boolmap[(t + 1)*j-1+off];
		vector<bool> piece = subset(raw, from, to);
		xysuperblock sbpiece = xysuperblock(blockify(piece),f.is_x_superblock); //make superblock of same parity as f with the piece from from to to
		if (t%2==0) {
			fold += sbpiece.superblock_normal_form_rel(); //the main part. 

			//switch and slide
			fold += "ur"; //extend u/d in rel with information about direction facing?? like un and us. this would then be unr   //switch levels and slide. Also remove residues used in switch and slide
			//int to = boolmap[(t + 1)*j - 1];


			int last_one = to;// boolmap[(t + 1)*j + off]; //made before incrementing off below!
			//boolmap[last_one +1] == [last one] + 2
			if (boolmap[(t + 1)*j +off] == last_one+2)//boolmap[(t + 1)*j + off] + 2) //if the next one is spaced by only one, exclude it
				off++;
			int first_one = boolmap[(t + 1)*j + off]; //points to the nextone that can be placed. distance is first_one-last_one
			int distance = first_one - last_one;
			int gap = (distance-2) / 2 - 1;
			string foldstr = make_loop_rel(gap);
			if (foldstr[0] == 'f') { foldstr[0] = 'r'; }
			else if (foldstr[0] == 'l') { foldstr[0] = 'f'; }
			fold += foldstr;

			//replace first char: if f then r but if l then f
			//fold += slide_fold()
			//first abs then split?
		}
		else {
			//main part folding down
			fold += sbpiece.superblock_normal_form_rel();


			//wrap part
			int distance = boolmap[(t + 1)*j + off]-to;
			int distance2 = boolmap[(t + 1)*j + off+1] - boolmap[(t + 1)*j + off];

			string wrap = string(distance / 2 - 1, 'f') + "rr" + string(distance / 2 - 1, 'f');
			string wrap2 = string(distance2 / 2 - 1, 'f') + "rr" + string(distance2 / 2 - 1, 'f');
			if (wrap[0] == 'r') { wrap[0] = 'f'; }
			else // wrap[0] == 'f'
				wrap[0] = 'l';
			if (wrap2[0] == 'r') { wrap2[0] = 'f'; }
			else // wrap[0] == 'f'
				wrap2[0] = 'l';
			fold = fold + wrap + wrap2;
			off += 2;
			//boolmap[(t + 1)*j + off] now points to the one after distance to. Can name this value and make the indexing more readable
			
			
			//switch and slide
			int distance3 = boolmap[(t + 1)*j + off]- boolmap[(t + 1)*j + off-1];
			if (distance3 == 2) {
				off++;
				distance3 = boolmap[(t + 1)*j + off] - boolmap[(t + 1)*j + off - 1];
			}
			
			string sas = string(distance3 / 2 - 1, 'f') + "rr" + string(distance3 / 2 - 1, 'f');
			sas[0] = 'u';
			sas[distance3 - 1] = 'l';
			if (sas[1] == 'r')
				sas[1] = 'f';
			else //its 'f' then
				sas[1] = 'l';
			//go around, switch and slide.
			fold += sas;
		}

	}
	string rev = reversefold(fold);
	reversefold(fold);
	//todo: pre and post reverse, middle

	return(fold);
}