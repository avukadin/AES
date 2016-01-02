#ifndef SOURCE_MATRIX_H
#define SOURCE_MATRIX_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bitset>
using namespace std;

class source_matrix
{
public:
    source_matrix(string name, int *extra, string );
    void mix_columns(int inv);
    void shift(int inv);
    vector < char >* get_master();
    void save_file(string file, int extra, int inv, string);

private:
    vector < char > *master_matrix=new vector <char>;
    char temp1,temp2,temp3;
    int count=0;

    char a,b,c,d;
    int a1,a2,a3,a4;

    unsigned char two(char i);
    unsigned char fourteen(char i);
    unsigned char thirteen(char i);
    unsigned char eleven(char i);
    unsigned char nine(char i);
    unsigned char three(char i);

};

#endif // SOURCE_MATRIX_H
