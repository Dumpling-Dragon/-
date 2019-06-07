#include<iostream>
#include<cstdio>
using namespace std;
int n,r,a[21];
bool flag[21]={0};
void print()
{
    for(int i=1;i<=r;i++)
        cout<<"  "<<a[i];
    cout<<endl;
}
void search(int step)//一共三个，分三步填 
{
	for(int i=a[step-1]/*不加这个就变成排列了*/;i<=n;i++)//算符数量，即可填数量 
	{
		if(!flag[i])
		{
			flag[i]=true;
			a[step]=i;//第几个空位 
			if(step==r)//填满
			  print();
			else 
			  search(step+1);
			flag[i]=0;//把当前步骤填的数字清掉 �������� 
		}
	}
}//
int main()
{
	a[0]=1; 
	cin>>n>>r;
	search(1); 
	return 0;
}//哈哈哈 
