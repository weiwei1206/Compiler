#include"head.h"
extern int nowaddress;
extern bianYi parse;
extern item sign;
extern fouryuan Quadruples;
extern suanfu_stack STACK;


extern valuetable VT;

//���� =
state&state::operator=(state &temp) {
    for (int i = 0; i<temp.chain[0] + 1; i++)
        chain[i] = temp.chain[i];
    codebegin = temp.codebegin;
    return *this;
}

state sentence() {
    state temp;
    switch (sign.x) {  //�Ӿ��ӵĵ�һ��token����ʼ����

    case 23: {//programe  ����ǳ���Ŀ�ʼ
        item signtemp = sign;
        nextstat();
        if (sign.x != 36)error();  //�����һ�����ӵ�һ��token ���Ǳ�ʶ����  ����
        Quadruples.load(nowaddress, signtemp, sign, sign, sign);  //��һ����Ԫʽ��0,program,��ʶ��
        nowaddress++;
        nextstat();  //ȡ��;��
        if (sign.x != 52)error(); //���ֱ�Ӳ��ǣ��ͱ���
        nextstat();
        state temp = S();  //���б����������
        sentence();  //������һ�����
        return temp;
//        break;
    }
    case 34: {//while   �����ѭ�����
        state temp = while_1S3();
        return temp;
//        break;
    }
    case 36: {//  ����Ǳ�ʶ��  ��ת��ֵ���
        state temp = fuzhi_E();
        return temp;
//        break;
    }
    case 3: {//begin  �������
        state temp = mulsentence();
        return temp;
//        break;
    }
    case 15: {//if  �������
        state temp = if_TS2();
        return temp;
//        break;
    }
    case 26: {//   repeat���
        state temp = repeat_E();
        return temp;
//        break;
    }
    default:error();
    }
    return temp;
}

//����˵�����
state S() {
    state temp;
    switch (sign.x) {
    case 33: {  //var
        nextstat();
        valueDefine();  //var ����ĵ�һ�������Ķ���
        K();
        break;
        //
    }
    default:break;
    }
    return temp;
}

//����Ǳ�ʶ�� ��ʼ���崦��1.��¼ֵ 2.ȷ������
state K() {
    state temp;
    switch (sign.x) {
    case 36: {  //��ʶ��
        valueDefine();
        break;
    }
    default:break;
    }
    return temp;
}

//�������壺1.���±�ʶ����ֵ  2.
valuetype valueDefine() {
    valuetype temp;
    if (sign.x != 36)error();  //�����ͷ�Ĳ��Ǳ�ʶ���Ͳ��Ǳ�������
    temp.location = sign.y;  //ȷ�� �����ı�ʶ��
    nextstat();  //Ҫ��������������ж� ��������

    temp.type = (L()).type;  //ȷ�� ����������
    VT.add(temp);  //�ѱ����ӵ�������
    return temp;
}

//����������䣺 ����֮������������ ��,��������������������β�ģ���
valuetype L() {
    valuetype temp;
    switch (sign.x) {
    case 44: {  //����������û��ȷ��ֵ���ݹ����
        nextstat();
        //     if(sign.x!=36)error();
        temp.type = (valueDefine()).type;
        break;
    }
    case 50: {  //���������Ϳ���ȡ����һ��tokenȻ��ȷ������
        nextstat();
        temp.type = (T()).type;
        break;
    }
    default:error();
    }
    return temp;
}


//����������䣺������;���
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

//��¼ѭ����俪ʼ  ����ʽ��W �� while
state while_() {
    state temp;
    temp.codebegin = nowaddress;
    if (sign.x != 34)error();  //while
    return temp;
}

//����do֮ǰ��ѭ�����  ����ʽ��  W���� W E do
state while_Edo() {
    state temp;
    state tempw = while_();
    nextstat();
    TFL tempe = boolean_E();
    if (sign.x != 10)error(); //�����겻�ǡ�do���ʹ�
    Quadruples.backpatch(tempe.headt, nowaddress);
    for (int zz = 0; zz<tempe.headf[0] + 1; zz++)
        temp.chain[zz] = tempe.headf[zz];
    temp.codebegin = tempw.codebegin;
    return temp;
}

//���� ���� ѭ�����   ����ʽ�� S���� W�� S3
state while_1S3() {
    STACK.suanfu_clear();  //����һ����俪ʼ��ʱ����շ���ջ
    state temp;
    state tempc = while_Edo(); //��while do֮ǰ
    nextstat();
    state temps = sentence();
    Quadruples.backpatch(temps.chain, tempc.codebegin);
    Quadruples.load(nowaddress, tempc.codebegin);
    nowaddress++;
    temp = tempc;
    return temp;
}

//��ʼ�����������
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

//����then֮ǰ��ѭ�����
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

//����else֮ǰ��ѭ�����   T �� C S0 else
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
    if (sign.x != 26)error();  //��repeat��
    return temp;
}

//until���֮ǰ��
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

//��ʼ�����ظ����  ����
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
