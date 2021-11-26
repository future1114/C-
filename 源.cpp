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
	// ���ɳ���ΪvecLen�ĳ���������A��
	Vec<ZZ> A; // ��̬����A����ͷ�ļ�vector.h������
	long vecLen = 100; 
	A.SetLength(vecLen);// A���鳤��Ϊ vecLen
	ZZ sum = to_ZZ(0);
	cout << "A=" << endl;
	for (int i = 0; i < vecLen; i++) {
		A[i] = sum + RandomBits_ZZ(16) + 1;// ����ÿһ���ǰ��������ĺͲ�����16bit���ȵ�����
		cout << A[i] << endl;		                   //+1ȷ�������Ϊ0ʱ��1.
		sum = sum + A[i];
	}
	cout << endl << "sum_A = " << sum << endl;
	// ѡ����Կt��k�����ɹ�ԿB
	ZZ t, k, t_inv;
	k = sum + RandomBits_ZZ(16) + 1;// ����һ����A���ܺʹ�������k
	while (1) {
		t = RandomBnd(k); //�������һ����kС�������
		if (InvModStatus(t_inv, t, k) == 0) { //��t����Ԫt_inv ==0��ʾ
			break; // ����ҵ���k���ʵ������t�����˳�while
		}
	}
	cout << "t = " << t << endl;
	cout << "k = " << k << endl;
	cout << "B = " << endl;
	Vec<ZZ> B;
	B.SetLength(vecLen); // ���й�ԿB��˽ԿA�ĳ�����ͬ
	for (int j = 0; j < vecLen; j++) {
		B[j] = MulMod(A[j], t, k);  // B��ÿ��Ԫ��= A��ÿ��Ԫ�� * t mod k
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
	for (int i = 0; i < 16; i++) { //��16����ĸת�ɶ�����,�洢��128λ���ȵ��ַ����鵱��
		ax = char_string(miWen[i]);
		for (int j = 0; j < 8; j++) {
			in_m[nx] = ax[j];
			nx++;
		}
	}
	unsigned char ou_m[129] = "";// ���ܺ�����Ŀռ�
	////�ù�ԿB��������in_m�õ�����c
	ZZ c = to_ZZ(0);
	for (int i = 0; i < vecLen; i++) {
		if (in_m[i] == '1') {
			c = B[i] + c; //������Ķ�ӦԪ��Ϊ1������϶�Ӧλ��B��Ԫ��ֵ
		}
	}
	cout << "c = " << c << endl;

	//// ��˽ԿA��t��k����c�õ�����out_m
	ZZ c_1 = MulMod(c, t_inv, k);// ����c��˽Կ t����Ԫt_inv �Լ�k �����Ӧ˽ԿA�� ���ĺ�c_1
	for (int j = vecLen - 1; j >= 0; j--) { // ���������н��ܵõ������ķ���out_m������ 
		if (c_1 >= A[j]){
			ou_m[j] = '1'; // �ʼ�ĵ�һ�������ַ�'1'��Ӧ����һ������ͬ��
			c_1=c_1-A[j];
		}
		else{
			ou_m[j] = '0';
		}
	}
	cout << endl;
	////  ��ӡ����in_m�ͽ��ܵõ����ĵ�out_m���۲��Ƿ���ͬ
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
	for (int i = 0; i < 16; i++) {//��������ת��16����ĸ
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
