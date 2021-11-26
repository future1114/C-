#include<iostream>
#include<string>
using namespace std;
string change(char c)//将字母转化为二进制
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
string change1(string &data)//将二进制转化为字母
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
    { //将16个字母转成二进制,存储在128位长度的字符数组当中
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
    for (int i = 1; i < 129; i++){//校验写入数组是否成功
        cout << b[i - 1];
        if (i%8==0){
            cout << endl;
        }
    }
    string c,d,e;
    int ix = 0;
    for (int i = 0; i < 16;i++){//将二进制转成16个字母
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
