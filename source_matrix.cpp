#include "source_matrix.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bitset>
using namespace std;

source_matrix::source_matrix(string name, int *extra){
    ifstream file(name);
    while(file.get(c)){

        master_matrix.push_back(c);
        ++count;

    }
    *extra=0;
    for(int i=count%16 ; i<16 ;i++){
        master_matrix.push_back(' ');
        ++(*extra);
    }
file.close();
}

unsigned char source_matrix::two(char i){
     unsigned char result=(i<<1);
     bitset<8>byte(i);
     if(byte.test(7)){
     //	result=result^27;
     }
     return result;
 }
unsigned char source_matrix::fourteen(char i){

     unsigned char result=two(two(two(i)^i)^i);
     //cout<<i<<endl;
     return result;
 }

unsigned char source_matrix::thirteen(char i){
     unsigned char result=two(two(two(i)^i))^i;
     return result;
 }

unsigned char source_matrix::eleven(char i){
     unsigned char result=two(two(two(i))^i)^i;
     return result;
 }

unsigned char source_matrix::nine(char i){
     unsigned char result=two(two(two(i)))^i;
     return result;
 }

unsigned char source_matrix::three(char i){
     unsigned char result=two(i)^i;
     return result;
 }

void source_matrix::mix_columns( int inv){
     if(inv==0){
         for(auto i=master_matrix.begin() ; i!=master_matrix.end(); i=i+4 ){
             a=*i;
             b=*(i+1);
             c=*(i+2);
             d=*(i+3);
             a1=a;
             a2=b;
             a3=c;
             a4=d;

             *i=two(a1)^three(a2)^(a3)^(a4);
             *(i+1)=(a1)^two(a2)^three(a3)^(a4);
             *(i+2)=(a1)^(a2)^two(a3)^three(a4);
             *(i+3)=three(a1)^(a2)^(a3)^two(a4);


         }

     }
     else{
         for(auto i=master_matrix.begin() ; i!=master_matrix.end(); i=i+4 ){
             a=*i;
             b=*(i+1);
             c=*(i+2);
             d=*(i+3);
             a1=a;
             a2=b;
             a3=c;
             a4=d;

             *i=fourteen(a1)^eleven(a2)^thirteen(a3)^nine(a4);
             *(i+1)=nine(a1)^fourteen(a2)^eleven(a3)^thirteen(a4);
             *(i+2)=thirteen(a1)^nine(a2)^fourteen(a3)^eleven(a4);
             *(i+3)=eleven(a1)^thirteen(a2)^nine(a3)^fourteen(a4);

         }
     }

 }

 void source_matrix::shift(int inv){
     if(inv==0){
         for(auto i=master_matrix.begin() ; i!=master_matrix.end() ; i+=16){

             //row 2
             temp1=*(i+4);
             *(i+4)=*(i+5);
             *(i+5)=*(i+6);
             *(i+6)=*(i+7);
             *(i+7)=temp1;

             //row 3
             temp1=*(i+8);
             temp2=*(i+9);
             *(i+8)=*(i+10);
             *(i+9)=*(i+11);
             *(i+10)=temp1;
             *(i+11)=temp2;

             //row 4
             temp1=*(i+12);
             temp2=*(i+13);
             temp3=*(i+14);
             *(i+12)=*(i+15);
             *(i+13)=temp1;
             *(i+14)=temp2;
             *(i+15)=temp3;
         }
     }

     else{
         for(auto i=master_matrix.begin() ; i!=master_matrix.end() ; i+=16){
             //row 2
             temp1=*(i+7);
             *(i+7)=*(i+6);
             *(i+6)=*(i+5);
             *(i+5)=*(i+4);
             *(i+4)=temp1;

             //row 3
             temp1=*(i+11);
             temp2=*(i+10);
             *(i+11)=*(i+9);
             *(i+10)=*(i+8);
             *(i+9)=temp1;
             *(i+8)=temp2;

             //row4
             temp1=*(i+15);
             temp2=*(i+14);
             temp3=*(i+13);
             *(i+15)=*(i+12);
             *(i+14)=temp1;
             *(i+13)=temp2;
             *(i+12)=temp3;
         }
     }
 }
    void source_matrix::save_file(string file, int extra ,int inv){

        ofstream myfile;
        if(inv==1){
        myfile.open("d-"+file);
        }
        else{myfile.open("e-"+file);}
        string text;
        if(inv==1){
        for(auto i=master_matrix.begin(); i!=master_matrix.end()-extra; ++i){
            myfile<<*i;
            //mix_columns(&master_matrix,0);
        }
        }
        else{
            for(auto i=master_matrix.begin(); i!=master_matrix.end(); ++i){
                myfile<<*i;
            }
        }
        //cout<<text;
        //myfile<<text;
        myfile.close();
    }

 vector<char>* source_matrix::get_master() {
     return &master_matrix;
 }
