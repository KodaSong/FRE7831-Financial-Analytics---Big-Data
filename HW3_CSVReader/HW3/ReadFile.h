#pragma once
#ifndef ReadFile_h
#define ReadFile_h

#include <iostream>
#include <fstream>
#include <sstream> 
#include <ctime>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>
#include <thread>

using namespace std;

//void read_csv(string filename, vector<int> & Volume, vector<double> & Price);
void read_csv_test(string filename, vector<int> & Volume, vector<double> & Price);
void multi_thread(vector<string>& file_vec, vector<int>& Volume, vector<double>& Price);


#endif // !ReadFile_h



