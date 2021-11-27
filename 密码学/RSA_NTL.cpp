#include <NTL/ZZ.h>  
NTL_CLIENT
#include<fstream>
using namespace std;

int main() {
	ZZ p, q;
	long len = 512;
	SetSeed(to_ZZ((int)time(NULL)));
	p = GenPrime_ZZ(len, 80);//����bit���ȵĴ�����
	q = GenPrime_ZZ(len, 80);
	ZZ n = p * q;
	ZZ fai_n = (p - 1) * (q - 1);//ŷ����
	cout << "p = " << p << endl << endl;
	cout << "q = " << q << endl << endl;
	cout << "n = " << n << endl << endl;
	cout << "fai_n = " << fai_n << endl << endl;
	ZZ publicKey_e, priKey_d;
	while (1) { //ȷ��ģ�����ɹ��˳�
		publicKey_e = RandomBnd(fai_n);//ȷ��������ɵĹ�Կ��С��fai_n
		SetBit(publicKey_e, 0);//ȷ����Կ������
		cout << "publicKey_e = " << publicKey_e << endl << endl;
		if (InvModStatus(priKey_d, publicKey_e, fai_n) == 0) {
			//��Կ
			break;
		}
	}
	cout << "priKey_d = " << priKey_d << endl << endl;
	ZZ rand_n = RandomBnd(n);
	ZZ c = PowerMod(rand_n, publicKey_e, n); //����
	ZZ get_n = PowerMod(c, priKey_d, n); //����
	cout << "rand_n = " << rand_n << endl << endl;
	cout << "c = " << c << endl << endl;
	if (rand_n == get_n) {
		cout << "Success" << endl;
	}
	else {
		cout << "False" << endl;
	}
	ofstream fout("Դ��cout.txt");
	fout << p << "\n" << q << "\n" << n << "\n" << fai_n << "\n" << publicKey_e << "\n" << priKey_d << "\n" << endl;
	return 1;
}