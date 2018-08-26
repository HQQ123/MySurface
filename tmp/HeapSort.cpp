#include<iostream>
#include<vector>
using namespace std;
void HeapSort(vector<int> &arr);
void HeapAdjust(vector<int> & arr, int low, int high);
void swap(vector<int> &arr, int i, int j);
int main()
{
	int arr[10] = {9,2,2,1,6,3,7,6,8,10};
	vector<int> vec(arr, arr+10);
	HeapSort(vec);
	for(int i=0; i<vec.size(); i++)
		cout<<vec[i]<<endl;
	return 0;
}
void HeapSort(vector<int>& arr)
{
	for(int i=(arr.size()-1)/2; i>=0; i-- )
		HeapAdjust(arr, i, arr.size());
	for(int i=arr.size()-1; i>0; i--)
	{
		swap(arr, 0, i);
		HeapAdjust(arr, 0, i);
	}
}
void HeapAdjust(vector<int> & arr, int low, int high)
{
	 int temp = arr[low];
	 for(int j=2*low+1; j<high; j=2*low+1)
	 {
		 if(j+1<high && arr[j+1]>arr[j])
			 j++;
		 if(temp>arr[j])
			 break;
		 arr[low] = arr[j];
		 low = j;
	 }
	 arr[low] = temp;
}
void swap(vector<int>& arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
