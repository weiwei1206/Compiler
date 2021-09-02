#include"head.h"


extern int nowaddress;//��ʾ��һ����ַ
extern bianYi parse;            //�ʷ�����
extern int c;               //��ʱ�����ĺ�׺
extern item sign;            //
extern fuzhi_stack FUZHI_STACK;//��ֵջ
extern fouryuan Quadruples;         //��Ԫ���
extern valuetable VT;          //������
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

//��ʼ���������
state mulsentence() {
    state temp;
    switch (sign.x) {
    case 3:  //��begin��
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
    case 43:return fuzhi_add; //��+��
    case 45:return fuzhi_sub;  //��-��
    case 41:return fuzhi_mul;  //��*��
    case 48:return fuzhi_div;  //"/"
    case 51:return fuzhi_equ;  //":="
    case 39:return fuzhi_leftkuohao;  //"("
    case 40:return fuzhi_rightkuohao;  //")"
    case 36:
    case 37:return fuzhi_bc;  //"����"
    case fuzhi_end: return fuzhi_jing;
    default:return -1;
    }
}
void fuzhi_superpop(int i) {
    item temp[3];
    switch (i) {
    case fuzhi_add: {  //��+��
        for (int j = 0; j<3; j++)  //������������װ��temp����
            FUZHI_STACK.fuzhi_pop(temp[j]);
        FUZHI_STACK.optop++;
        char tempc[templength];  //��ʱ������
        tempc[0] = 't';

        string strss;
        strss=to_string(c);
        strncpy(tempc+1,strss.c_str(),templength-1); //����һ����ʱ���� ti
//        _itoa_s(c, tempc + 1,templength-1, 10);
        c++;  //��ʱ���������
        FUZHI_STACK.applyforitem(tempc);  //����ʱ���������ּӵ���ʶ������
        item tempt(36, parse.list2.idend - 1);  //��ʱ��������һ
        //
        valuetype tempv;

        int ttt = 0;
        if (temp[2].x == 36)  //����Ӻ��ұ��Ǳ�ʶ��
            ttt = VT.vt_findlocation(temp[2].y);  //�ҵ����ڱ������е�λ��
        int kkk = 0;
        if (temp[0].y == 36)  //����Ӻ�����Ǳ�ʶ��
            kkk = VT.vt_findlocation(temp[0].y);
        if (ttt == -1 || kkk == -1)error();  //�κ�һ���������ھͳ�����
        tempv.location = parse.list2.idend - 1;  //�±���λ��
        tempv.type = VT.vt[ttt].type;  //�±�������
        VT.add(tempv);  //�����±���
        //
        FUZHI_STACK.fuzhi_push(tempt);  //���±����ӵ���ֵ��
        FUZHI_STACK.optop--;
        Quadruples.load(nowaddress, temp[1], temp[2], temp[0], tempt); //��+��2,0,t��
        nowaddress++;  //��ǰ��Ԫʽ��ַ��һ
        break;

    }

      //���˷�����ͬ�ϣ�
    case fuzhi_mul: {
        for (int j = 0; j<3; j++)  //�Ӹ�ֵջ����������Ҫ���˷�����
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
        //����������ͬ�ϣ�
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

//��ʼ����ֵ���
state fuzhi_E() {
    FUZHI_STACK.fuzhi_clear();
    state tempstate;
    tempstate.codebegin = nowaddress;
    tempstate.chain[0] = 0;
    item signtemp;
    if (findfuhaobiao(sign.x) == -1)  //����������е�����һ���ͱ��� ��Ϊ�����Ǳ�ʶ����ͷ�Ž�����
        error();
    item tempitem(100, 0);
    FUZHI_STACK.fuzhi_push(tempitem);
    int i;
    int j = findfuzhibiao(sign.x);
    for (; FUZHI_STACK.fuzhitop != 1 || sign.x != 100;) {  //ջû��
        i = findfuzhibiao(FUZHI_STACK.fzs[FUZHI_STACK.optop].x);  //��ȡջ��Ԫ��

        if (i == -1 || j == -1)error();
        int k = fuzhibiao[i][j];

        switch (k) {
        case 0:
        case -1: {
            FUZHI_STACK.fuzhi_push(sign);
            nextstat();
            if ((j = findfuzhibiao(sign.x)) == -1) {  //���û�ڸ�ֵ���У����������ʽ������ѹ��߽�
                signtemp = sign;
                sign.x = 100;
                sign.y = 0;
                j = fuzhi_jing;
            }

            break;
        }
        case 1: {  //�ҵ������ض���
            fuzhi_superpop(i);
            break;
        }
        default:error();
        }
    }
    sign = signtemp;
    return tempstate;
}
