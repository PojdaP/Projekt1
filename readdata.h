#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool readcsv( ifstream& file, vector<vector<string>>& data );
bool readtxt( ifstream& file, vector<vector<string>>& data );