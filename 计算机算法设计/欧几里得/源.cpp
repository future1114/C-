#include<iostream>
using namespace std;
#include "ojld.h"
#include<ctime>

int main()
{
	clock_t startTime, endTime;
	for (int n = 10; n <= 10000; n = n * 10)
	{
		startTime = clock();//计时开始
		int max = 0;
		int min = 1000;
		__int64 sum = 0;
		for (int i = n; i > 1; i--)
		{
			for (int i1 = n; i1 > 1; i1--)
			{
				ojld gcd(i, i1);
				int z;
				z = gcd.zzf();
				sum = sum + z;
				if (z > max)
					max = z;
				if (z < min)
					min = z;
			}
		}
		float avg;
		avg = sum / n;
		cout << "max is " << max<<" ;" << "min is " << min<<" ;" << "avg is " << avg << endl;
		endTime = clock();//计时结束
		cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	return 0;
}