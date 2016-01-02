#ifndef KEY_MATRIX_H
#define KEY_MATRIX_H

//#include "key_matrix_global.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bitset>
using namespace std;


class key_matrix
{
public:
    key_matrix(string key);
    void shift(int round);
    vector <char>* get_key(int round);

private:
    vector<char> key_m;
    int i=0;
    vector < vector<char> >round_key;
    char temp;
};


#endif // KEY_MATRIX_H
