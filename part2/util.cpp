#include"head.h"
int mytime = 0;              //表示正在取第几个sign
extern bianYi parse;            //词法分析
extern item sign;            //
void nextstat() {
    if (mytime<parse.list3.w)
        sign = parse.list3.result[mytime++];
}

item::item() {};
item::item(int x1, int x2) {
    x = x1;
    y = x2;
};
//
TFL& TFL::operator=(TFL &temp) {
    for (int z = 0; z<headt[0]; z++)
        headt[z] = temp.headt[z];
    for (int z = 0; z<headf[0]; z++)
        headf[z] = temp.headf[z];
    codebegin = temp.codebegin;
    return *this;
}
TFL::TFL(const TFL & temp) {
    for (int z = 0; z<temp.headt[0] + 1; z++)
        headt[z] = temp.headt[z];
    for (int z = 0; z<temp.headf[0] + 1; z++)
        headf[z] = temp.headf[z];
    codebegin = temp.codebegin;
}

void error() {
    cout << "Line: " << parse.list3.hang[mytime] << " has a mistake." << endl;
    exit(1);
}
