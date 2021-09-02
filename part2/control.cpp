#include"head.h"
extern int nowaddress;
extern bianYi parse;
extern item sign;
extern fouryuan Quadruples;
extern suanfu_stack STACK;


extern valuetable VT;

//重载 =
state&state::operator=(state &temp) {
    for (int i = 0; i<temp.chain[0] + 1; i++)
        chain[i] = temp.chain[i];
    codebegin = temp.codebegin;
    return *this;
}

state sentence() {
    state temp;
    switch (sign.x) {  //从句子的第一个token串开始分析

    case 23: {//programe  如果是程序的开始
        item signtemp = sign;
        nextstat();
        if (sign.x != 36)error();  //程序第一个句子第一个token 不是标识符就  报错
        Quadruples.load(nowaddress, signtemp, sign, sign, sign);  //第一个四元式：0,program,标识符
        nowaddress++;
        nextstat();  //取“;”
        if (sign.x != 52)error(); //如果直接不是；就报错
        nextstat();
        state temp = S();  //进行变量定义分析
        sentence();  //分析下一条语句
        return temp;
//        break;
    }
    case 34: {//while   如果是循环语句
        state temp = while_1S3();
        return temp;
//        break;
    }
    case 36: {//  如果是标识符  就转赋值语句
        state temp = fuzhi_E();
        return temp;
//        break;
    }
    case 3: {//begin  复合语句
        state temp = mulsentence();
        return temp;
//        break;
    }
    case 15: {//if  条件语句
        state temp = if_TS2();
        return temp;
//        break;
    }
    case 26: {//   repeat语句
        state temp = repeat_E();
        return temp;
//        break;
    }
    default:error();
    }
    return temp;
}

//变量说明语句
state S() {
    state temp;
    switch (sign.x) {
    case 33: {  //var
        nextstat();
        valueDefine();  //var 后面的第一个变量的定义
        K();
        break;
        //
    }
    default:break;
    }
    return temp;
}

//如果是标识符 开始具体处理：1.记录值 2.确定类型
state K() {
    state temp;
    switch (sign.x) {
    case 36: {  //标识符
        valueDefine();
        break;
    }
    default:break;
    }
    return temp;
}

//变量定义：1.记下标识符的值  2.
valuetype valueDefine() {
    valuetype temp;
    if (sign.x != 36)error();  //如果开头的不是标识符就不是变量定义
    temp.location = sign.y;  //确定 变量的标识符
    nextstat();  //要靠后面的语句才能判定 变量类型

    temp.type = (L()).type;  //确定 变量的类型
    VT.add(temp);  //把变量加到变量表
    return temp;
}

//变量定义语句： 变量之后的两种情况： “,”，“：”（不包含句尾的；）
valuetype L() {
    valuetype temp;
    switch (sign.x) {
    case 44: {  //“，”：还没法确定值，递归调用
        nextstat();
        //     if(sign.x!=36)error();
        temp.type = (valueDefine()).type;
        break;
    }
    case 50: {  //“：”：就可以取到下一个token然后确定类型
        nextstat();
        temp.type = (T()).type;
        break;
    }
    default:error();
    }
    return temp;
}


//变量定义语句：最后类型具体
valuetype T() {
    valuetype temp;
    switch (sign.x) {
    case 17: {  //integer
        temp.type = 17;
        nextstat();
        if (sign.x != 52)error();
        nextstat();
        break;
    }
    case 4: {  //bool
        temp.type = 4;
        nextstat();
        if (sign.x != 52)error();
        nextstat();
        break;
    }
    default: error();
    }
    return temp;
}

state SS() {
    state temp;
    return temp;

};
state::state() {
    chain[0] = 0;
    codebegin = nowaddress;
};
state::state(const state & temp) {
    for (int i = 0; i<temp.chain[0] + 1; i++) {
        chain[i] = temp.chain[i];
    }
    codebegin = temp.codebegin;
}
state& state::merge(int cs[], int cd[]) {
    for (int i = 0; i<cs[0] + 1; i++)
        chain[i] = cs[i];
    for (int i = 1; i<cd[0] + 1; i++)
        chain[i + cs[0]] = cd[i];
    chain[0] = cs[0] + cd[0];
    return*this;
}
//state&state::operator=(state &temp) {
//    for (int i = 0; i<temp.chain[0] + 1; i++)
//        chain[i] = temp.chain[i];
//    codebegin = temp.codebegin;
//    return *this;
//}

//记录循环语句开始  产生式：W → while
state while_() {
    state temp;
    temp.codebegin = nowaddress;
    if (sign.x != 34)error();  //while
    return temp;
}

//处理do之前的循环语句  产生式：  W’→ W E do
state while_Edo() {
    state temp;
    state tempw = while_();
    nextstat();
    TFL tempe = boolean_E();
    if (sign.x != 10)error(); //条件完不是“do”就错
    Quadruples.backpatch(tempe.headt, nowaddress);
    for (int zz = 0; zz<tempe.headf[0] + 1; zz++)
        temp.chain[zz] = tempe.headf[zz];
    temp.codebegin = tempw.codebegin;
    return temp;
}

//处理 整个 循环语句   产生式： S‘→ W’ S3
state while_1S3() {
    STACK.suanfu_clear();  //分析一条语句开始的时候清空符号栈
    state temp;
    state tempc = while_Edo(); //到while do之前
    nextstat();
    state temps = sentence();
    Quadruples.backpatch(temps.chain, tempc.codebegin);
    Quadruples.load(nowaddress, tempc.codebegin);
    nowaddress++;
    temp = tempc;
    return temp;
}

//开始处理条件语句
state if_TS2() {
    STACK.suanfu_clear();
    state temp;
    state tempt = if_CS0else();
    nextstat();
    state temps = sentence();
    temp.merge(temps.chain, tempt.chain);
    temp.codebegin = tempt.codebegin;
    return temp;
}

//处理then之前的循环语句
state if_Ethen() {
    state temp;
    switch (sign.x) {
    case 15: { //if
        nextstat();
        TFL tempe = boolean_E();
        Quadruples.backpatch(tempe.headt, nowaddress);
        for (int zz = 0; zz<tempe.headf[0] + 1; zz++)
            temp.chain[zz] = tempe.headf[zz];
        temp.codebegin = tempe.codebegin;
        if (sign.x != 29)error();  //then
        break;
    }
    default:error();
    }
    return temp;
}

//处理else之前的循环语句   T → C S0 else
state if_CS0else() {
    state temp;
    state tempc = if_Ethen();
    nextstat();
    state temps = fuzhi_E();//
    if (sign.x != 11)error();  //else
    int q = nowaddress;
    Quadruples.load(nowaddress, 0);
    nowaddress++;
    Quadruples.backpatch(tempc.chain, nowaddress);
    int tempq[2];
    tempq[0] = 1;
    tempq[1] = q;
    temp.merge(temps.chain, tempq);
    return temp;
}
/*
repeat_E->repeat_T E
repeat_T->repeat_B S until
repeat_B->repeat
*/
state repeat_B() {
    state temp;
    temp.codebegin = nowaddress;
    if (sign.x != 26)error();  //“repeat”
    return temp;
}

//until语句之前的
state repeat_T() {
//    state temp;
    //temp.codebegin=nowaddress;
    state temp = repeat_B();
    nextstat();
    state temps = sentence();
    //  nextstat();
    if (sign.x != 32)error();  //"until"
    Quadruples.backpatch(temps.chain, nowaddress);
    return temp;
}

//开始处理重复语句  整个
state repeat_E() {
    STACK.suanfu_clear();
    state temp;
    state tempt = repeat_T();
    nextstat();
    TFL temptfl = boolean_E();
    Quadruples.backpatch(temptfl.headf, tempt.codebegin);
    //     Quadruples.load(nowaddress,tempt.codebegin);
    //	  nowaddress++;
    //	  cout<<"goto        ,"<<endl;
    for (int zz = 0; zz<temptfl.headt[0] + 1; zz++)
        temp.chain[zz] = temptfl.headt[zz];
    temp.codebegin = tempt.codebegin;
    return temp;
}
