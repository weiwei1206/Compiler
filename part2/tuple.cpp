#include"head.h"
extern int nowaddress;//
extern bianYi parse;            //
extern item sign;            //
void fouryuan::load(int address1, item t1, item t2, item t3, item t4) {
    payyuan[yuantop][0] = t1;
    payyuan[yuantop][1] = t2;
    payyuan[yuantop][2] = t3;
    payyuan[yuantop][3] = t4;
    address[yuantop] = address1;
    yuantop++;
}

//加入无条件跳转语句
void fouryuan::load(int address1, int t4) {
    jumplist[yuantop][0] = -1;
    jumplist[yuantop][1] = t4;
    address[yuantop] = address1;
    yuantop++;
}
void fouryuan::load(int address1, item t1, item t2, item t3, int t4) {
    payyuan[yuantop][0] = t1;
    payyuan[yuantop][1] = t2;
    payyuan[yuantop][2] = t3;
    jumplist[yuantop][0] = 1;
    jumplist[yuantop][1] = t4;
    address[yuantop] = address1;
    yuantop++;
}
fouryuan::fouryuan() {
    yuantop = 0;
}
void fouryuan::backpatch(int l[], int address) {
    for (int i = 1; i<l[0] + 1; i++) {
        jumplist[l[i] - baseaddress][1] = address;
    }
}
void fouryuan::printfouryuan() {
    for (int i = 0; i<yuantop; i++) {
        if (payyuan[i][0].x == 23)  //"program"
            cout << "(" << address[i] << ")" << " ("
            << parse.list1.list[payyuan[i][0].x] << ","
            << parse.list2.list[payyuan[i][1].y] << ",-,-)"
            << endl;
        else if (payyuan[i][0].x == 12)  //"end"
            cout << "(" << address[i] << ")" << " ("
            << "sys,-,-,-)"
            << endl;

        else if (jumplist[i][0] == 1) {  //如果是关系语句
            cout << "(" << address[i] << ")" << " (" << "j"
                << parse.list1.list[payyuan[i][0].x] << ",";
            helpprint(i, 1);
            helpprint(i, 2);
            cout << jumplist[i][1] << ")"
                << endl;
        }
        else if (jumplist[i][0] == -1) {  //如果是无条件跳转语句
            cout << "(" << address[i] << ")" << " (" << "j" << ",-,-,"
                << jumplist[i][1] << ")"
                << endl;
        }
        else if (payyuan[i][0].x != 51) {  //不是赋值语句":="，是其他算数运算
            cout << "(" << address[i] << ")" << " ("
                << parse.list1.list[payyuan[i][0].x] << ",";
            helpprint(i, 1);
            helpprint(i, 2);
            cout << parse.list2.list[payyuan[i][3].y] << ")"
                << endl;
        }
        else {  //如果是赋值语句
            cout << "(" << address[i] << ")" << " ("
                << parse.list1.list[payyuan[i][0].x] << ",";
            helpprint(i, 1);
            cout << "-,"
                << parse.list2.list[payyuan[i][3].y] << ")"
                << endl;
        }
    }
}

//打印单个二元组的内容
void fouryuan::helpprint(int i, int j) {
    if (payyuan[i][j].x == 36)  //如果是标识符，就先去标识符表中寻找
        cout << parse.list2.list[payyuan[i][j].y] << ",";
    else cout << payyuan[i][j].y << ",";
}
