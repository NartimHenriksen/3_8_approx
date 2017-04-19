#pragma once
//#define NDEBUG 
#include <assert.h>

#include <vector>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
//std::pair<vector<block>, vector<block>> subroutine2(vector<block> blocks);
//vector<block> blockify(vector<bool> b);

template<class T>
std::vector<T> reverse_vector(std::vector<T>v);
void visualize3D(std::string inp, std::string fold);
void visualize(std::string inp, std::string fold);
void brake();
std::vector<bool> treat_input(std::string);
int func(int x);
std::string block2DA(std::string inp);
std::string block2DB(std::string inp); //, std::string udlr= "UDLRFB"
std::string simple2D(std::string inp);
std::string simple3D(std::string inp);

std::string block3D(std::string inp, string udlr, bool logdata);//string udlr= "UDLRFB",bool logdata=false);
std::string block3D(std::string inp);
double time_simple2d(int iterations, std::string inp);
double time_block2DA(int iterations, std::string inp);
double time_any(int iterations, std::string inp, string(*f)(string));

//double time_block2DB(int iterations, std::string inp);
std::string rel2abs(std::string rel, string udlr);
std::string abs2rel(std::string abs, string udlr);
std::string absrev(std::string abs, string udlr);
std::string hp_gen(const int length,const int p);
void SAB2D(string inp);
void SAB3D(string inp);
