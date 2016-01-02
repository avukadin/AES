#include "key_matrix.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bitset>
using namespace std;


    key_matrix::key_matrix(string key){
        for(auto i=0; i<16 ; ++i){
            key_m.push_back(' ');
        }

        for(auto c : key){
            key_m[i]=c;
            ++i;
        }

        for(auto i=0; i<=10; ++i){
            round_key.push_back(key_m);
        }
    }

    void key_matrix::shift(int round){
            temp=round_key[round][12];
            round_key[round][12]=round_key[round][13];
            round_key[round][13]=round_key[round][14];
            round_key[round][14]=round_key[round][15];
            round_key[round][15]=temp;

    }

    vector <char>* key_matrix::get_key(int round){
       return &(round_key[round]);
    }


