#include"head.h"
#include<string.h>

int nowaddress = baseaddress;
bianYi parse;
int c = 1;
valuetable VT;
fouryuan Quadruples;
fuzhi_stack FUZHI_STACK;
suanfu_stack STACK;
item sign;

int main() {
//    while(1){
        GATE:
        cout<<endl<<endl<<endl;
        cout<<"WeiWei"<<endl;
        cout<<"201630970798"<<endl;
        cout<<"JK1"<<endl;
        cout<<endl<<endl;
        cout<<"Please input the program_number:";
        char test[10];
        cin >> test;
        if (strcmp(test, "TEST3")==0) {   //< = >
            parse.createbianYi3();  //读取文件到流
            parse.ciFa();  //对读入的流进行词法分析
            nextstat();
            sentence();
            Quadruples.printfouryuan();
        }
        else if (strcmp(test, "TEST4") == 0) {
            parse.createbianYi4();
            parse.ciFa();
            nextstat();  //取一个二元组
            sentence();
            Quadruples.printfouryuan();
        }
        else if (strcmp(test, "TEST1") == 0) {
            parse.createbianYi1();
            parse.ciFa();
            nextstat();
            sentence();
            Quadruples.printfouryuan();
        }
        else if (strcmp(test, "TEST2") == 0) {
            parse.createbianYi2();
            parse.ciFa();
            nextstat();
            sentence();
            Quadruples.printfouryuan();
        }
        else if (strcmp(test, "TEST5") == 0) {
            parse.createbianYi5();
            parse.ciFa();
            nextstat();
            sentence();
            Quadruples.printfouryuan();
        }
        else {
            cout << "Wrong,please input again." << endl;
            goto GATE;
        }
//    }

    system("pause");
}
