#include <stdio.h>
#define gc getchar_unlocked
inline int fast_input(void)
{
	char t;
	int x=0;
	int neg=0;
	t=gc();
	while((t<48 || t>57) && t!='-')
		t=gc();
	if(t=='-')
		neg=1;
	else
	{
		while(t>=48 && t<=57)
		{
			x=(x<<3)+(x<<1)+t-48;
			t=gc();
		}
	}
	if(neg)
		x=-x;
	return x;
}
inline void fast_output(int x)
{
	char a[12];
	int i=0,j;
	a[0]='0';
	while(x)
	{
		a[i++]=x%10+48;
		x/=10;
	}
	for(j=i-1;j>=0;j--)
	{
		putchar_unlocked(a[j]);
	}
	putchar_unlocked('\n');
}
int main()
{
	int t;
	t=fast_input();
	while(t--)
	{
		int n,min1=9999999,min2=9999999,x,temp;
		n=fast_input();
		while(n--)
		{
			x=fast_input();
			if(min1>x)
			{
				min2=min1;
				min1=x;
			}
			else if(min2>x && min1!=x)
			{
				min2=x;
			}
		}
		fast_output(min1+min2);
	}
	return 0;
}
