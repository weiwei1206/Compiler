#include"head.h"

extern bianYi parse;            //词法分析
extern item sign;            //


void valuetable::add(valuetype temp) {
    vt[vttop++] = temp;
}
valuetable::valuetable() {
    vttop = 0;
}
void valuetable::print() {
    for (int i = 0; i<vttop; i++)
        cout << parse.list2.list[vt[i].location] << "  " << vt[i].type << endl;
}
int valuetable::vt_findlocation(int l) {
    for (int i = 0; i<vttop; i++) {
        if (vt[i].location == l)return i;
    }
    return -1;
}
valuetype::valuetype(int x, int y) {
    type = x;
    location = y;
}
valuetype::valuetype() {};
valuetype::valuetype(const valuetype&temp) {
    type = temp.type;
    location = temp.location;
}
resultlist::resultlist() { w = 0; };
void resultlist::add(int hao, int id, int hangi) {
    result[w].x = hao;
    result[w].y = id;
    hang[w] = hangi;
    w++;
}
void resultlist::print() {
    int i;
    for(i=0;i<w;i++){
        cout<<"("<<result[i].x<<","<<result[i].y<<")"<<"\t";
        if((i+1)%5==0)cout<<endl;
    }

//    for(int i=0;i<w;i++){
//        cout<<"W"<<hang[i]<<endl;
//    }
}


changbiaolist::changbiaolist() {
    idend = 1;
    for (int j = 0; j<max2; j++) {
        list[j] = new char[max3];
    }
}
void changbiaolist::add(char hao[max3]) {
    strncpy(list[idend++], hao, max3);
}

biaomalist::biaomalist() {
    for (int j = 0; j<max; j++) {
        list[j] = new char[max0];
    }
    strncpy(list[1], "and", 10);
    strncpy(list[2], "array", 10);
    strncpy(list[3], "begin", 10);
    strncpy(list[4], "bool", 10);
    strncpy(list[5], "call", 10);
    strncpy(list[6], "case", 10);
    strncpy(list[7], "char", 10);
    strncpy(list[8], "constant", 10);
    strncpy(list[9], "dim", 10);
    strncpy(list[10], "do", 10);
    strncpy(list[11], "else", 10);
    strncpy(list[12], "end", 10);
    strncpy(list[13], "false", 10);
    strncpy(list[14], "for", 10);
    strncpy(list[15], "if", 10);
    strncpy(list[16], "input", 10);
    strncpy(list[17], "integer", 10);
    strncpy(list[18], "not", 10);
    strncpy(list[19], "of", 10);
    strncpy(list[20], "or", 10);
    strncpy(list[21], "output", 10);
    strncpy(list[22], "procedure", 10);
    strncpy(list[23], "program", 10);
    strncpy(list[24], "read", 10);
    strncpy(list[25], "real", 10);
    strncpy(list[26], "repeat", 10);
    strncpy(list[27], "set", 10);
    strncpy(list[28], "stop", 10);
    strncpy(list[29], "then", 10);
    strncpy(list[30], "to", 10);
    strncpy(list[31], "true", 10);
    strncpy(list[32], "until", 10);
    strncpy(list[33], "var", 10);
    strncpy(list[34], "while", 10);
    strncpy(list[35], "write", 10);
    strncpy(list[36], "标识符", 20);
    strncpy(list[37], "整数", 20);
    strncpy(list[38], "字符常数", 20);
    strncpy(list[39], "(", 10);
    strncpy(list[40], ")", 10);
    strncpy(list[41], "*", 10);
    strncpy(list[42], "*/", 10);
    strncpy(list[43], "+", 10);
    strncpy(list[44], ",", 10);
    strncpy(list[45], "-", 10);
    strncpy(list[46], ".", 10);
    strncpy(list[47], "..", 10);
    strncpy(list[48], "/", 10);
    strncpy(list[49], "/*", 10);
    strncpy(list[50], ":", 10);
    strncpy(list[51], ":=", 10);
    strncpy(list[52], ";", 10);
    strncpy(list[53], "<", 10);
    strncpy(list[54], "<=", 10);
    strncpy(list[55], "<>", 10);
    strncpy(list[56], "=", 10);
    strncpy(list[57], ">", 10);
    strncpy(list[58], ">=", 10);
    strncpy(list[59], "[", 10);
    strncpy(list[60], "]", 10);
}
void bianYi::createbianYi3() {
    inf.open("/home/ww/SCHOOL/curriculum/Third_Up/Compile/LAB/Compiler1/Test3.txt", ios::in);
    if (!inf) {
        cerr << "error,file could not be open" << endl;
        abort();
    }
    i = 1;
}
void bianYi::createbianYi4() {
    inf.open("/home/ww/SCHOOL/curriculum/Third_Up/Compile/LAB/Compiler1/Test4.txt", ios::in);
    if (!inf) {
        cerr << "error,file could not be open" << endl;
        abort();
    }
    i = 1;
}

void bianYi::createbianYi1() {
    inf.open("/home/ww/SCHOOL/curriculum/Third_Up/Compile/LAB/Compiler1/Test1.txt", ios::in);
    if (!inf) {
        cerr << "error,file could not be open" << endl;
        abort();
    }
    i = 1;
}

void bianYi::createbianYi2() {
    inf.open("/home/ww/SCHOOL/curriculum/Third_Up/Compile/LAB/Compiler1/Test2.txt", ios::in);
    if (!inf) {
        cerr << "error,file could not be open" << endl;
        abort();
    }
    i = 1;
}

void bianYi::createbianYi5() {
    inf.open("/home/ww/SCHOOL/curriculum/Third_Up/Compile/LAB/Compiler1/Test5.txt", ios::in);
    if (!inf) {
        cerr << "error,file could not be open" << endl;
        abort();
    }
    i = 1;
}




bianYi::bianYi() {};
bianYi::bianYi(char*fileName) {
    inf.open(fileName, ios::in);
    i = 1;
}

//如果token串在编码表中就加到 结果表 并返回1
int bianYi::looklist1(int begin, int end, char fuhao[10]) {
    for (int j = begin; j <= end; j++) {
        if (strcmp(list1.list[j], fuhao) == 0) {
            list3.add(j, 0, i);
            return 1;
        }
    }
    return 0;
}

//加到结果表中  如果在表2就返回1, 如果不在就加到2 并返回0
int bianYi::looklist2(char fuhao[10]) {
    for (int j = 1; j <= list2.idend - 1; j++) {
        if (strcmp(list2.list[j], fuhao) == 0) {  //如果在表2中，就加到结果表，并返回1
            list3.add(36, j, i);
            return 1;
        }
    }
    list2.add(fuhao);
    list3.add(36, list2.idend - 1, i);
    return 0;
}


//字符数组
int bianYi::looklist22(char fuhao[max3]) {
    for (int j = 1; j <= list2.idend - 1; j++) {
        if (strcmp(list2.list[j], fuhao) == 0) {
            list3.add(38, j, i);
            return 1;
        }
    }
    list2.add(fuhao);
    list3.add(38, list2.idend - 1, i);
    return 0;
}

//一个一个读取流中的字符 并 记录行号
char bianYi::getCh() {
    char c;
    if (inf.get(c)) {
        if (c == '\n')i++;
        return c;
    }
    else {
        i++;
        return NULL;
    }
}
bianYi::~bianYi() {
    inf.close();
}
void bianYi::ciFa() {
    char c;
    int j;
    c = getCh();  //从文件流中读取一个字符
    while (c != NULL) {
        while (c == ' ' || c == '\n' || c == '\t')c = getCh();  //过滤界符
        //如果是字母
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            char biaoShi[10];

            biaoShi[0] = c;
            int state = 0;
            for (j = 1; true; j++) {
                c = getCh();
                //如果还是字母
                if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))biaoShi[j] = c;
                //如果是数字，就转状态1
                else if (c >= 48 && c <= 57) {
                    biaoShi[j] = c;
                    state = 1;
                }
                //既不是字母也不是数字就退出
                else break;
            }
            biaoShi[j] = '\0';
            if (state == 0) { //可能是编码表中的内容
                if (looklist1(1, 35, biaoShi) == 0) {
                    looklist2(biaoShi);
                }
            }
            else looklist2(biaoShi);  //state1不在编码表中
        }
        //如果是数字
        else if (c >= 48 && c <= 57) {
            int n = c - '0';
            for (c = getCh(); c >= 48 && c <= 57; c = getCh())
                n = n * 10 + c - '0';
            list3.add(37, n, i);

        }
        //如果是‘'’ 接下来就按字符常数处理
        else if (c == '\'') {
            char temp[max4];
            c = getCh();
            for (j = 0; c != '\''&&c != '\n'; j++) {
                temp[j] = c;
                c = getCh();
            }
            if (c == '\n')cout << "error：Line" << i << "can't find '" << endl;
            temp[j] = '\0';
            c = getCh();

            looklist22(temp);  //对字符数组做操作
        }
        //否则，就是各种符号
        else {
            char hao[3];
            hao[0] = c;
            hao[1] = '\0';
            if (looklist1(39, 60, hao)) {  //如果是左括号
                c = getCh();
                hao[1] = c;
                hao[2] = '\0';
                if (strcmp(hao, "/*") == 0) { //如果是注释
                    list3.w--;
                    for (j = 0; c != '\n'&&c != NULL; j++) {

                        c = getCh();
                        if (c == '*') {
                            c = getCh();
                            if (c == '/')
                                break;
                        }
                    }
                    if (c == '\n' || c == NULL)cout << "error: Line " << i << "has a mistake.*/ " << endl;//
                    c = getCh();
                }
                else if (looklist1(39, 60, hao))
                {
                    c = getCh();
                    list3.w--;
                    list3.w--;
                    looklist1(39, 60, hao);
                }
            }
            else { /*cout << "error: Line " << i << "has a mistake." << endl;*/ c = getCh(); }
        }
    }
//    list3.print();
    cout<<endl;
}

