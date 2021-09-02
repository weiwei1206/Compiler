#include<iostream>
#include<string.h>
#include<string>
#include<cstring>
#include<fstream>
#include<stdlib.h>
#include<sstream>

using namespace std;

#define max 61
#define max2 200
#define max3 40
#define max4 40
#define max0 10
class item {
public:
    int x, y;
    item();
    item(int x1, int x2);
};

class resultlist {
public:
    int w;  //œá¹û±íÖÐ¶þÔª×éµÄžöÊý
    int hang[max2];
    item result[max2];
    resultlist();
    void add(int hao, int id, int);
    //ŽòÓ¡œá¹û
    void print();
};


//±êÊ¶·û±í
class changbiaolist {
public:
    int idend;
    char *list[max2];
    changbiaolist();
    void add(char hao[max3]);
};

//±àÂë±íÀà
class biaomalist {
public:
    char*list[max];
    biaomalist();
};

//
class bianYi {
private:
    fstream inf;
    int i;//ÐÐºÅ

public:
    biaomalist list1;  //±àÂë±í
    resultlist list3;  //œá¹û±í
    changbiaolist list2;  //±êÊ¶·û±í
    void createbianYi3();  //
    void createbianYi4();  //
    void createbianYi1();  //
    void createbianYi2();  //
    void createbianYi5();  //
    bianYi();
    bianYi(char*fileName);
    int looklist1(int begin, int end, char fuhao[10]);
    int looklist2(char fuhao[10]);  //±êÊ¶·û
    int looklist22(char fuhao[max3]);  //×Ö·û³£Êý
    char getCh();
    ~bianYi();
    void ciFa();
};

//state
#define numchain 10
class state {
public:
    int chain[numchain];
    int codebegin;
    state&merge(int cs[], int cd[]);
    state&operator=(state &);
    state(const state&temp);
    state();
};

//tfl
#define numTFL 10
class TFL {
public:
    TFL() {}
    int headt[numTFL];
    int headf[numTFL];
    int codebegin;
    TFL&operator=(TFL &temp);
    TFL(const TFL & temp);

};

//Ëã·û
#define suanfu_or    1
#define suanfu_and   2
#define suanfu_not   3
#define suanfu_above     4
#define suanfu_low     5
#define suanfu_leftkuohao   6
#define suanfu_rightkuohao     7
#define suanfu_bctf  0
#define suanfu_jing     8
#define suanfu_equ 9
#define suanfu_lowequ 10
#define suanfu_aboveequ 11
#define suanfu_end   100
#define numsuanfu 11
#define volumnstack 40
#define nummaxstack 10
#define volumntruelist 10
#define volumnfalselist 10
#define _available 1
#define _unavailable 0

class suanfu_stack {
public:
    int suanfutop;
    int optop;//ÔËËã·û¶¥
    item sfs[volumnstack];
    int truelist[nummaxstack][volumntruelist];
    int falselist[nummaxstack][volumnfalselist];
    suanfu_stack();
    void suanfu_clear();
    int applyfortruelist();
    int applyforfalselist();
    void suanfu_push(item temp);
    void suanfu_pop(item &temp);
    void truelist_merge(int first, int second, int end);
    void falselist_merge(int first, int second, int end);
};
int findfuhaobiao(int k);
void superpop(int i);
TFL boolean_E(); //ÕâÒ»Ä£¿éµÄÈë¿Ú


                 //¿ØÖÆ
                 /*
                 while_W->while
                 while_W->while_W boolean_E do
                 while_W1S3->while_W S
                 */
state while_();
state while_Edo();
state while_1S3();//while¿ØÖÆÓïŸäµÄÈë¿Ú
                /*
                if_Ethen->if boolean_E then
                if_CS0else->if_Ethen S else
                if_TS2->if_CS0else S
                */
state if_CS0else();
state if_Ethen();
state if_TS2();//while¿ØÖÆÓïŸäµÄÈë¿Ú
             /*
             repeat_E->repeat_T E
             repeat_T->repeat_B S until
             repeat_B->repeat
             */
state repeat_B();
state repeat_E();//repeat¿ØÖÆÓïŸäµÄÈë¿Ú
state repeat_T();
//ž³Öµ
#define numfuzhi 8
#define fuzhi_add 1
#define fuzhi_sub 2
#define fuzhi_mul 3
#define fuzhi_div 4
#define fuzhi_equ 5
#define fuzhi_bc 0
#define fuzhi_jing   6
#define fuzhi_leftkuohao 7
#define fuzhi_rightkuohao 8
#define volumnstack 40
#define fuzhi_end   100

class fuzhi_stack {
public:
    int fuzhitop;
    int optop;//ÔËËã·û¶¥
    item fzs[volumnstack];
    fuzhi_stack();
    int applyforitem(char fuhao[max3]);
    void fuzhi_push(item temp);
    void fuzhi_pop(item &temp);
    void fuzhi_clear();
};
int findfuzhibiao(int k);
void fuzhi_superpop(int i);
state fuzhi_E();//ÕâÒ»Ä£¿éµÄÈë¿Ú

#define numtv 20
//±êÊ¶·û£šŒŽ±äÁ¿£© ŸßÌåµÄ ÀàÐÍ
class valuetype {
public:
    int type;
    int location;
    valuetype(int, int);
    valuetype(const valuetype&);
    valuetype();
};

//±äÁ¿±í£ºŽ¢ŽæÃ¿žö valuetype()£ºÖµ£¬ÀàÐÍ
class valuetable {
public:
    valuetype vt[numtv];
    int vttop;
    valuetable();
    void add(valuetype);
    int vt_findlocation(int l);
    void print();
};
state sentence();//Èë¿Ú
state S();
state K();
valuetype valueDefine();
valuetype L();
valuetype T();
//ÓïŸä¹¹Ôì
/*
mulsentence->begin sentencelist end   žŽºÏÓïŸäµÄchainÈ¡ÓïŸä±íµÄchain
sentencelist->sentence sentencetemp   ÓÃÁÙÊ±ŸäµÄcodebegin»ØÌîÓïŸäµÄchain,ÓÃsentencetempµÄchain×÷ÎªÓïŸä±íµÄchain
sentencetemp->;sentencelist|#         ÓïŸä±íµÄchain×÷ÎªÁÙÊ±ŸäµÄchain,ÈôÎª¿ÕÔò·µ»Ø³€¶ÈÎª0µÄchain
*/
state mulsentence();
state sentencelist();
state sentencetemp();

//ËÄÔªÊœ
#define numyuan 40
class fouryuan {
public:
    fouryuan();
    item payyuan[numyuan][4];  //ËÄÔª×é±í   Ã¿žöËÄÔª×éÓÐËÄžö¶þÔª×é
    int jumplist[numyuan][2];  //Ìø×ª±í   Ã¿ÏîŒÇÂŒŽÓÄÄÌø×ªµœÄÄ
    void load(int, item t1, item t2, item t3, item t4);
    void load(int, item t1, item t2, item t3, int t4);
    void backpatch(int l[], int address);
    void load(int address1, int t4);
    int yuantop;
    int address[numyuan];
    void printfouryuan();
    void helpprint(int, int);

};

#define baseaddress 0    //»ùµØÖ·
#define templength 8



void error();              //³öŽíŽŠÀí
void nextstat();
