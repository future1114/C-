#pragma once
class ojld
{
	private:
		int a, b;
		int c;
	public:
		ojld(int m, int n)
		{
			a = m;
			b = n;
			c = 0;
		}
		int zzf()
		{
			int r;
			while (b != 0)
			{
				r = a % b;
				a = b;
				b = r;
				c++;
			}
			return c;
		}


};

