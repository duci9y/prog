#include<stdio.h>
#include<string.h>
#ifndef ONLINE_JUDGE
inline int getchar_unlocked() { return getchar(); }
inline void putchar_unlocked(char a) { putchar(a); }
#endif
inline void fastRead(int *a)
{
register char c=0;
while (c<33)
{
c=getchar_unlocked();
}
*a=0;
while (c>33)
{
*a=*a*10+c-48;
c=getchar_unlocked();
}
}
inline void fastWrite(int a)
{
char snum[12];
register int i=0;
do
{
snum[i++]=a%10+48;
a=a/10;
}while(a!=0);
--i;
while(i>=0)
putchar_unlocked(snum[i--]);
putchar_unlocked('\n');
}
int ans[10]={9,81,648,4536,27216,136080,544320,1632960,3265920,3265920};
int fn(char *c,int size,int in)
{
int fixed,sum=0,count,i,j,k,flag=0,temp;
if(size>10)
{
sum=ans[9];
size=10;
}
else
{
count=0;
while(count<size && flag==0)
{
i=0;
k=0;
while(i<count)
{
if(c[count]>c[i])
k++;
if(c[count]==c[i])
flag=1;
i++;
}
fixed=j=count;
temp=c[count]-48-k;
if(temp<0)
temp=0;
if(!count)
temp--;
while(j<size-1)
{
temp*=(9-fixed++);
j++;
}
sum+=temp;
count++;
}
if(flag==0 && in==0)
{
++sum;
}
}
while(--size)
sum+=ans[size-1];
return sum;
}
main()
{
char r[20],l[20];
register char c;
register int i;
int ls,rs,t,result;
fastRead(&t);
while(t--)
{
//scanf("%s%s",l,r);
c=getchar_unlocked();
while( c<33 )
c=getchar_unlocked();
i=0;
while( c>33 )
{
l[i++]=c;
c=getchar_unlocked();
}
l[i]='\0';
while( c<33 )
c=getchar_unlocked();
i=0;
while( c>33 )
{
r[i++]=c;
c=getchar_unlocked();
}
r[i]='\0';
rs=strlen(r);
ls=strlen(l);
result=fn(r,rs,0)-fn(l,ls,1);
fastWrite(result);
}
} 
