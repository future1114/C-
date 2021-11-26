#include <NTL/ZZ.h>
#include <NTL/vector.h>

using namespace std;
using namespace NTL;

int main()
{
	////////////// 生成长度为vecLen的超递增序列A
	Vec<ZZ> A;  // 动态数组A，在头文件vector.h中声明
	long vecLen = 100; // 数组长度
	
	A.SetLength(vecLen); // 设置动态数组A的长度为vecLen
	ZZ sum = to_ZZ(0);  // sum初始为0
	
	cout << "A=" << endl;
	for (int i = 0; i < vecLen; i++) {				
		A[i] = sum + RandomBits_ZZ(16)+1; // 后面每一项比前面所有项的和不超过16bit长度的数，+1确保随机数为0时加1.
		cout << A[i] << endl;
		sum = sum + A[i];
	}	
	cout << endl<<"sum_A="<< sum << endl;

	////////////// 选择私钥 t和k ，生成公钥B
	ZZ t, k, t_inv;
	k=sum+ RandomBits_ZZ(16) + 1; // 产生一个比 A的总和大的随机数k
	while (1) {
		t = RandomBnd(k); // 随机产生一个比k小的随机数t
		if (InvModStatus(t_inv, t, k) == 0) {  // 求t的逆元t_inv，==0表示逆元存在
			break;  // 如果找到与k互质的随机数t，则退出while.
		}
	}
	cout << endl <<"t="<< t << endl;
	cout << "k=" << k << endl << endl;

	cout << "B=" << endl;
	Vec<ZZ> B;
	B.SetLength(vecLen);  // 序列公钥B和私钥A的长度相同
	for (int j = 0; j < vecLen;j++) {
		B[j]= MulMod(A[j],t,k);  // B的每个元素= A的每个元素 * t mod k
		cout << B[j] << endl;
	}

	////////////// 输入明文01字符串,确保vecLen< 128
	unsigned char in_m[129] = "01010101101101000101010110110100010101011011010001010101101101000101010110110100010101011011010001010101101101000101010110110100";
	unsigned char ou_m[129] = ""; // 解密后的明文空间

	////////////// 用公钥B加密明文in_m得到密文c
	ZZ c = to_ZZ(0);  // 密文c初始化为0
	for (int i = 0; i < vecLen; i++) {
		if (in_m[i] == '1') c = B[i] + c; //如果明文对应元素为1，则加上对应位置B中元素值
	}
	cout << endl << "c="<<c << endl;

	////////////// 用私钥A、t、k解密c得到明文out_m
	ZZ c_1 = MulMod(c, t_inv, k); // 密文c用私钥 t的逆元t_inv 以及k 算出对应私钥A的 明文和c_1
	for (int j = vecLen - 1; j >= 0;j--) {  // 超递增序列解密得到的明文放在out_m数组中 
		if (c_1 >= A[j]) {  /// 最开始的第一个明文字符'1'对应的数一定是相同的
			ou_m[j] = '1';
			c_1 = c_1- A[j];
		}
		else
			ou_m[j] = '0';
	}

	////////////// 打印明文in_m和解密得到明文的out_m，观察是否相同
	cout << endl << "in_m=";
	for (int i = 0; i < vecLen; i++) {
		cout << in_m[i];
	}

	cout << endl << "ou_m=";
	for (int i = 0; i < vecLen; i++) {
		cout << ou_m[i];
	}
	cout << endl;
}


//#include <NTL/ZZ.h>
//#include <NTL/vector.h>
//
//using namespace std;
//using namespace NTL;
//
//int main()
//{
//	Vec<ZZ> v;
//	cin >> v;
//
//	long n = v.length();
//	cout << n << endl;
//	v.SetLength(2 * n);
//
//	long i;
//	for (i = 0; i < n; i++)
//		v[n + i] = v[n - 1 - i];
//
//	cout << v << "\n";
//}

//#include <NTL/ZZ.h>
//#include <NTL/matrix.h>
//
//using namespace std;
//using namespace NTL;
//
//void mul(Mat<ZZ>& X, const Mat<ZZ>& A, const Mat<ZZ>& B)
//{
//	long n = A.NumRows();
//	long l = A.NumCols();
//	long m = B.NumCols();
//
//	if (l != B.NumRows())
//		Error("matrix mul: dimension mismatch");
//
//	X.SetDims(n, m); // make X have n rows and m columns
//
//	long i, j, k;
//	ZZ acc, tmp;
//
//	for (i = 1; i <= n; i++) {
//		for (j = 1; j <= m; j++) {
//			acc = 0;
//			for (k = 1; k <= l; k++) {
//				mul(tmp, A(i, k), B(k, j));
//				add(acc, acc, tmp);
//			}
//			X(i, j) = acc;
//		}
//	}
//}
//
//int main()
//{
//	Mat<ZZ> A,B,X;
//	cin >> A;
//	cin >> B;
//	mul(X, A, B);
//	cout << X << endl;
//
//	cout << X<< "\n";
//}



//#include <NTL/mat_ZZ.h>
//#include <NTL/mat_poly_ZZ.h>
//#include <NTL/HNF.h>
//
//NTL_CLIENT
//
//int main()
//{
//	mat_ZZ B, X;
//	vec_ZZ v, w;
//
//	cin >> B;
//	cin >> v;
//
//	ZZ d;
//
//	double t;
//	cerr << "matrix inverse...";
//	t = GetTime();
//	inv(d, X, B);
//	cerr << (GetTime() - t) << "\n";
//
//	cout << d << "\n";
//	cout << X << "\n";
//
//	cout << "\n\n\n";
//
//	cerr << "hensel solve...";
//	t = GetTime();
//	HenselSolve1(d, w, B, v);
//	cerr << (GetTime() - t) << "\n";
//
//	cout << d << "\n";
//	cout << w << "\n";
//
//	cout << "\n\n\n";
//
//	ZZX f;
//
//	cerr << "char poly...";
//	t = GetTime();
//	CharPoly(f, B);
//	cerr << (GetTime() - t) << "\n";
//
//	cout << f << "\n";
//
//	cout << "\n\n\n";
//
//	cerr << "HNF...";
//	t = GetTime();
//	HNF(X, B, d);
//	cerr << (GetTime() - t) << "\n";
//
//	cout << X;
//
//	return 0;
//}
