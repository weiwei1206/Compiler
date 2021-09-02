#include"head.h"


extern int nowaddress;//表示下一个地址
extern bianYi parse;            //词法分析
extern int c;               //临时变量的后缀
extern item sign;            //
extern fuzhi_stack FUZHI_STACK;//赋值栈
extern fouryuan Quadruples;         //四元组表
extern valuetable VT;          //变量表
int fuzhibiao[numfuzhi + 1][numfuzhi + 1] = { -2,1,1,1,1,1,1,-2,1,
-1,1,1,-1,-1,-2,1,-1,1,
-1,1,1,-1,-1,-2,1,-1,1,
-1,1,1,1,1,-2,1,-1,1,
-1,1,1,1,1,-2,1,-1,1,
-1,-1,-1,-1,-1,-2,1,-1,1,
-1,-1,-1,-1,-1,-1,0,-1,-2,
-1,-1,-1,-1,-1,-1,-2,-1,0,
-2,1,1,1,1,1,1,1,1
};

//开始处理复合语句
state mulsentence() {
    state temp;
    switch (sign.x) {
    case 3:  //“begin”
    {
        nextstat();
        state temp = sentencelist();
        if (sign.x != 12){ //end
            error();
        }
        Quadruples.load(nowaddress, sign, sign, sign, sign);
        return temp;
//        break;
    }
    default:error();
    }
    return temp;
}
state sentencelist() {
    state temp = sentence();
    state temp2 = sentencetemp();
    Quadruples.backpatch(temp.chain, temp2.codebegin);
    return temp2;
}
state sentencetemp() {
    state temp;
    switch (sign.x) {
    case 52: {  //";"
        nextstat();
        if (sign.x == 12)return temp;  //"end"
        sentencelist();
        break;
    }
    default:break;
    }
    return temp;
}
void fuzhi_stack::fuzhi_clear() {
    fuzhitop = 0;
    optop = 0;
}
fuzhi_stack::fuzhi_stack() {
    fuzhitop = 0;
    optop = 0;
}
void fuzhi_stack::fuzhi_push(item temp) {
    fzs[fuzhitop++] = temp;
    optop = fuzhitop - 1;
}
int fuzhi_stack::applyforitem(char fuhao[max3]) {
    parse.list2.add(fuhao);
    return 1;
}
void fuzhi_stack::fuzhi_pop(item &temp) {
    --fuzhitop;
    --optop;
    temp = fzs[fuzhitop];

}
int findfuzhibiao(int k) {
    switch (k) {
    case 43:return fuzhi_add; //“+”
    case 45:return fuzhi_sub;  //“-”
    case 41:return fuzhi_mul;  //“*”
    case 48:return fuzhi_div;  //"/"
    case 51:return fuzhi_equ;  //":="
    case 39:return fuzhi_leftkuohao;  //"("
    case 40:return fuzhi_rightkuohao;  //")"
    case 36:
    case 37:return fuzhi_bc;  //"整数"
    case fuzhi_end: return fuzhi_jing;
    default:return -1;
    }
}
void fuzhi_superpop(int i) {
    item temp[3];
    switch (i) {
    case fuzhi_add: {  //“+”
        for (int j = 0; j<3; j++)  //弹出三个东西装到temp里面
            FUZHI_STACK.fuzhi_pop(temp[j]);
        FUZHI_STACK.optop++;
        char tempc[templength];  //临时变量表
        tempc[0] = 't';

        string strss;
        strss=to_string(c);
        strncpy(tempc+1,strss.c_str(),templength-1); //创建一个临时变量 ti
//        _itoa_s(c, tempc + 1,templength-1, 10);
        c++;  //临时变量的序号
        FUZHI_STACK.applyforitem(tempc);  //把临时变量的名字加到标识符表中
        item tempt(36, parse.list2.idend - 1);  //临时变量数加一
        //
        valuetype tempv;

        int ttt = 0;
        if (temp[2].x == 36)  //如果加号右边是标识符
            ttt = VT.vt_findlocation(temp[2].y);  //找到其在变量表中的位置
        int kkk = 0;
        if (temp[0].y == 36)  //如果加号左边是标识符
            kkk = VT.vt_findlocation(temp[0].y);
        if (ttt == -1 || kkk == -1)error();  //任何一个变量不在就出错了
        tempv.location = parse.list2.idend - 1;  //新变量位置
        tempv.type = VT.vt[ttt].type;  //新变量类型
        VT.add(tempv);  //加入新变量
        //
        FUZHI_STACK.fuzhi_push(tempt);  //把新变量加到赋值表
        FUZHI_STACK.optop--;
        Quadruples.load(nowaddress, temp[1], temp[2], temp[0], tempt); //（+，2,0,t）
        nowaddress++;  //当前四元式地址加一
        break;

    }

      //（乘法过程同上）
    case fuzhi_mul: {
        for (int j = 0; j<3; j++)  //从赋值栈弹出三个需要做乘法的项
            FUZHI_STACK.fuzhi_pop(temp[j]);
        FUZHI_STACK.optop++;
        char tempc[3];
        tempc[0] = 't';

        string strss=to_string(c);
        strncpy(tempc+1,strss.c_str(),2);
//        _itoa_s(c, tempc + 1,2, 10);
        c++;
        FUZHI_STACK.applyforitem(tempc);
        item tempt(36, parse.list2.idend - 1);
        valuetype tempv;
        int ttt = VT.vt_findlocation(temp[2].y);
        tempv.location = parse.list2.idend - 1;
        tempv.type = VT.vt[ttt].type;
        VT.add(tempv);
        FUZHI_STACK.fuzhi_push(tempt);
        FUZHI_STACK.optop--;
        Quadruples.load(nowaddress, temp[1], temp[2], temp[0], tempt);
        nowaddress++;
        break;
    }
        //（除法过程同上）
    case fuzhi_div: {
        for (int j = 0; j<3; j++)
            FUZHI_STACK.fuzhi_pop(temp[j]);
        FUZHI_STACK.optop++;
        char tempc[3];
        tempc[0] = 't';

        string strss=to_string(c);
        strncpy(tempc+1,strss.c_str(),2);
//        _itoa_s(c, tempc + 1,2, 10);
        c++;
        FUZHI_STACK.applyforitem(tempc);
        item tempt(36, parse.list2.idend - 1);
        //
        valuetype tempv;
        int ttt = VT.vt_findlocation(temp[2].y);
        tempv.location = parse.list2.idend - 1;
        tempv.type = VT.vt[ttt].type;
        VT.add(tempv);
        //
        FUZHI_STACK.fuzhi_push(tempt);
        FUZHI_STACK.optop--;
        Quadruples.load(nowaddress, temp[1], temp[2], temp[0], tempt);
        nowaddress++;
        break;

    }
    case fuzhi_equ: {
        for (int j = 0; j<3; j++)
            FUZHI_STACK.fuzhi_pop(temp[j]);
        Quadruples.load(nowaddress, temp[1], temp[0], temp[0], temp[2]);
        nowaddress++;
        break;
    }
    case fuzhi_rightkuohao: {
        for (int j = 0; j<3; j++)
            FUZHI_STACK.fuzhi_pop(temp[j]);
        FUZHI_STACK.fuzhi_push(temp[1]);
        break;
    }
    case fuzhi_bc: {
        FUZHI_STACK.optop--;
        break;
    }
    }
}

//开始处理赋值语句
state fuzhi_E() {
    FUZHI_STACK.fuzhi_clear();
    state tempstate;
    tempstate.codebegin = nowaddress;
    tempstate.chain[0] = 0;
    item signtemp;
    if (findfuhaobiao(sign.x) == -1)  //不是算符表中的任意一个就报错 因为这里是标识符开头才进来的
        error();
    item tempitem(100, 0);
    FUZHI_STACK.fuzhi_push(tempitem);
    int i;
    int j = findfuzhibiao(sign.x);
    for (; FUZHI_STACK.fuzhitop != 1 || sign.x != 100;) {  //栈没空
        i = findfuzhibiao(FUZHI_STACK.fzs[FUZHI_STACK.optop].x);  //获取栈顶元素

        if (i == -1 || j == -1)error();
        int k = fuzhibiao[i][j];

        switch (k) {
        case 0:
        case -1: {
            FUZHI_STACK.fuzhi_push(sign);
            nextstat();
            if ((j = findfuzhibiao(sign.x)) == -1) {  //如果没在赋值表中，则这条表达式结束，压入边界
                signtemp = sign;
                sign.x = 100;
                sign.y = 0;
                j = fuzhi_jing;
            }

            break;
        }
        case 1: {  //找到最左素短语
            fuzhi_superpop(i);
            break;
        }
        default:error();
        }
    }
    sign = signtemp;
    return tempstate;
}
