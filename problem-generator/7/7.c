#include<stdio.h>
#include<string.h>
#define DIFF(a,b) ((a)>(b)?((a)-(b)):((b)-(a)))
static char str[100009];
int main()
{
	int dist[12][12],le[12],i,j,len,d1,d2;
	char sc,ec,chr1,chr2;
	scanf("%s",str);
	len = strlen(str);
	if(len==1)
	{
		printf("0\n");
		return 0;
	}
	if(str[len-1]==str[0]||len==2)
	{
		printf("1\n");
		return 0;
	}
	for(i=0;i<12;i++)
	{
		le[i] = -1;
		for(j=0;j<12;j++)
			dist[i][j] = -1;
	}
	sc = str[0];
	str[0] = 's';
	ec = str[len-1];
	str[len-1] = 'e';
	le[10]=0;
	for(i=1;i<len-1;i++)
	{
		chr1 = str[i];
		le[chr1-'0'] = i;
		if(i<dist[chr1-'0'][10]||dist[chr1-'0'][10]==-1)
			dist[chr1-'0'][10] = dist[10][chr1-'0'] = i;
		if((len-i-1)<dist[chr1-'0'][11]||dist[chr1-'0'][11]==-1)
			dist[chr1-'0'][11] = dist[11][chr1-'0'] = len-i-1;
		for(j=0;j<10;j++)
		{
			if(le[j]!=-1)
			{
				if(DIFF(le[j],i)<dist[chr1-'0'][j]||dist[chr1-'0'][j]==-1)
					dist[chr1-'0'][j] = dist[j][chr1-'0'] = DIFF(le[j],i);
				if(j==sc-'0'&&(dist[10][chr1-'0']>(dist[j][chr1-'0']+1)||dist[10][chr1-'0']==-1))
					dist[10][chr1-'0'] = dist[chr1-'0'][10] = dist[j][chr1-'0']+1;
				if(j==ec-'0'&&(dist[11][chr1-'0']>(dist[j][chr1-'0']+1)||dist[11][chr1-'0']==-1))
					dist[11][chr1-'0'] = dist[chr1-'0'][11] = dist[j][chr1-'0']+1;
				if(chr1==sc&&(dist[10][j]>(dist[j][chr1-'0']+1)||dist[10][j]==-1))
					dist[10][j] = dist[j][10] = dist[j][chr1-'0']+1;
				if(chr1==ec&&(dist[11][j]>(dist[j][chr1-'0']+1)||dist[11][chr1-'0']==-1))
					dist[11][j] = dist[j][11] = dist[j][chr1-'0']+1;
				if((dist[chr1-'0'][j]+dist[j][10]+1)<dist[chr1-'0'][10]||dist[chr1-'0'][10]==-1)
					dist[chr1-'0'][10] = dist[10][chr1-'0'] = dist[chr1-'0'][j]+dist[j][10]+1;
				if((dist[chr1-'0'][j]+dist[j][11]+1)<dist[chr1-'0'][11]||dist[chr1-'0'][11]==-1)
					dist[chr1-'0'][11] = dist[11][chr1-'0'] = dist[chr1-'0'][j]+dist[j][11]+1;
				/*if((dist[chr1-'0'][j]+dist[j][10]+1)<dist[chr1-'0'][10]||dist[chr1-'0'][10]==-1)
					dist[chr1-'0'][10] = dist[10][chr1-'0'] = dist[chr1-'0'][j]+dist[j][10]+1;
				if((dist[chr1-'0'][j]+dist[j][11]+1)<dist[chr-'0'][11]||dist[chr1-'0'][11]==-1)
					dist[chr1-'0'][11] = dist[11][chr1-'0'] = dist[chr1-'0'][j]+dist[j][11]+1;*/
				if(dist[chr1-'0'][10]+dist[chr1-'0'][11]>dist[10][11]||dist[10][11]==-1)
					dist[10][11] = dist[11][10] = dist[chr1-'0'][10]+dist[chr1-'0'][11];
			}
		}
	}
	chr1 = str[len-1];
	if((len-1)<dist[10][11]||dist[10][11]==-1)
		dist[10][11] = dist[11][10] = len-1;
	for(j=0;j<10;j++)
	{
		if(le[j]!=-1)
		{
			if(DIFF(le[j],len-1)<dist[11][j]||dist[11][j]==-1)
				dist[11][j] = dist[j][11] = DIFF(le[j],len-1);
			if(j==sc-'0'&&(dist[10][11]>(dist[j][11]+1)||dist[10][11]==-1))
				dist[10][11] = dist[11][10] = dist[j][11]+1;
			if(j==ec-'0'&&(dist[10][11]>(dist[j][10]+1)||dist[10][11]==-1))
				dist[10][11] = dist[11][10] = dist[j][10]+1;
		}
	}
	printf("%d\n",dist[10][11]);
	return 0;
}
