#include <NTL/ZZ.h>  
NTL_CLIENT
#include<fstream>
using namespace std;

int main() {
	ZZ p, q;
	long len = 512;
	SetSeed(to_ZZ((int)time(NULL)));
	p = GenPrime_ZZ(len, 80);//生成bit长度的大素数
	q = GenPrime_ZZ(len, 80);
	ZZ n = p * q;
	ZZ fai_n = (p - 1) * (q - 1);//欧拉数
	cout << "p = " << p << endl << endl;
	cout << "q = " << q << endl << endl;
	cout << "n = " << n << endl << endl;
	cout << "fai_n = " << fai_n << endl << endl;
	ZZ publicKey_e, priKey_d;
	while (1) { //确保模逆计算成功退出
		publicKey_e = RandomBnd(fai_n);//确保随机生成的公钥是小于fai_n
		SetBit(publicKey_e, 0);//确保公钥是奇数
		cout << "publicKey_e = " << publicKey_e << endl << endl;
		if (InvModStatus(priKey_d, publicKey_e, fai_n) == 0) {
			//求公钥
			break;
		}
	}
	cout << "priKey_d = " << priKey_d << endl << endl;
	ZZ rand_n = RandomBnd(n);
	ZZ c = PowerMod(rand_n, publicKey_e, n); //加密
	ZZ get_n = PowerMod(c, priKey_d, n); //解密
	cout << "rand_n = " << rand_n << endl << endl;
	cout << "c = " << c << endl << endl;
	if (rand_n == get_n) {
		cout << "Success" << endl;
	}
	else {
		cout << "False" << endl;
	}
	ofstream fout("源码cout.txt");
	fout << p << "\n" << q << "\n" << n << "\n" << fai_n << "\n" << publicKey_e << "\n" << priKey_d << "\n" << endl;
	return 1;
}