#include "widget.h"
#include "ui_widget.h"
#include <QCheckBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

     ui->lineEdit_2->setText(myDir.currentPath()+"/");
     ui->lineEdit_3->setText(myDir.currentPath()+"/");
     ui->lineEdit->setEchoMode(QLineEdit::Password);
     ui->radioButton->setChecked(1);


}

Widget::~Widget()
{
    delete ui;

}


void Widget::on_pushButton_clicked()
{
    this->close();
}


void Widget::on_pushButton_2_clicked()
{
    QDir ales;
    Source_path= ui->lineEdit_2->text();
    if(ui->checkBox->isChecked()){


    }
    Dest_path= ui->lineEdit_3->text();
    Password= ui->lineEdit->text();

    string key=Password.toStdString();
    encrypt=1;
    if(ui->radioButton->isChecked()){
        encrypt=0;
    }
    string Source_path_string=Source_path.toStdString();
    string Dest_path_string=Dest_path.toStdString();
    string file;
    for(auto a=Source_path_string.end()-1 ; a!=Source_path_string.begin();--a ){
        if(*a=='/'){
            ++a;
            while(a!=Source_path_string.end()){
                file+=*a;
                ++a;
            }
            break;
        }

    }

    //==========================================

    int extra=0;
    source_matrix master(file,&extra,Source_path_string);
    key_matrix key_m(key);

    vector<char> temp(4);
    vector<vector<char>> const_vec(11,temp);

    //Generate round keys
    for(int round=1; round<=10; ++round){
        //shift up last columns of key
        key_m.shift(round);

        //S-box last coloumns of key
        for(int i=12; i<16 ; ++i){
            s_box( &( (*key_m.get_key(round))[i] ) );
        }

        //get round constant
        const_vec[round]=round_const(round);

        //XOR round constant with s-boxed column and first columns of previous round key
        for(auto i=0 ; i<4; ++i){
            (*key_m.get_key(round))[i]=((const_vec[round][i])^(*key_m.get_key(round))[i+12])^((*key_m.get_key(round-1))[i]);
        }

        //Generate 2nd, 3rd and 4th column of new key
        for(auto i=4; i<16; ++i){
            (*key_m.get_key(round))[i]=(*key_m.get_key(round))[i%4]^(*key_m.get_key(round-1))[i];
        }

    }

    //Encryption Algorthithum
    if(encrypt==0){
        //XOR coresponding entries with key matrix
        XOR(key_m.get_key(0),master.get_master());

        for(int round=1; round<=10 ; ++round){

            //Run state matrix through s-box
            for(auto i=master.get_master()->begin(); i!=master.get_master()->end(); ++i){
                s_box(&(*i));
            }

            //Shift rows of state matrix
            master.shift(0);

            //Mix columns
            master.mix_columns(0);

            //XOR state matrix current round key key
            XOR(key_m.get_key(round),master.get_master());

        }
    }

    //Decryption Algorithum
    else{
        for(int round=10; round>0; --round){
            XOR(key_m.get_key(round),master.get_master());

            master.mix_columns(1);

            master.shift(1);

            for(auto i=master.get_master()->begin(); i!=master.get_master()->end(); ++i){
                s_box_inv(&(*i));
            }
        }
        XOR(key_m.get_key(0),master.get_master());
    }

   master.save_file(file, extra, encrypt,Dest_path_string);

   }




void Widget::s_box( char *a){
    unsigned char h=*a;
    const vector < vector < string > > encrypterse_matrix
    {
    {"00", "01", "8d", "f6", "cb", "52", "7b", "d1", "e8", "4f", "29", "c0", "b0", "e1", "e5", "c7"},
    {"74", "b4", "aa", "4b", "99", "2b", "60", "5f", "58", "3f", "fd", "cc", "ff", "40", "ee", "b2"},
    {"3a", "6e", "5a", "f1", "55", "4d", "a8", "c9", "c1", "0a", "98", "15", "30", "44", "a2", "c2"},
    {"2c", "45", "92", "6c", "f3", "39", "66", "42", "f2", "35", "20", "6f", "77", "bb", "59", "19"},
    {"1d", "fe", "37", "67", "2d", "31", "f5", "69", "a7", "64", "ab", "13", "54", "25", "e9", "09"},
    {"ed", "5c", "05", "ca", "4c", "24", "87", "bf", "18", "3e", "22", "f0", "51", "ec", "61", "17"},
    {"16", "5e", "af", "d3", "49", "a6", "36", "43", "f4", "47", "91", "df", "33", "93", "21", "3b"},
    {"79", "b7", "97", "85", "10", "b5", "ba", "3c", "b6", "70", "d0", "06", "a1", "fa", "81", "82"},
    {"83", "7e", "7f", "80", "96", "73", "be", "56", "9b", "9e", "95", "d9", "f7", "02", "b9", "a4"},
    {"de", "6a", "32", "6d", "d8", "8a", "84", "72", "2a", "14", "9f", "88", "f9", "dc", "89", "9a"},
    {"fb", "7c", "2e", "c3", "8f", "b8", "65", "48", "26", "c8", "12", "4a", "ce", "e7", "d2", "62"},
    {"0c", "e0", "1f", "ef", "11", "75", "78", "71", "a5", "8e", "76", "3d", "bd", "bc", "86", "57"},
    {"0b", "28", "2f", "a3", "da", "d4", "e4", "0f", "a9", "27", "53", "04", "1b", "fc", "ac", "e6"},
    {"7a", "07", "ae", "63", "c5", "db", "e2", "ea", "94", "8b", "c4", "d5", "9d", "f8", "90", "6b"},
    {"b1", "0d", "d6", "eb", "c6", "0e", "cf", "ad", "08", "4e", "d7", "e3", "5d", "50", "1e", "b3"},
    {"5b", "23", "38", "34", "68", "46", "03", "8c", "dd", "9c", "7d", "a0", "cd", "1a", "41", "1c"}
    };

    int num=0;

    string encrypterse=encrypterse_matrix[h/16][h%16];
    int i=0;
    char encrypterse_char=0;
    while(i<2){

        switch(encrypterse[i])
        {

            case '0':
            num=0;
            break;

            case '1':
            num=1;
            break;

            case '2':
            num=2;
            break;

            case '3':
            num=3;
            break;

            case '4':
            num=4;
            break;

            case '5':
            num=5;
            break;

            case '6':
            num=6;
            break;

            case '7':
            num=7;
            break;

            case '8':
            num=8;
            break;

            case '9':
            num=9;
            break;

            case 'a':
            num=10;
            break;

            case 'b':
            num=11;
            break;

            case 'c':
            num=12;
            break;

            case 'd':
            num=13;
            break;

            case 'e':
            num=14;
            break;

            case 'f':
            num=15;
            break;

            case 'g':
            num=16;
            break;

        }

        if(i==0){
            encrypterse_char+=16*num;
        }

        else{
            encrypterse_char+=num;
        }
        ++i;
    }

    //Converts encrypterse_char to binary vector
    vector<int> bitvec(8,0);
    bitset<8> bits(encrypterse_char);

    for(auto i=0 ; i<8; ++i){
        if(bits.test(i)){
            bitvec[i]=1;
        }
    }

    //Multiplies bitvec by matrix
    vector< vector <int> > matrix={
    {1,0,0,0,1,1,1,1},
    {1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1},
    {1,1,1,1,0,0,0,1},
    {1,1,1,1,1,0,0,0},
    {0,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,0},
    {0,0,0,1,1,1,1,1},
    };

    vector<int> result_vec(8,0);
    for (auto i=0; i<8; ++i){
        for (auto j=0; j<8; ++j){
            result_vec[i]+=bitvec[j]*matrix[i][j];
        }

        if(i==0 || i==1 || i==5 || i==6){
            result_vec[i]+=1;
        }

        result_vec[i]%=2;
            }

    bitset<8> s_char_b;
    for(auto i=0; i<8; ++i){

        if(result_vec[i]==1){
            s_char_b.flip(i);
        }

    }

    unsigned char s_char=s_char_b.to_ulong();
    *a=s_char;

}

void Widget::XOR(vector<char> *key_matrix, vector<char> *master_matrix){

    int count=0;
    auto j=(*key_matrix).begin();
    for(auto i=(*master_matrix).begin() ; i!=(*master_matrix).end() ; ++i){
        (*i)=(*i)^(*j);
        count++;
        j++;
        if(count==16){
            count=0;
            j=(*key_matrix).begin();
        }
    }
}

void Widget::s_box_inv(char *a){
    unsigned char h=*a;
    const vector<vector<string>> s_encrypterse={
    {"52","09","6a","d5","30","36","a5","38","bf","40","a3","9e","81","f3","d7","fb"},
    {"7c","e3","39","82","9b","2f","ff","87","34","8e","43","44","c4","de","e9","cb"},
    {"54","7b","94","32","a6","c2","23","3d","ee","4c","95","0b","42","fa","c3","4e"},
    {"08","2e","a1","66","28","d9","24","b2","76","5b","a2","49","6d","8b","d1","25"},
    {"72","f8","f6","64","86","68","98","16","d4","a4","5c","cc","5d","65","b6","92"},
    {"6c","70","48","50","fd","ed","b9","da","5e","15","46","57","a7","8d","9d","84"},
    {"90","d8","ab","00","8c","bc","d3","0a","f7","e4","58","05","b8","b3","45","06"},
    {"d0","2c","1e","8f","ca","3f","0f","02","c1","af","bd","03","01","13","8a","6b"},
    {"3a","91","11","41","4f","67","dc","ea","97","f2","cf","ce","f0","b4","e6","73"},
    {"96","ac","74","22","e7","ad","35","85","e2","f9","37","e8","1c","75","df","6e"},
    {"47","f1","1a","71","1d","29","c5","89","6f","b7","62","0e","aa","18","be","1b"},
    {"fc","56","3e","4b","c6","d2","79","20","9a","db","c0","fe","78","cd","5a","f4"},
    {"1f","dd","a8","33","88","07","c7","31","b1","12","10","59","27","80","ec","5f"},
    {"60","51","7f","a9","19","b5","4a","0d","2d","e5","7a","9f","93","c9","9c","ef"},
    {"a0","e0","3b","4d","ae","2a","f5","b0","c8","eb","bb","3c","83","53","99","61"},
    {"17","2b","04","7e","ba","77","d6","26","e1","69","14","63","55","21","0c","7d"}
    };

    string encrypterse=s_encrypterse[h/16][h%16];
    int i=0;
    int num=0;
    char encrypterse_char=0;
    while(i<2){

        switch(encrypterse[i])
        {

            case '0':
            num=0;
            break;

            case '1':
            num=1;
            break;

            case '2':
            num=2;
            break;

            case '3':
            num=3;
            break;

            case '4':
            num=4;
            break;

            case '5':
            num=5;
            break;

            case '6':
            num=6;
            break;

            case '7':
            num=7;
            break;

            case '8':
            num=8;
            break;

            case '9':
            num=9;
            break;

            case 'a':
            num=10;
            break;

            case 'b':
            num=11;
            break;

            case 'c':
            num=12;
            break;

            case 'd':
            num=13;
            break;

            case 'e':
            num=14;
            break;

            case 'f':
            num=15;
            break;

            case 'g':
            num=16;
            break;

        }

        if(i==0){
            encrypterse_char+=16*num;
        }

        else{
            encrypterse_char+=num;
        }
        ++i;
    }

    *a=encrypterse_char;

}

vector <char> Widget::round_const(int round){
    vector<char> const_vec(4);
    const_vec[0]=1;
    int i=0;
    while(round>1 && i<round){
        const_vec[0]=(const_vec[0]<<1)^27;

        ++i;
    }
    return const_vec;
}

