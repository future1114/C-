#include<NTL/ZZ.h>
#include<NTL/vector.h>
#include<string>
#include<iostream>

using namespace std;
using namespace NTL;
string char_string(unsigned char c)
{
	string data;
	for (int i = 0; i < 8; i++)
	{
		if ((c >> (i - 1)) & 0x01 == 1)
		{
			data += "1";
		}
		else
		{
			data += "0";
		}
	}
	for (int a = 1; a < 5; a++)
	{
		unsigned char x = data[a];
		data[a] = data[8 - a];
		data[8 - a] = x;
	}
	return data;
}
string string_char(string data)
{
	string result;
	char c = '\0';
	for (int i = 0; i < 8; i++)
	{
		if (data[i] == '1') {
			c = (c << 1) | 1;
		}
		else c = c << 1;
	}
	// cout<<c;
	result += (unsigned char)c;
	return  result;
}
int main() {
	// 生成长度为vecLen的超递增序列A；
	Vec<ZZ> A; // 动态数组A，在头文件vector.h中声明
	long vecLen = 100; 
	A.SetLength(vecLen);// A数组长度为 vecLen
	ZZ sum = to_ZZ(0);
	cout << "A=" << endl;
	for (int i = 0; i < vecLen; i++) {
		A[i] = sum + RandomBits_ZZ(16) + 1;// 后面每一项比前面所有项的和不超过16bit长度的数，
		cout << A[i] << endl;		                   //+1确保随机数为0时加1.
		sum = sum + A[i];
	}
	cout << endl << "sum_A = " << sum << endl;
	// 选择密钥t和k，生成公钥B
	ZZ t, k, t_inv;
	k = sum + RandomBits_ZZ(16) + 1;// 产生一共比A的总和大的随机数k
	while (1) {
		t = RandomBnd(k); //随机产生一个比k小的随机数
		if (InvModStatus(t_inv, t, k) == 0) { //求t的逆元t_inv ==0表示
			break; // 如果找到与k互质的随机数t，则退出while
		}
	}
	cout << "t = " << t << endl;
	cout << "k = " << k << endl;
	cout << "B = " << endl;
	Vec<ZZ> B;
	B.SetLength(vecLen); // 序列公钥B和私钥A的长度相同
	for (int j = 0; j < vecLen; j++) {
		B[j] = MulMod(A[j], t, k);  // B的每个元素= A的每个元素 * t mod k
		cout << B[j] << endl;
	}
	unsigned char in_m[129];
	//unsigned char in_m[129] = "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101";
	string ax;
	int nx = 0;
	char miWen[16];
	cout << "input 16 char :" << endl;
	for (int ix = 0; ix < 16; ix++) {
		cin >> miWen[ix];
	}
	for (int i = 0; i < 16; i++) { //将16个字母转成二进制,存储在128位长度的字符数组当中
		ax = char_string(miWen[i]);
		for (int j = 0; j < 8; j++) {
			in_m[nx] = ax[j];
			nx++;
		}
	}
	unsigned char ou_m[129] = "";// 解密后的明文空间
	////用公钥B加密明文in_m得到密文c
	ZZ c = to_ZZ(0);
	for (int i = 0; i < vecLen; i++) {
		if (in_m[i] == '1') {
			c = B[i] + c; //如果明文对应元素为1，则加上对应位置B中元素值
		}
	}
	cout << "c = " << c << endl;

	//// 用私钥A、t、k解密c得到明文out_m
	ZZ c_1 = MulMod(c, t_inv, k);// 密文c用私钥 t的逆元t_inv 以及k 算出对应私钥A的 明文和c_1
	for (int j = vecLen - 1; j >= 0; j--) { // 超递增序列解密得到的明文放在out_m数组中 
		if (c_1 >= A[j]){
			ou_m[j] = '1'; // 最开始的第一个明文字符'1'对应的数一定是相同的
			c_1=c_1-A[j];
		}
		else{
			ou_m[j] = '0';
		}
	}
	cout << endl;
	////  打印明文in_m和解密得到明文的out_m，观察是否相同
	cout << "in_v = ";
	for (int i = 0; i < vecLen; i++) {
		cout << in_m[i];
	}
	cout << endl << "ou_v = ";
	for (int i = 0; i < vecLen; i++) {
		cout << ou_m[i];
	}
	cout << endl;
	string tmpe, d, e;
	int ix = 0;
	//char ex = '\0';
	for (int i = 0; i < 16; i++) {//将二进制转成16个字母
		c = ou_m[ix];
		for (int j = 0; j < 7; j++) {
			ix++;
			e = ou_m[ix];
			//cout << e << endl;
			tmpe.append(e);
		}
		//tmpe.append('\0');
		d = string_char(tmpe);
		ix++;
		cout << d << "    ";
	}
	cout << endl;
	return 0;
}
