#include<iostream>
#include<ctime>
using namespace std;

__int64  fun(int n)
{
	if (n < 0)
	{
		cout << "illegal" << endl;
		return 0;
	}
	else if (n==0)
	{
		return 1;
	}
	else
	{
		return n * fun(n - 1);
	}
}
int main()
{
	int n;
	clock_t startTime, endTime;
	cout << "input : ";
	cin >> n;
	startTime = clock();
	cout << fun(n) << endl;
	endTime = clock(); 
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}