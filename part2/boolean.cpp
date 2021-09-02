#include"head.h"
extern int nowaddress;
extern bianYi parse;
extern item sign;
extern suanfu_stack STACK;
extern fouryuan Quadruples;
int suanfubiao[numsuanfu + 1][numsuanfu + 1] = { -2, 1,1, 1, 1 ,1 ,1, 1,1, 1,1 ,1,
-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,
-1,1,1,-1,-1,-1,-1,1, 1,-1,-1,-1,
-1,1,1 ,1,-1,-1,-1,1 ,1,-1,-1,-1,
-1,1,1 ,1,-2,-2 ,-1,1,1,-2,-2,-2,
-1,1,1, 1,-2 ,-2,-1,1,1,-2,-2,-2,
-1,-1,-1,-1,-1,-1,-1,0,1,-1,-1,-1,
1,1, 1 ,1, 1, 1, 1, 1, 1,1 , 1,1,
-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,
-1,1,1,1, -2, -2,-1,1 ,1,-2,-2,-2,
-1,1,1,1, -2,-2,-1,1, 1,-2,-2,-2,
-1,1,1,1, -2,-2,-1, 1,1 ,-2,-2,-2
};
int findfuhaobiao(int k) {
    switch (k) {
    case 20:return suanfu_or;   //"or"
    case 18:return suanfu_not;  //"not"
    case 1:return suanfu_and;  //"and"
    case 53:return suanfu_low;  //"<"
    case 57:return suanfu_above;  //">"
    case 39:return suanfu_leftkuohao;  //"("
    case 40:return suanfu_rightkuohao;  //")"
    case 56:return suanfu_equ;  //"="
    case 54:return suanfu_lowequ;  //"<="
    case 58:return suanfu_aboveequ;  //">="
    case 36:  //"标识符"
    case 31:  //“true”
    case 13:  //"false"
    case 37:return suanfu_bctf;  //"整数"
    case suanfu_end: return suanfu_jing;
    default:return -1;
    }
}
void superpop(int i) {
    item temp[5];
    int tempt = STACK.applyfortruelist();
    int tempf = STACK.applyforfalselist();
    switch (i) {
    case suanfu_above:
    case suanfu_low:
    case suanfu_equ:
    case suanfu_aboveequ:
    case suanfu_lowequ: {
        for (int j = 0; j<3; j++)
            STACK.suanfu_pop(temp[j]);  //从栈顶弹相应多个元素
        STACK.optop++;
        Quadruples.load(nowaddress, temp[1], temp[2], temp[0], 0);  //
        STACK.truelist[tempt][1] = nowaddress;
        STACK.falselist[tempf][1] = nowaddress;
        STACK.truelist[tempt][2] = 1;
        STACK.falselist[tempf][2] = 1;
        STACK.truelist[tempt][3] = nowaddress;
        STACK.falselist[tempf][3] = ++nowaddress;
        Quadruples.load(nowaddress, 0);
        ++nowaddress;
        item tempitem(-1, tempt);
        STACK.suanfu_push(tempitem);
        tempitem.x = -2;
        tempitem.y = tempf;
        STACK.suanfu_push(tempitem);
        break;
    }

    case suanfu_not: {
        for (int j = 0; j<3; j++)
            STACK.suanfu_pop(temp[j]);
        STACK.optop += 2;
        STACK.truelist[tempt][0] = _available;
        STACK.falselist[tempf][0] = _available;
        temp[0].x = -1;
        temp[1].x = -2;
        STACK.truelist[temp[1].y][0] = _unavailable;
        STACK.falselist[temp[0].y][0] = _unavailable;
        for (int zz = 0, ww; zz<3 + (STACK.truelist[temp[1].y][2]) ? (STACK.falselist[temp[0].y][2]) : (STACK.truelist[temp[1].y][2])>(STACK.falselist[temp[0].y][2]); zz++) {
            ww = STACK.truelist[temp[1].y][zz];
            STACK.truelist[temp[1].y][zz] = STACK.falselist[temp[0].y][zz];
            STACK.falselist[temp[0].y][zz] = ww;
        }
        STACK.suanfu_push(temp[1]);
        STACK.suanfu_push(temp[0]);
        break;
    }
    case suanfu_and: {
        for (int j = 0; j<5; j++)
            STACK.suanfu_pop(temp[j]);
        STACK.optop += 2;
        Quadruples.backpatch(STACK.truelist[temp[4].y] + 2, STACK.truelist[temp[1].y][1]);
        STACK.falselist_merge(temp[3].y, temp[0].y, tempf);
        STACK.truelist[temp[1].y][0] = _unavailable;
        STACK.truelist[tempt][0] = _available;
        STACK.suanfu_push(temp[1]);
        item tempitem(-2, tempf);
        STACK.suanfu_push(tempitem);
        break;
    }

    case suanfu_or: {
        for (int j = 0; j<5; j++)
            STACK.suanfu_pop(temp[j]);
        STACK.optop += 2;
        Quadruples.backpatch(STACK.falselist[temp[3].y] + 2, STACK.truelist[temp[1].y][1]);
        STACK.truelist_merge(temp[4].y, temp[1].y, tempt);
        STACK.falselist[tempf][0] = _available;
        STACK.falselist[temp[0].y][0] = _unavailable;
        item tempitem(-1, tempt);
        STACK.suanfu_push(tempitem);
        STACK.suanfu_push(temp[0]);
        break;
    }

    case suanfu_bctf: {
        STACK.truelist[tempt][0] = _available;
        STACK.falselist[tempf][0] = _available;
        STACK.optop--;
        break;
    }
      default:error();
    }//

}
TFL boolean_E() {
    item signtemp;
    TFL temptfl;
    if (findfuhaobiao(sign.x) == -1)  //没有布尔语句的必须内容则报错
        error();
    item tempitem(100, 0);
    STACK.suanfu_push(tempitem);
    int i;
    int j = findfuhaobiao(sign.x);
    for (; STACK.suanfutop != 3 || sign.x != 100;) {
        i = findfuhaobiao(STACK.sfs[STACK.optop].x);  //取栈顶的元素
        //
        if (i == -1 || j == -1)error();
        int k = suanfubiao[i][j];

        switch (k) {
        case 0:
        case -1: {  //如果优先级大的话  就压到栈里面
            STACK.suanfu_push(sign);
            nextstat();
            if ((j = findfuhaobiao(sign.x)) == -1) { //栈底
                signtemp = sign;
                sign.x = 100;
                sign.y = 0;
                j = suanfu_jing;
            }

            break;
        }
        case 1: {
            superpop(i);  //如果优先级小于 找到最左素短语
            break;
        }
        default:error();
        }
    }
    sign = signtemp;
    item temp2;
    STACK.suanfu_pop(temp2);
    for (int z = 0; z<STACK.falselist[temp2.y][2] + 1; z++)
        temptfl.headf[z] = STACK.falselist[temp2.y][z + 2];
    STACK.suanfu_pop(temp2);
    for (int z = 0; z<STACK.truelist[temp2.y][2] + 1; z++)
        temptfl.headt[z] = STACK.truelist[temp2.y][z + 2];
    temptfl.codebegin = STACK.truelist[temp2.y][1];
    return temptfl;
}
suanfu_stack::suanfu_stack() {
    suanfutop = 0;
    optop = 0;
    for (int i = 0; i<nummaxstack; i++)
        truelist[i][0] = _available;
    for (int i = 0; i<nummaxstack; i++)
        falselist[i][0] = _available;
}
void suanfu_stack::suanfu_clear() {
    suanfutop = 0;
    optop = 0;
    for (int i = 0; i<nummaxstack; i++)
        truelist[i][0] = _available;
    for (int i = 0; i<nummaxstack; i++)
        falselist[i][0] = _available;
}
int suanfu_stack::applyfortruelist() {
    int i;
    for (i = 0; i<nummaxstack; i++)
        if (truelist[i][0] == _available) {
            truelist[i][0] = _unavailable;
            break;
        }
    if (i == nummaxstack)error();
    return i;
}
int suanfu_stack::applyforfalselist() {
    int i;
    for (i = 0; i<nummaxstack; i++)
        if (falselist[i][0] == _available) {
            falselist[i][0] = _unavailable;
            break;
        }
    return i;
}
void suanfu_stack::suanfu_push(item temp) {
    sfs[suanfutop++] = temp;
    if (temp.x != -1 && temp.x != -2)
        optop = suanfutop - 1;
}
void suanfu_stack::suanfu_pop(item &temp) {
    --suanfutop;
    --optop;
    if (sfs[suanfutop].x == -1) {
        truelist[sfs[suanfutop].y][0] = _available;
        temp = sfs[suanfutop];
    }
    else if (sfs[suanfutop].x == -2) {
        falselist[sfs[suanfutop].y][0] = _available;
        temp = sfs[suanfutop];
    }
    else {
        temp = sfs[suanfutop];
    }

}
void suanfu_stack::truelist_merge(int first, int second, int end) {
    int k;
    for (k = 3; k<truelist[first][2] + 3; k++)
        truelist[end][k] = truelist[first][k];
    int t = k;
    k = 0;
    for (; k<truelist[second][2]; k++)
        truelist[end][k + t] = truelist[second][k + 3];
    truelist[end][2] = k - 2;
    truelist[end][1] = truelist[first][1];
}
void suanfu_stack::falselist_merge(int first, int second, int end) {
    int k;
    for (k = 3; k<falselist[first][2] + 3; k++)
        falselist[end][k] = falselist[first][k];
    int t = k;
    k = 0;
    for (; k<falselist[second][2]; k++)
        falselist[end][k + t] = falselist[second][k + 3];
    falselist[end][2] = falselist[first][2] + falselist[second][2];
    falselist[end][1] = falselist[first][1];
}
