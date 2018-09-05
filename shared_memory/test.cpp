#include<iostream>
using namespace std;
void fun(int a, int b)
{
	cout<<&a<<endl;
	cout<<&b<<endl;
	return;
}
int main()
{
	int a; int b;
	fun(a,b);
	return 0;
}
