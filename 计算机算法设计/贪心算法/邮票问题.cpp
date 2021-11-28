#include<iostream>
using namespace std;

void sort(int *n,int s){ //冒泡排序法
    int temp;
    for (int i = 0; i < s;i++) {                  
		for (int j = 0; j < s - i;j++) {     
			if (n[j] > n[j + 1]) {
				temp = n[j];
				n[j] = n[j + 1];
				n[j + 1] = temp;
			}
		}
	}

}

int main()
{
    int s = 0; //邮票总个数
    int i;
    int cost; //总需面额
    cout << "需贴多收钱的邮票：";
    cin >> cost;
    cout << "一共有多少张邮票" << endl;
    cin >> s; //邮票个数
    s = s - 1;
    int* x1 = new int[s];
    cout << "输入邮票的面值" << endl;
    for (int m = 0; m <= s;m++){
        cin >> x1[m];
    }
    int sum = 0;
    sort(x1,s); //对总面额进行排序
    for ( i = 0; i <= s;i++){ //从大到小选取总额的邮票
        sum = sum + x1[s - i];
        if (sum>=cost)
            break;
    }
    cout << "已经使用 " << i + 1 << " 张邮票" << endl;
    cout << "总面额为 " << sum << " 元" << endl;
    cout << "使用邮票的面额分别为：";
    for (int j = 0; j <= i;j++){
        cout << x1[s - j] << "元"
             << " ";
    }
    cout << endl;
    delete[] x1;
    return 0;
}
