#include<iostream>
#include<string>
using namespace std;
string change(char c)//����ĸת��Ϊ������
{
     string data;
    for(int i=0;i<8;i++)
    {
        //  data+=c&(0x01<<i);
        if ( ( c >>(i-1) ) & 0x01 == 1 )
        {
            data+="1";
        }
        else
        {
            data+="0";
        }
    }
    for(int a=1;a<5;a++)
    {
        char x=data[a];
        data[a]=data[8-a];
        data[8-a]=x;
    }
   return data;
}
string change1(string &data)//��������ת��Ϊ��ĸ
{
    string result;
    char c='\0';
    for(int i=0;i<8;i++)
    {
        if(data[i]=='1') {
            c=(c<<1)|1;
        }
        else c=c<<1;
    }
   // cout<<c;
    result+=(unsigned char)c;
    return  result;
}
int main(){
    string ax;
    int nx = 0;
    char a[16] = {'a','b','c','d','e','f','g','h','a','b','c','d','e','f','g','h'};
    char b[129];
    for (int i = 0; i < 16;i++){
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 16; i++)
    { //��16����ĸת�ɶ�����,�洢��128λ���ȵ��ַ����鵱��
        ax = change(a[i]);
        for (int j = 0; j < 8; j++)
        {
            cout << ax[j];
            b[nx] = ax[j];
            nx++;
        }
        cout << endl;
        }
    cout << endl;
    for (int i = 1; i < 129; i++){//У��д�������Ƿ�ɹ�
        cout << b[i - 1];
        if (i%8==0){
            cout << endl;
        }
    }
    string c,d,e;
    int ix = 0;
    for (int i = 0; i < 16;i++){//��������ת��16����ĸ
        c = b[ix];
        for (int j = 0; j < 8;j++){
            ix++;
            e = b[ix];
            c.append(e);
        }
        d = change1(c);
        cout << " " << d ;
    }
    system("pause");

    return 0;
}
