#include <stdio.h>

int main(void) {
	int n,i,j,t,k;
	scanf("%d",&k);
	while(k>0)
	{
		scanf("%d",&n);
		int fg=0,j=n,t=1;
		while(n>0)
		{
			i=n%10;
			if(i>=1)
			{
				fg=1;
				break;
			}
			n/=10;
			t*=10;
		}
		if(j==t)
		{
			fg=0;
		}
		if(fg)
			printf("YES\n");
		else
			printf("NO\n");
		k--;
	}
	return 0;
}
