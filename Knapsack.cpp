#include <NTL/ZZ.h>
#include <NTL/vector.h>

using namespace std;
using namespace NTL;

int main()
{
	////////////// ���ɳ���ΪvecLen�ĳ���������A
	Vec<ZZ> A;  // ��̬����A����ͷ�ļ�vector.h������
	long vecLen = 100; // ���鳤��
	
	A.SetLength(vecLen); // ���ö�̬����A�ĳ���ΪvecLen
	ZZ sum = to_ZZ(0);  // sum��ʼΪ0
	
	cout << "A=" << endl;
	for (int i = 0; i < vecLen; i++) {				
		A[i] = sum + RandomBits_ZZ(16)+1; // ����ÿһ���ǰ��������ĺͲ�����16bit���ȵ�����+1ȷ�������Ϊ0ʱ��1.
		cout << A[i] << endl;
		sum = sum + A[i];
	}	
	cout << endl<<"sum_A="<< sum << endl;

	////////////// ѡ��˽Կ t��k �����ɹ�ԿB
	ZZ t, k, t_inv;
	k=sum+ RandomBits_ZZ(16) + 1; // ����һ���� A���ܺʹ�������k
	while (1) {
		t = RandomBnd(k); // �������һ����kС�������t
		if (InvModStatus(t_inv, t, k) == 0) {  // ��t����Ԫt_inv��==0��ʾ��Ԫ����
			break;  // ����ҵ���k���ʵ������t�����˳�while.
		}
	}
	cout << endl <<"t="<< t << endl;
	cout << "k=" << k << endl << endl;

	cout << "B=" << endl;
	Vec<ZZ> B;
	B.SetLength(vecLen);  // ���й�ԿB��˽ԿA�ĳ�����ͬ
	for (int j = 0; j < vecLen;j++) {
		B[j]= MulMod(A[j],t,k);  // B��ÿ��Ԫ��= A��ÿ��Ԫ�� * t mod k
		cout << B[j] << endl;
	}

	////////////// ��������01�ַ���,ȷ��vecLen< 128
	unsigned char in_m[129] = "01010101101101000101010110110100010101011011010001010101101101000101010110110100010101011011010001010101101101000101010110110100";
	unsigned char ou_m[129] = ""; // ���ܺ�����Ŀռ�

	////////////// �ù�ԿB��������in_m�õ�����c
	ZZ c = to_ZZ(0);  // ����c��ʼ��Ϊ0
	for (int i = 0; i < vecLen; i++) {
		if (in_m[i] == '1') c = B[i] + c; //������Ķ�ӦԪ��Ϊ1������϶�Ӧλ��B��Ԫ��ֵ
	}
	cout << endl << "c="<<c << endl;

	////////////// ��˽ԿA��t��k����c�õ�����out_m
	ZZ c_1 = MulMod(c, t_inv, k); // ����c��˽Կ t����Ԫt_inv �Լ�k �����Ӧ˽ԿA�� ���ĺ�c_1
	for (int j = vecLen - 1; j >= 0;j--) {  // ���������н��ܵõ������ķ���out_m������ 
		if (c_1 >= A[j]) {  /// �ʼ�ĵ�һ�������ַ�'1'��Ӧ����һ������ͬ��
			ou_m[j] = '1';
			c_1 = c_1- A[j];
		}
		else
			ou_m[j] = '0';
	}

	////////////// ��ӡ����in_m�ͽ��ܵõ����ĵ�out_m���۲��Ƿ���ͬ
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
