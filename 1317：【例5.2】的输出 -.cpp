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
void search(int step)//һ���������������� 
{
	for(int i=a[step-1]/*��������ͱ��������*/;i<=n;i++)//������������������� 
	{
		if(!flag[i])
		{
			flag[i]=true;
			a[step]=i;//�ڼ�����λ 
			if(step==r)//����
			  print();
			else 
			  search(step+1);
			flag[i]=0;//�ѵ�ǰ�������������� 
		}
	}
}
int main()
{
	a[0]=1; 
	cin>>n>>r;
	search(1); 
	return 0;
}
