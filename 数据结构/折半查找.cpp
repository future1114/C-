#include<iostream>
using namespace std;

void sort(int * a, int len)
{
    int i, j, t;
    for (i = 0; i < len - 1; ++i)
    {
        for (j = 0; j < len - 1 - i; ++j)
        {
            if (a[j] > a[j + 1]) // >��ʾ���� <��ʾ����
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
    cout << endl;
    for (i = 0; i < len; i++)
    {
        cout <<"a ["<< i + 1 << "] : " << a[i] << "   ";
    }
    cout << endl;
}
int binary_search(int key,int a[],int n) 
{
    int low,high,mid,count=0,count1=0;
    low = 0;
    high = n;
    while(low<high)    
    {
        count++;
        mid = (low + high) / 2;
        if(key<a[mid])
            high = mid - 1;
        else if(key>a[mid])
            low = mid + 1;
        else if (key == a[mid])
        {
            cout << "�ɹ����ң� ����" << count << "�� λ���� : " << mid << " Ԫ���� : " << a[mid] << endl;
            count1++;
            break;
        }
    }
    if (count1 == 0)
        cout << "����ʧ��!" << endl;
    return 0;
}
int main(){
    cout << "��������Ԫ�صĸ�����" << endl;
    int n;
    cin >> n;
    int *a = new int[n];
    cout << "������Ԫ�أ�" << endl;
    for (int i = 0; i < n; i++){
        cout << i + 1 << " : ";
        cin >> a[i];
    }
    sort(a, n);
    int key;
    cout << "��������ҵ�Ԫ�� : " << endl;
    cin >> key;
    int x = binary_search(key, a, n);
    delete[] a;
    return 0;
}