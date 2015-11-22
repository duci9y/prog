#include<bits/stdc++.h>
using namespace std;
long long m;
long long power(long long a,long long b,long long x)
{
	if(b==0)
		return 1;
	long long temp=power(a,b/2,x);
	temp=(temp*temp)%x;
	if(b&1)
		temp=(temp*a)%x;
	return temp;
}
vector<long long>v;
void sieve()
{
    long long i,j,a[41100]={0};
    for(i=2;i<=41000;i++)
        if(!a[i])
            for(j=i*i;j<=41000;j+=i)
                a[j]=1;
   for(i=2;i<=41000;i++)
        if(!a[i])
            v.push_back(i);
}
int main()
{
	int t;
	long long i,n,k,q,j;
	sieve();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&m,&q);
		if(n<=11)
		{
			long long int a[12][5]={{0}};
			for(i=2;i<=11;i++)
			{
				if(i==2)
					a[i][0]=2;
				if(i==3)
					a[i][1]=3;
				if(i==4)
					a[i][0]=8;
				if(i==5)
					a[i][2]=5;
				if(i==6)
				{
					a[i][0]=6;
					a[i][1]=6;
				}
				if(i==7)
					a[i][3]=7;
				if(i==8)
					a[i][0]=24;
				if(i==9)
					a[i][1]=18;
				if(i==10)
				{
					a[i][0]=10;
					a[i][2]=10;
				}
				if(i==11)
					a[i][4]+=11;
			}
			for(i=3;i<=11;i++)
			{
				for(j=0;j<=4;j++)
				a[i][j]+=a[i-1][j];
			}
			while(q--)
			{
				scanf("%lld",&k);
				long long int p[5]={0};
				for(i=0;i<5;i++)
					p[i]=a[n][i]-a[k][i]-a[n-k][i];
		//		for(i=0;i<5;i++)
		//			cout<<p[i]<<" ";
				long long ans=1;
				for(i=0;i<5;i++)
					ans=(ans*power(v[i],p[i],m))%m;
				ans=(ans%m);
				printf("%lld\n",ans);
			}
		}
		else
		{
			long long x=1;
			long long p=m;
			long long counter=0;
			for(i=0;i<v.size()&&p!=1;)
			{
				if(m%v[i]==0)
				{
					counter=1;
					p=p/v[i];
					while(p%v[i]==0)
	  			        counter++,p=p/v[i];
					x*=(power(v[i],counter,m+1)-power(v[i],counter-1,m+1));
					i++;
				}
			     	else
					i++;
			}
			if(p!=1)
				x*=(p-1);
			long long a[n/2+2];
			a[1]=power(n,n,m);
			for(i=2;i<=n/2;i++)
			{
				long long y=power(i,x-1,m);
				y=power(y,i,m);
				long long z=power(n+1-i,n+1-i,m);
				z=(y*z)%m;
				a[i]=(a[i-1]*z)%m;
			}
			while(q--)
			{
				scanf("%lld",&k);
				if(k<=n/2)
					printf("%lld\n",a[k]);
				else
					printf("%lld\n",a[n-k]);
			}
		}
	}
	return 0;
}
