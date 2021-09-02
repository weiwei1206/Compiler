#include<fstream>
#include<iostream>
#include<string.h>
using namespace std;

char *word[36]={"","and","array","begin","bool","call","case",
"char","constant","dim","do","else","end","false","for","if","input", 
"integer","not","of","or","printTwotuple", "procedure","program","read",
"real","repeat","set","stop","then","to","true","until","var","while","write"};
int a[10000],b[10000];

char myCopy[1000][1000];
char mybuffer[1000000];
int line=1,biaoji1=1,num=1,abnum=1,charnum=1;
void scaner();
void AA_inputLetter();
void D_inputNumber();
void GH_Notes();
void IK_Symbol();
void FF_characterConstants();
void inputStream();
void printTwotuple();
bool wrong=false;

//µ±¿ÉÄÜÊÇÆäËû·ûºÅ
void IK_Symbol()
{
    //ŽŠÀíË«œç·û
    if(mybuffer[num]=='.'&&mybuffer[num+1]=='.')
	{
		a[abnum]=47;
		b[abnum]=0;
		abnum++;
		num+=2;
	}
    else if(mybuffer[num]==':'&&mybuffer[num+1]=='=')
	{
		a[abnum]=51;
		b[abnum]=0;
		abnum++;
		num+=2;
	}
    else if(mybuffer[num]=='<'&&mybuffer[num+1]=='=')
	{
		a[abnum]=54;
		b[abnum]=0;
		abnum++;
		num+=2;
	}
    else if(mybuffer[num]=='<'&&mybuffer[num+1]=='>')
	{
		a[abnum]=55;
		b[abnum]=0;
		abnum++;
		num+=2;
	}
    else if(mybuffer[num]=='>'&&mybuffer[num+1]=='=')
	{
		a[abnum]=58;
		b[abnum]=0;
		abnum++;
		num+=2;
	}
    //ŽŠÀíµ¥œç·û
    else if(mybuffer[num]=='(')
	{
		a[abnum]=39;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]==')')
	{
		a[abnum]=40;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='*')
	{
		a[abnum]=41;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='+')
	{
		a[abnum]=43;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]==',')
	{
		a[abnum]=44;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='-')
	{
		a[abnum]=45;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='.')
	{
		a[abnum]=46;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='/')
	{
		a[abnum]=48;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]==':')
	{
		a[abnum]=50;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]==';')
	{
		a[abnum]=52;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='<')
	{
		a[abnum]=53;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='=')
	{
		a[abnum]=56;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='>')
	{
		a[abnum]=57;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]=='[')
	{
		a[abnum]=59;
		b[abnum]=0;
		abnum++;
		num++;
	}
    else if(mybuffer[num]==']')
	{
		a[abnum]=60;
		b[abnum]=0;
		abnum++;
		num++;
	}
	else
	{
		wrong=true;
        cout<<"Line "<<line<<":"<<"Illegal symbol:"<<mybuffer[num]<<" appears!"<<endl;
		num++;
	}
	if(num<charnum)
        scaner();
}

//œ«ÎÄŒþÄÚÈÝÈ«²¿¶ÁÈë»º³åÇø
void inputStream()
{
    string n;
    char ch;
	cin>>n;
    string address="/home/ww/SCHOOL/curriculum/Third_Up/Compile/LAB/Compiler/"+n;
    ifstream infile(address);
	while(infile.get(ch))
        mybuffer[charnum++]=ch;
}

//µ±ÊäÈëµÄÊÇÊý×Ö
void D_inputNumber()
{
	char store[1000];
    store[0]=mybuffer[num];
	num++;
	int i=0;
    bool isD_inputNumber=true;
    while((mybuffer[num]>='a'&&mybuffer[num]<='z')||(mybuffer[num]>='A'&&mybuffer[num]<='Z')||(mybuffer[num]>='0'&&mybuffer[num]<='9'))
	{
        store[++i]=mybuffer[num];
        if(mybuffer[num]<'0'||mybuffer[num]>'9')
            isD_inputNumber=false;
		num++;
	}
	int l1=i+1;
    if(isD_inputNumber)
		a[abnum]=37;
	else
	{
		wrong=true;
        cout<<"Line "<<line<<":"<<"Illegal identifier occurred!"<<endl;
	}
	store[l1]='\0';
	for(i=1;i<biaoji1;i++)
	{
        int j=strcmp(myCopy[i],store);
        if(strcmp(myCopy[i],store)==0)
		{
			b[abnum]=i;
			abnum++;
			break;
		}
	}	
	if(i==biaoji1)
	{
		b[abnum]=biaoji1;
        strcpy(myCopy[biaoji1],store);
	    biaoji1++;
		abnum++;
	}
	if(num<charnum)
	{
        if(mybuffer[num]==' ')scaner();
        else if(mybuffer[num]=='\n')scaner();
        else if(mybuffer[num]=='/'&&mybuffer[num+1]=='*')num+=2,GH_Notes();
        else if(mybuffer[num]=='\'')FF_characterConstants();
        else IK_Symbol();
	}
}

void printTwotuple()
{
	if(!wrong)
	{
		int i;
	    for(i=1;i<abnum;i++)
		{
			cout<<"("<<a[i]<<",";
		    if(b[i])
				cout<<b[i];
		    else cout<<"-";
		    cout<<")   ";
		    if(i%5==0)
			    cout<<endl;
		}
	cout<<endl;
	}
}

void scaner()
{
    while(num<charnum)  //µ±»¹Ã»¶ÁÍêÏÖÓÐ×Ö·û
    {
        //Èç¹ûÊÇ×ÖÄž
        if((mybuffer[num]>='a'&&mybuffer[num]<='z')||(mybuffer[num]>='A'&&mybuffer[num]<='Z'))
            AA_inputLetter();
        //Èç¹ûÊÇÊý×Ö
        else if(mybuffer[num]>='0'&&mybuffer[num]<='9')
            D_inputNumber();
        //Èç¹ûÊÇ¡®
        else if(mybuffer[num]=='\'')
            FF_characterConstants();
        //Èç¹ûÊÇ/
        else if(mybuffer[num]=='/')
		{
            if(mybuffer[num+1]=='*'){
                num+=2;GH_Notes();
            }
            //Èç¹ûÊÇÆäËû·ûºÅ
            else IK_Symbol();
		}
        //Èç¹ûÊÇ¿ÕžñµÈ·ûºÅ
        else if(mybuffer[num]=='\n')
			line++,num++;
        else if(mybuffer[num]==' ')
			num++;
		else
            IK_Symbol();
	}
}

//µ±¿ÉÄÜÊÇ×¢ÊÍ
void GH_Notes()
{
    while(mybuffer[num]!='*'||mybuffer[num+1]!='/')
	{
        if(mybuffer[num]=='\n'||num>=charnum)
		{
			wrong=true;
            cout<<"Line "<<line<<":"<<"missing right symbol'*/'!"<<endl;
			line++;
			num++;
			break;
		}
		num++;
	}
    if(mybuffer[num]=='*'||mybuffer[num+1]=='/')
	    num+=2;
	if(num<charnum)
        scaner();
}

//µ±ÊäÈëµÄÊÇ×ÖÄž
void AA_inputLetter()
{
	char store[1000];
    store[0]=mybuffer[num];
	num++;
	int i=1;
    while((mybuffer[num]>='a'&&mybuffer[num]<='z')||(mybuffer[num]>='A'&&mybuffer[num]<='Z')||(mybuffer[num]>='0'&&mybuffer[num]<='9'))
        store[i++]=mybuffer[num++];
	int l1=i;
	store[l1]='\0';
    //Èç¹ûÊÇ±£Áô×ÖºÍ²Œ¶û³£Á¿
	for(i=1;i<=35;i++)
	{
		if(strcmp(word[i],store)==0)
		{
			a[abnum]=i;
			b[abnum]=0;
			abnum++;
			break;
		}
	}
    //Èç¹ûÊÇ±êÊ¶·û
	if(i==36)
	{
		for(i=1;i<biaoji1;i++)
		{
            if(strcmp(myCopy[i],store)==0)
			{
				a[abnum]=36;
				b[abnum]=i;
				abnum++;
				break;
			}
		}
		if(i==biaoji1)
		{
			a[abnum]=36;
			b[abnum]=biaoji1;
			abnum++;
            strcpy(myCopy[biaoji1],store);
			biaoji1++;
		}
	}
	if(num<charnum)
	{
        if(mybuffer[num]==' ')scaner();
        else if(mybuffer[num]=='\n')scaner();
        else if(mybuffer[num]=='/'&&mybuffer[num+1]=='*')num=+2,GH_Notes();
        else if(mybuffer[num]=='\'')FF_characterConstants();
        else IK_Symbol();
	}
}

//µ±¿ÉÄÜÊÇ×Ö·û³£Á¿
void FF_characterConstants()
{
	char store[1000];
    store[0]=mybuffer[num];
	int i=0;
	num++;
    while(mybuffer[num]!='\'')
	{
        if(mybuffer[num]=='\n'||num>=charnum)
		{
		    wrong=true;
            cout<<"Line "<<line<<":"<<"Missing right single quote!"<<endl;
			line++;
			break;
		}
        store[++i]=mybuffer[num];
		num++;
	}
	int l1=i+1;
	store[l1]='\0';
	num++;
	for(i=1;i<biaoji1;i++)
	{
        if(strcmp(myCopy[i],store)==0)
		{
			a[abnum]=38;
			b[abnum]=i;
			abnum++;
			break;
		}
	}
	if(i==biaoji1)
	{
		a[abnum]=38;
		b[abnum]=biaoji1;
		abnum++;
        strcpy(myCopy[biaoji1],store);
		biaoji1++;
	}
	if(num<charnum)
	{
        if(mybuffer[num]==' ')scaner();
        else if((mybuffer[num]>='a'&&mybuffer[num]<='z')||(mybuffer[num]>='A'&&mybuffer[num]<='Z'))AA_inputLetter();
        else if(mybuffer[num]>='0'&&mybuffer[num]<='9')D_inputNumber();
        else if(mybuffer[num]=='\n')scaner();
        else if(mybuffer[num]=='/'&&mybuffer[num+1]=='*'){num=+2;GH_Notes();}
        else if(mybuffer[num]=='\'')FF_characterConstants();
        else IK_Symbol();
	}
}

int main()
{
    while(1){
        line=1,biaoji1=1,num=1,abnum=1,charnum=1;
        cout<<endl<<endl<<endl;
        cout<<"WeiWei"<<endl;
        cout<<"201630970798"<<endl;
        cout<<"JK1"<<endl;
        cout<<endl<<endl;
        cout<<"Please input the program_number:";
        inputStream();
        scaner();
        printTwotuple();
    }

	return 0;
}
