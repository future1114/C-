//Code1:
#include<iostream>
using namespace std;

void perm(int A[], int k, int n)
{
	int i;
	if (k == 1)
	{
		for (i = 0; i < n; i++)
		{
			cout << " " << A[i] << " ";
			if ((i + 1) % n == 0)
			{
				cout << endl;
			}
		}
	}
	else
	{
		for (i = n - k; i < n; i++)
		{
			swap(A[i], A[n - k]);
			perm(A, k - 1, n);
			swap(A[i], A[n - k]);
		}
	}
}

int main()
{
	int n, A[10], i;
	cout << "input : ";
	cin >> n;
	cout << endl;
	for (i = 0; i < n; i++)
	{
		A[i] = i + 1;
	}
	perm(A, n, n);
	return 0;
}
