#include<iostream>
using namespace std;
void quickSort(int arr[], int low, int high)
{
    int first = low;
    int last  = high;
    int key = arr[first];
    if(low >= high)
        return;
    while(first < last){
        while(first < last && arr[last] > key){
            last--;
        }
        arr[first] = arr[last];
        while(first < last && arr[first] < key){
            first++;
        }
        arr[last] = arr[first];
    }
    arr[first] = key;
    quickSort(arr, low, first-1);
    quickSort(arr, first+1, high);
}

int main(){
    int i;
    int a[10];
    for(i = 0; i < 10; i++){
        a[i] = rand() % 1000;
        cout << a[i] << "  ";
    }
    cout << endl;
    quickSort(a, 0, 9);
    for (i = 0; i < 10; i++){
        cout << a[i] << "  ";
    }
    cout << endl;
    return 0;
}


